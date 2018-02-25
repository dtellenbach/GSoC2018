# Google Summer of Code 2018 - Faster Matrix Algebra for ATLAS #

David A. Tellenbach <<david.tellenbach@me.com>>
## Overview ##

This repository contains a very first draft for an efficient implementation of symmetric matrices using the C++ library Eigen. More information about the project and the design of the contained class SymmetricMatrix can be found in the Doxygen documentation.

### Structure ###

The repository is structured as follows

    GSoC2018
    ├── README.markdown             
    ├── makefile 
    ├── build.py                  
    ├── doc     
    |   ├── doxygen
    │   │   ├── Doxyfile
    │   │   └── mainpage.dox                   
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

The SymmatricMatrix class is header only, therefore you can just include the file ``./include/SymmatricMatrix.h`` and give it a try.
Since this is an experimental project, Eigen is included in the ``./include`` directory. There is no need to have it in one of your include directories. Actually you can build everything except the Google benchmarks with nothing installed but a compiler that supports C++11.

Using GNU Make you can build the contained examples, benchmarks, tests and the documenation. The following make directives are available:

    example             Builds the examples
    benchmark           Builds the benchmarks
    googlebenchmark     Builds benchmarks using Google's benchmark library
    test                Builds tests
    html-doc            Builds documentation of SymmetricMatrix as HTML
    pdf-doc             Builds documentation of SymmetricMatrix as PDF
    clean               Removes built executables and documentation

E.g., running ``make example`` builds all files contained in (./examples)[./examples] in ./bin. 

## Examples ##

Several examples that demonstrate all features of the matrix class can be found in [./example](./doc/Documentation.pdf). In detail the following topics are covered:

**[Example 1](./examples/example1.cc)**
- Construct an instance of ``SymmetricMatrix`` from an instance of ``Eigen::Matrix`` (fixed size)
- Print an instance of ``SymmetricMatrix`` into console
- Test if an instance of ``Eigen::Matrix`` is symmetric
- Access elements of the symmetric matrix directly and change their value

**[Example 2](./examples/example2.cc)**
- Difference between matrices with fixed and with dynamic size
- Typedefs for several classes of class template SymmetricMatrix
- Constructing symmetric matrices filled with random values

**[Example 3](./examples/example3.cc)**
- Addition and subtraction for two instances of symmetric matrix
- Addition and subtraction for symmetric matrices and arbitrary matrices

**[Example 4](./examples/example4.cc)**
- Multiplication for two instances of symmetric matrix
- Multiplication of symmetric and arbitrary matrices

**[Example 5](./examples/example5.cc)**
- Runtime excpetions and compile-time errors




