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
    |   ├── Documentation.pdf                  
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
    └── bin

## How to build ##

The SymmatricMatrix class is header only, therefore you can just include the file ``./include/SymmatricMatrix.h``, change the include path for Eigen and give it a try.

To build the examples and benchmarks included you should use the ``./build.py`` script with the followng syntax

    build.py --type {test,example,benchmark,googlebenchmark}
             --file FILE --out FILE [--run] [--list] [--clean][-h]

For example the command

    ./build.py --type=example --file=example1.cc

would build the file ``./examples/example1.cc`` and create an executable ``./bin/example1``.

Before start building ``./build.py`` will check for several dependencies like compiler versions or the existence of the Google benchmark library.

Since this is an experimental project, Eigen is included in the ``./include`` directory. There is no need to have it in one of your include directories. 

Actually you can build everything except the Google benchmarks with nothing installed but a compiler that supports C++11.

## Examples ##

Several examples that demonstrate all features of the matrix class can be found in [./example](./doc/Documentation.pdf). In detail the following topics are covered:

**[Example 1](./example/example1.cc)**
- Construct an instance of ``SymmetricMatrix`` from an instance of ``Eigen::Matrix``
- Print an instance of ``SymmetricMatrix`` into console
- Test if an instance of ``Eigen::Matrix`` is symmetric

**[Example 2](./example/example2.cc)**
- Construct an instance of ``SymmetricMatrix`` from ``std::vector```
- Perform addition for two instances of ``SymmetricMatrix``
- Perform multiplication for two instances of ``SymmetricMatrix``

**[Example 2](./example/example3.cc)**
- Get to know the difference between fixed dimension (compile-time) and dynamic dimension (runtime)
- See how fixed and dynamic dimensions react differently on terms of error reporting

## Further Information ##

Further information about the design of the SymmetricMatrix class and benchmark results for both, time and space, check out the [documentation](./doc/Documentation.pdf).



