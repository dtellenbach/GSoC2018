#!/usr/bin/env python3

################################################################################
#   Google Summer of Code 2018 - Faster Matrix Algebra for ATLAS               #
#                                                                              #
#   David A. Tellenbach <david.tellenbach@me.com>                              #
#                                                                              #
#   Build script for the evaluation the of the Google Summer of Code 2018      #
#   project 'Faster Matrix Multiplication for ATLAS'                           #
################################################################################

import os
import argparse
import subprocess

compiler = 'g++'

# Generic build function that gets called by all specific build functions with
# different arguments depending on build type
def build(dep, outfile, infile, cc, ccargs, largs):
    print("Checking dependencies...")
    for entry in dep:
        check = checkProgram(entry)
        print(" > Checking for {}...".format(entry), end='')
        if check is not None:
            print(" Found -> {}".format(check))
        else:
            print(" Not found. Exit.")
            exit()

    # Join everything into a single list
    cmd = [cc] + ccargs + largs + ['-o'] + [outfile, infile]
    
    print("Running {} ...".format(' '.join(cmd)))
    # Try to open subprocess and execute build command
    try:
        proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, 
                                 stderr=subprocess.PIPE)
        stdout, stderr = proc.communicate()
        if len(stdout) != 0:
            print(stdout.decode("utf-8"))
        if len(stderr) != 0:
            print(stderr.decode("utf-8"))
            exit()
    except subprocess.TimeoutExpired:
        proc.kill()
        outs, errs = proc.communicate()

    print("Done.")

# Buildtype test
def buildTest(infile, outfile):
    infile = os.path.join('./test', infile)
    ccargs = ['-std=c++11', '-Wall', '-Werror', '-Wpedantic']
    global compiler
    build([compiler], outfile, infile, compiler, ccargs, [])

# Buildtype example
def buildExample(infile, outfile):
    infile = os.path.join('./examples', infile)
    ccargs = ['-std=c++11', '-O3']
    global compiler
    build([compiler], outfile, infile, compiler, ccargs, [])

# Buildtype benchmark
def buildBenchmark(infile, outfile):
    infile = os.path.join('./benchmark', infile)
    ccargs = ['-std=c++11']
    global compiler
    if compiler == 'icpc':
        ccargs.append('-fast')
    else:
        ccargs.append('-O3')
    build([compiler], outfile, infile, compiler, ccargs, [])

# Buildtype googlebenchmark
def buildGoogleBenchmark(infile, outfile):
    infile = os.path.join('./googlebenchmark', infile)
    ccargs = ['-std=c++11', '-O3']
    largs = ["-lbenchmark"]
    global compiler
    if compiler == 'icpc':
        ccargs.append('-fast')
    else:
        ccargs.append('-O3')
    build([compiler], outfile, infile, compiler, ccargs, largs)

# Check if a program is installed. This basically mimics the UNIX command which
def checkProgram(program):
    def is_exe(fpath):
        return os.path.isfile(fpath) and os.access(fpath, os.X_OK)

    fpath, fname = os.path.split(program)
    if fpath:
        if is_exe(program):
            return program
    else:
        for path in os.environ["PATH"].split(os.pathsep):
            exe_file = os.path.join(path, program)
            if is_exe(exe_file):
                return exe_file
    return None

# Find all files in a given directory with externsion .cc or .cpp
def findFiles(path):
    ret = []
    for root, dir, files in os.walk(path):
        for file in files:
            if file.endswith('.cc') or file.endswith('.cpp'):
                ret.append(os.path.join(root, file))
    return ret

