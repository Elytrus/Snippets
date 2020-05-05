import os
import random
import subprocess as sub
from datetime import datetime
from multiprocessing import Pool
from threading import current_thread

from colorama import init, Fore, Style

# Configuration settings
MAX_THREADS = 5
TIMEOUT = 5.
GCC_ARGS = ['-DLOCAL', '-O2']
PROBLEMS = (
    ('test/aplusb.cpp', 'aplusb'),
    ('test/aplusb_wa.cpp', 'aplusb'),
    ('test/aplusb_ce.cpp', 'aplusb'),
    ('test/aplusb_sigsev.cpp', 'aplusb'),
    ('test/aplusb_abort.cpp', 'aplusb'),
)
RAND_LIM = (0, 1000000000)

# Some constants that shouldn't be touched
DATA_BASE_DIR = 'test_lib/library-checker-problems/sample'

# Colorama Style Settings
CE = Fore.RED + Style.DIM + 'CE' + Style.RESET_ALL + ' '
WA = Fore.LIGHTRED_EX + 'WA' + Style.RESET_ALL + ' '
AC = Fore.GREEN + 'AC' + Style.RESET_ALL + ' '
RE = Fore.LIGHTYELLOW_EX + 'RE' + Style.RESET_ALL + ' '


def check(out, expected_out):
    """
    Checker for solutions
    :param out: Actual output
    :param expected_out: Expected output
    :return:
    """
    return out.split() == expected_out.split()


def log(msg):
    """
    Logs a message.  Thread name and time are included
    :param msg: Message to log
    :return:
    """
    full_msg = f'[{current_thread().name}/{datetime.now().strftime("%H:%M:%S")}] {msg}'
    print(full_msg)


def rand_exe_name():
    """
    Returns a random name for an executable file (that hasn't been taken already)
    :return:
    """
    path = f'{random.randint(*RAND_LIM)}.exe'
    while os.path.exists(path):
        path = f'{random.randint(*RAND_LIM)}.exe'
    return path


def colorama_init():
    """
    Inits colorama
    :return:
    """
    init(strip=False, convert=True, autoreset=True)


def get_res(src_file, problem):
    """
    Tests the specified source file.  Returns whether it passed the test cases
    :param src_file: The source file to test
    :param problem: The ID of the problem to test the source code on
    :return:
    """

    # Colorama
    colorama_init()

    # Compile
    log(f'Compiling {src_file}')
    exe_path = rand_exe_name()
    sub.run(['g++', src_file] + GCC_ARGS + ['-o', exe_path])
    if not os.path.exists(exe_path):
        log(f'{CE}Compile of {src_file} failed!')
        return False

    def cleanup():  # Cleanup function
        os.remove(exe_path)

    # Generate test data
    log(f'Generating test data for {src_file}...')
    sub.run(['python', 'test_lib/library-checker-problems/generate.py', '-p', problem])

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
            log(f'{RE}{src_file} RE {test}: Non-zero return code {res.returncode}')
            cleanup()
            return False
        elif res.stderr:
            log(f'{RE}{src_file} RE {test}: stderr: {res.stderr}')
            cleanup()
            return False

        # Check
        if check(res.stdout, test_output):
            log(f'{AC}{src_file} passed {test}')
        else:
            log(f'{WA}{src_file} failed {test}')
            cleanup()
            return False
    cleanup()
    return True


if __name__ == '__main__':
    # Init colorama
    colorama_init()

    log('Running tests...')

    # Make pool and run tests
    with Pool(MAX_THREADS) as pool:
        passed_cnt = 0
        failed_cnt = 0
        for index, passed in enumerate(pool.starmap(get_res, PROBLEMS)):
            src_name, test_name = PROBLEMS[index]
            msg = f'{Fore.GREEN}{src_name} passed' if passed else f'{Fore.LIGHTRED_EX}{src_name} Failed'
            log(f'{msg} test set {test_name}')

            if passed:
                passed_cnt += 1
            else:
                failed_cnt += 1

        log(f'Passed {passed_cnt} tests, failed {failed_cnt} tests')
