import os
import random
import subprocess as sub
from concurrent.futures import ThreadPoolExecutor
from datetime import datetime
from threading import current_thread, Lock

from colorama import init, Fore, Style

# Configuration settings
MAX_THREADS = 5
TIMEOUT = 5.
GCC_ARGS = ['-DLOCAL', '-O2']

PROBLEMS = (
    ('test/graph_ds/unionfind.cpp', 'datastructure/unionfind'),
)

# Some constant values
DATA_BASE_DIR = 'test_lib/library-checker-problems/'
RAND_LIM = (0, 1000000000)
TEST_PROBLEMS = (  # Only for testing the tester
    ('test/test_tests/aplusb.cpp', 'sample/aplusb'),
    ('test/test_tests/aplusb_wa.cpp', 'sample/aplusb'),
    ('test/test_tests/aplusb_ce.cpp', 'sample/aplusb'),
    ('test/test_tests/aplusb_sigsev.cpp', 'sample/aplusb'),
    ('test/test_tests/aplusb_abort.cpp', 'sample/aplusb'),
)

# Colorama Style Settings
CE = Fore.RED + Style.DIM + 'CE' + Style.RESET_ALL + ' '
WA = Fore.LIGHTRED_EX + 'WA' + Style.RESET_ALL + ' '
AC = Fore.GREEN + 'AC' + Style.RESET_ALL + ' '
RE = Fore.LIGHTYELLOW_EX + 'RE' + Style.RESET_ALL + ' '

# Only for debugging
# PROBLEMS = TEST_PROBLEMS


def check(out, expected_out):
    """
    Checker for solutions
    :param out: Actual output
    :param expected_out: Expected output
    """
    return out.split() == expected_out.split()


def log(msg):
    """
    Logs a message.  Thread name and time are included
    :param msg: Message to log
    """
    full_msg = f'[{current_thread().name}/{datetime.now().strftime("%H:%M:%S")}] {msg}'
    print(full_msg)


def rand_exe_name():
    """
    Returns a random name for an executable file (that hasn't been taken already)
    """
    path = f'{random.randint(*RAND_LIM)}.exe'
    while os.path.exists(path):
        path = f'{random.randint(*RAND_LIM)}.exe'
    return path


def path_name(path):
    """
    Returns name of file path
    :param path: File path
    """
    return path.split('/')[-1]


def colorama_init():
    """
    Inits colorama
    """
    init(strip=False, convert=True, autoreset=True)


# Generator lock
generator_lock = Lock()


def get_res(src_file_problem):
    """
    Tests the specified source file.  Returns whether it passed the test cases
    :param src_file_problem: A tuple: (source file to test, Path to problem data folder relative to library-checker-problems root directory)
    :return: Whether the tests passed or not
    """
    src_file, problem = src_file_problem
    src_name = path_name(src_file)
    problem_id = problem.split('/')[-1]

    # Colorama
    colorama_init()

    # Compile
    log(f'Compiling {src_name}')
    exe_path = rand_exe_name()
    sub.run(['g++', src_file] + GCC_ARGS + ['-o', exe_path])
    if not os.path.exists(exe_path):
        log(f'{CE}Compile of {src_file} failed!')  # Using src_file instead of name so user knows full path
        return False

    def cleanup():  # Cleanup function
        os.remove(exe_path)

    # Generate test data
    generator_lock.acquire()
    log(f'Generating test data for {src_name}...')
    sub.run(['python', 'test_lib/library-checker-problems/generate.py', '-p', problem_id])
    generator_lock.release()

    # Run on tests
    data_dir = f'{DATA_BASE_DIR}/{problem}'
    for test in (os.path.splitext(name)[0] for name in os.listdir(f'{data_dir}/in')):
        with open(f'{data_dir}/in/{test}.in') as f:
            test_input = f.read()
        with open(f'{data_dir}/out/{test}.out') as f:
            test_output = f.read()

        # Run tests
        res = sub.run(['./' + exe_path], timeout=TIMEOUT, capture_output=True, text=True, input=test_input)
        if res.returncode:
            log(f'{RE}{src_name} RE {test}: Non-zero return code {res.returncode}')
            cleanup()
            return False
        elif res.stderr:
            log(f'{RE}{src_name} RE {test}: stderr: {res.stderr}')
            cleanup()
            return False

        # Check
        if check(res.stdout, test_output):
            log(f'{AC}{src_name} passed {test}')
        else:
            log(f'{WA}{src_name} failed {test}')
            cleanup()
            return False
    cleanup()
    return True


if __name__ == '__main__':
    # Init colorama
    colorama_init()

    print(os.getcwd())
    log('Running tests...')

    # Make pool and run tests
    with ThreadPoolExecutor(max_workers=MAX_THREADS, thread_name_prefix='T') as pool:
        passed_cnt = 0
        failed_cnt = 0
        for index, passed in enumerate(pool.map(get_res, PROBLEMS)):
            src_file, test_name = PROBLEMS[index]
            src_name = path_name(src_file)

            msg = f'{Fore.GREEN}{src_name} passed' if passed else f'{Fore.LIGHTRED_EX}{src_name} Failed'
            log(f'{msg} test set {test_name}')

            if passed:
                passed_cnt += 1
            else:
                failed_cnt += 1

        log(f'Passed {passed_cnt} tests, failed {failed_cnt} tests')