def main():
    
    # Parse command line arguments
    parser = argparse.ArgumentParser(description='Build benchmarks, tests and examples '
                                                 'for the evaluation test for '
                                                 'the Google Summer of Code '
                                                 'Project <Faster Matrix '
                                                 'Multiplication for ATLAS>')


    parser.add_argument('--type', '-t', 
                        choices = ['test', 'example', 'benchmark', 'googlebenchmark'],
                        help = 'The type of executable you want to build',
                        dest = 'buildtype')

    parser.add_argument('--file', '-f',
                        metavar = "FILE",
                        help = 'The file you want to build',
                        dest = 'infile')

    parser.add_argument('--list', '-l',
                        action = 'store_true',
                        help = 'List all files and their build types and exit',
                        dest = 'listFlag')

    parser.add_argument('--setcc', '-s',
                        choices = ['clang', 'gcc', 'icc'],
                        help = 'Choose C++ compiler.',
                        dest = 'compiler')

    parser.add_argument('--clean', '-c',
                        action = 'store_true',
                        dest = 'cleanFlag',
                        help = 'Clean all built binaries, documentation and exit')

    parser.add_argument('--doxy', '-d',
                        action = 'store_true',
                        dest = 'doxyFlag',
                        help = 'Build doxygen documentation, create a symbolic'
                               ' to it at the top level of this repository'
                               ' and exit.')

    args = parser.parse_args()

    # Check for --list option
    if args.listFlag:
        print("\n{:<20}{:<11}".format("Build type","Filename (*.cc, *.cpp)"))
        print("--------------------------------------------------------")
        done = False

        # tests
        files = findFiles("./test")
        for file in files:
            if not done:
                print("{:<20}{:<11}".format("test", os.path.basename(file)))
                done = True
            else:
                print("{:<20}{:<11}".format('', os.path.basename(file)))
        done = False

        # examples
        files = findFiles("./examples")
        for file in files:
            if not done:
                print("{:<20}{:<11}".format("example", os.path.basename(file)))
                done = True
            else:
                print("{:<20}{:<11}".format('', os.path.basename(file)))
        done = False

        # benchmarks
        files = findFiles("./benchmark")
        for file in files:
            if not done:
                print("{:<20}{:<11}".format("benchmarks", os.path.basename(file)))
                done = True
            else:
                print("{:<20}{:<11}".format('', os.path.basename(file)))
        done = False

        # googlebenchmarks
        files = findFiles("./googlebenchmark")
        for file in files:
            if not done:
                print("{:<20}{:<11}".format("googlebenchmarks", os.path.basename(file)))
                done = True
            else:
                print("{:<20}{:<11}".format('', os.path.basename(file)))
        done = False
        return

    # Check for --clean and, if set, clean
    if args.cleanFlag:
        print("Cleaning directory ./bin...", end = "") 
        files = [ f for f in os.listdir("./bin") ] 
        for file in files:
            os.remove(os.path.join("./bin", file))
        print("Done.")
        print("Cleaning directory ./doc/doxygen/html...", end = "")
        subprocess.call(["rm", "-rf", "./doc/doxygen/html"])
        print("Done.")
        print("Cleaning symbolic link to doxygen...", end = "")
        if os.path.isfile("./SymmetricMatrix.html"):
            os.remove("./SymmetricMatrix.html")
        print("Done.\nExit.")
        return

    # Check for --doxy
    if args.doxyFlag:
        dxy = checkProgram("doxygen")
        if dxy is None:
            print(__file__ + ": Error: Doxygen not found. Exit.")
            return
        else:
            print("Doxygen found: {}".format(dxy))
        print("Creating doxygen documentation...", end = "")
        subprocess.call([dxy, "./doc/doxygen/Doxyfile"])
        print("Done.")
        print("Creating symbolic link to documentation...", end = "")
        if os.path.isfile("SymmetricMatrix.html"):
            os.remove("SymmetricMatrix.html")
        os.symlink("./doc/doxygen/html/index.html", "SymmetricMatrix.html")
        print("Done.\nExit.")
        return

    # Check for --type and --file
    if args.buildtype is None:
        print(__file__ + ": Error: Missing option --type, -t")
        return
    if args.infile is None:
        print(__file__ + ": Error: Missing option --file, -f")
        infile = args.infile
        return
    else:
        infile = args.infile

    # Set outfile
    outfile = os.path.splitext(infile)[0] 
    outfile = './bin/' + outfile

    # Check for compiler
    global compiler
    if args.compiler is None or args.compiler == 'gcc':
        compiler = 'g++'     # GCC
    elif args.compiler == 'clang':
        compiler = 'clang++'   # LLVM Clang
    elif args.compiler == 'icc':
        compiler = 'icpc'     # Intel C++ Compiler

    # Invoke build based on buildtype
    if args.buildtype == 'test':
        buildTest(infile, outfile)
    elif args.buildtype == 'example':
        buildExample(infile, outfile)
    elif args.buildtype == 'benchmark':
        buildBenchmark(infile, outfile)
    elif args.buildtype == 'googlebenchmark':
        buildGoogleBenchmark(infile, outfile)


# if __file__ == 'build.py':
#     main()

main()

