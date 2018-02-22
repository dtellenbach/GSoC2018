# Google Summer of Code 2018 - Faster Matrix Algebra for ATLAS #

David A. Tellenbach <<david.tellenbach@me.com>>
## Overview ##

This repository contains a very first draft for an efficient implementation of symmetric matrices using the C++ library Eigen.

### Structure ###

The repository is structured as follows

    GSoC2018
    ├── README.markdown             
    ├── makefile 
    ├── build.py                  
    ├── doc                        
    │   ├── doxygen
    │   │   ├──src
    │   │   └── index.html
    │   ├── latex             
    │   └── img
    ├── include
    │   ├── SymmetricMatrix.h
    │   └── eigen3
    ├── benchmark
    │   ├── access.cc
    │   ├── addition1.cc
    │   ├── addition2.cc
    │   ├── multiplication1.cc
    │   ├── multiplication2.cc
    │   ├── memory.cc
    │   └── google
    ├── examples
    │   ├── example1.cc
    │   ├── example2.cc
    │   ├── example3.cc
    │   └── example4.cc
    ├── build
    └── bin

## Build ##

The SymmatricMatrix class is header only, therefore you can just include the file ``./include/SymmatricMatrix.h``, change the include path for Eigen and give it a try.

To build the examples and benchmarks included you should use the ``./build.py`` script with the followng syntax

    ./build.py 
        --type  One of the following build types:
                test, example, benchmark, googlebenchmark
        --file  Name of file you want to build
        --out   Name of output file (optional)
        --run   Run the executable after the build process
                has finished (optional)

For example the command

    ./build.py --type=example --file=example1.cc

would build the file ``./examples/example1.cc`` and create an executable ``./bin/example1``.

Before start building ``./build.py`` will check for several dependencies like compiler versions or the existence of the Google benchmark library.

Since this is an experimental project, Eigen is included in the ``./include`` directory. There is no need to have it in one of your include directories. 

Actually you can build everything except the Google benchmarks with nothing installed but a compiler that supports C++11.

## Further Information ##

Further information on how the project is 



