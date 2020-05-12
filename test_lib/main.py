import sys
import os
import random
import subprocess as sub
from concurrent.futures import ThreadPoolExecutor
from datetime import datetime
from threading import Lock

from colorama import init, Fore, Style

# Configuration settings
MAX_THREADS = 5
TIMEOUT = 5.
GCC_ARGS = ['-DLOCAL', '-O2']

PROBLEMS = (
    ('test/graph_ds/unionfind.cpp', 'datastructure/unionfind'),
    ('test/ds/prefix_sum_array.cpp', 'datastructure/static_range_sum'),
    ('test/ds/bit.cpp', 'datastructure/point_add_range_sum'),
    ('test/ds/sparse_table.cpp', 'datastructure/staticrmq'),
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
CE = (Fore.RED + Style.DIM, 'CE')
WA = (Fore.LIGHTRED_EX, 'WA')
AC = (Fore.GREEN, 'AC')
RE = (Fore.LIGHTYELLOW_EX, 'RE')

# Only for debugging
# PROBLEMS = TEST_PROBLEMS


def check(out, expected_out):
    """
    Checker for solutions
    :param out: Actual output
    :param expected_out: Expected output
    """
    return out.split() == expected_out.split()


# TODO: Make result logging multiline instead of as separate messages.  It would be cleaner and faster
log_lock = Lock()


def log(msg=''):
    """
    Logs a message.  Thread name and time are included
    :param msg: Message to log
    """
    log_lock.acquire()
    full_msg = f'[{datetime.now().strftime("%H:%M:%S")}] {msg}'
    print(full_msg)
    log_lock.release()


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
    :param src_file_problem: A tuple (source file to test, id of the problem to test the source code on, only if using the Yosupo judge.  Otherwise, leave this as blank)
    :return: A tuple (msg, passed), the log message for the verdict, and whether it passed or not
    """
    src_file, problem = src_file_problem
    src_name = path_name(src_file)
    problem_id = problem.split('/')[-1]
    yosupo = bool(problem)

    # Colorama
    colorama_init()

    # Logging Utils
    passed = []
    failed = []

    def log_message(verdict, message=None, extra=None):
        """
        Creates a log message for the result of the tests
        :param verdict: A verdict object- a tuple of (style, label)
        :param message: Some judge feedback that is displayed on the same line as the verdict, optional
        :param extra: Extra feedback displayed on the next line, optional
        :return:
        """
        return (f'{verdict[0]}{src_name} ({problem}) {verdict[1]}' + (f': {message}' if message else '') + f'{Style.RESET_ALL}\n' +
                (f'\t{extra}\n' if extra else '') +
                (f'\tpassed: {", ".join(passed)}\n' if passed else '') +
                (f'\tfailed: {", ".join(failed)}\n' if failed else '')).rstrip('\n')

    # Compile
    log(f'Compiling {src_name}')
    exe_path = rand_exe_name()
    sub.run(['g++', src_file] + GCC_ARGS + ['-o', exe_path])
    if not os.path.exists(exe_path):
        return log_message(CE), False

    def cleanup():  # Cleanup function
        os.remove(exe_path)

    # Generate test data
    if yosupo:
        generator_lock.acquire()
        log(f'Generating test data for {src_name}...')
        sub.run(['python', 'test_lib/library-checker-problems/generate.py', '-p', problem_id])
        generator_lock.release()

    # Logging and checking functions

    passed = []
    failed = []

    def check_RE(res):  # Given a CompletedProcess, returns a log message if there was an RE and None otherwise
        if res.returncode:
            return log_message(RE, f'non-zero return code', f'Test {test}: code {res.returncode}')
        elif res.stderr:
            return log_message(RE, f'non-empty stderr', f'Test {test}: {res.stderr}')
        return None

    # Run on tests
    if yosupo:
        data_dir = f'{DATA_BASE_DIR}/{problem}'
        for test in (os.path.splitext(name)[0] for name in os.listdir(f'{data_dir}/in')):
            with open(f'{data_dir}/in/{test}.in') as f:
                test_input = f.read()
            with open(f'{data_dir}/out/{test}.out') as f:
                test_output = f.read()

            # Run tests
            res = sub.run(['./' + exe_path], timeout=TIMEOUT, capture_output=True, text=True, input=test_input)

            # Check
            msg = check_RE(res)
            if msg:
                cleanup()
                return msg, False

            if check(res.stdout, test_output):
                passed.append(test)
            else:
                failed.append(test)
                cleanup()
                return log_message(WA, f'test {test}'), False

        cleanup()
        return log_message(AC), True
    else:
        # Run program
        res = sub.run(['./' + exe_path], timeout=TIMEOUT, capture_output=True, text=True)
        msg = check_RE(res)
        cleanup()

        # Checking
        if msg:
            return msg, False
        if res.stdout.strip() == 'AC':
            return log_message(AC, 'local tests'), True
        else:
            return log_message(WA, 'local tests'), False


if __name__ == '__main__':
    # Init colorama
    colorama_init()

    log(f'Working directory {os.getcwd()}')
    log('Running tests...')

    # If the first argument was specified, then that means only one problem should be graded
    if len(sys.argv) >= 2 and sys.argv[1]:
        for path, problem_id in PROBLEMS:  # Find the correct corresponding problem from the name of the test file
            if sys.argv[1] in path:
                msg, _ = get_res((path, problem_id))
                log(msg)
                sys.exit(0)
        log(f'No test file with the name {sys.argv[1]} was found!')
    else:
        # Make pool and run tests
        passed = []
        failed = []
        with ThreadPoolExecutor(max_workers=MAX_THREADS, thread_name_prefix='T') as pool:
            for index, msg_passed_tuple in enumerate(pool.map(get_res, PROBLEMS)):
                msg, case_passed = msg_passed_tuple
                log(msg)

                if case_passed:
                    passed.append(PROBLEMS[index][1])
                else:
                    failed.append(PROBLEMS[index][1])

            log()
            log(f'Passed {len(passed)} tests, failed {len(failed)} tests\n'
                f'\tPassed: {", ".join(passed)}\n'
                f'\tFailed: {", ".join(failed)}')
