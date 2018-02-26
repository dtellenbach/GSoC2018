# Google Summer of Code 2018 - Faster Matrix Algebra for ATLAS #

This repository contains a very first draft for an efficient implementation of symmetric matrices using the C++ library Eigen. More information about the project and the design of the contained class SymmetricMatrix can be found in the project documentation that can be build using ``make doc-proj``.

## Structure ##

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
    │   │   └── project.tex
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
    doc-code            Builds the Doxygen documentation of SymmetricMatrix as HTML
    doc-proj            Builds documentation about the project and its design as PDF
    clean               Removes built executables and documentation

E.g., running ``make example`` builds all files contained in [./examples](./examples) in ./bin. 

### Dependencies ###

To build examples, benchmarks and tests a C++ compiler that supports C++11 is required. As default compiler ``gcc`` is chosen but you can change the [makefile](makefile) to other compilers like ``clang`` or ``icc``.

To build the Google benchmarks you need to ensure that the corresponding library and headers are available. See [here](https://github.com/google/benchmark) for further information about the Google benchmark library.

To build the Doxygen documentation of the SymmetricMatrix class Doxygen must be installed. See [here](https://www.stack.nl/~dimitri/doxygen/) for further information about Doxygen.

To build the project documentation pdflatex is required. See [here](https://www.tug.org/applications/pdftex/) for further information about pdflatex.

## Examples ##

Several examples that demonstrate all available features of the SymmetricMatrix class can be found in [./example](./example). In detail the following topics are covered:

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

## Benchmarks ##

The repository contains two types of benchmarks: Benchmarks using a selfcontained (Stopwatch)(benchmark/Stopwatch.hpp) class and benchmarks using the Google benchmark library. In detail the following benchmarks are included:

### Native Benchmarks ###

**[access.cc](benchmark/access.cc):** Measures the time consumption of accessing all elements of instances of SymmetricMatrix and Eigen::Matrix for several dynamic dimensions.

**[add_fixed.cc](benchmark/add_fixed.cc):** Measure the time consumption of addition of instances of SymmetricMatrix and Eigen::Matrix for several fixed dimensions.

**[add_dynamic.cc](benchmark/add_dynamic.cc):** Measure the time consumption of addition of instances of SymmetricMatrix and Eigen::Matrix for several dynamic dimensions.

**[mult_fixed.cc](benchmark/mult_fixed.cc):** Measure the time consumption of multiplication of instances of SymmetricMatrix and Eigen::Matrix for several fixed dimensions.

**[mult_dynamic.cc](benchmark/mult_dynamic.cc):** Measure the time consumption of multiplication of instances of SymmetricMatrix and Eigen::Matrix for several dynamic dimensions.

### Google Benchmarks ###

**[add_fixed_g.cc](googlebenchmark/add_fixed_g.cc):** Measure the time consumption of addition of instances of SymmetricMatrix and Eigen::Matrix for several fixed dimensions using the Google benchmark library.

**[add_dynamic_g.cc](googlebenchmark/add_dynamic.cc):** Measure the time consumption of addition of instances of SymmetricMatrix and Eigen::Matrix for several dynamic dimensions using the Google benchmark library.

**[mult_fixed_g.cc](googlebenchmark/mult_fixed_g.cc):** Measure the time consumption of multiplication of instances of SymmetricMatrix and Eigen::Matrix for several fixed dimensions using the Google benchmark library.

**[mult_dynamic_g.cc](googlebenchmark/mult_dynamic_g.cc):** Measure the time consumption of multiplication of instances of SymmetricMatrix and Eigen::Matrix for several dynamic dimensions using the Google benchmark library.

## Tests ##

All tests work by first constructing an instance of Eigen::Matrix, make sure that this instance is symmetric and constructing instances of SymmetricMatrix by passing the constructed Eigen::Matrix. Then any operation is performed for both the SymmetricMatrix and the Eigen::Matrix. If both operations yield the same result, the test is passed. In fact the all tests check if instances of SymmetricMatrix behave like symantically identical instances of Eigen::Matrix.

Three tests are includes:

**[fixed_fixed.cc](test/fixed_fixed.cc):** Tests operations on symmetric matrices of fixed dimension with symmetric matrices of fixed dimension. Several datatypes and matrix dimensions are tested.

**[fixed_dynamic.cc](test/fixed_fixed.cc):** Tests operations on symmetric matrices of fixed dimension with symmetric matrices of dynamic dimension. Several datatypes and matrix dimensions are tested.

**[dynamic_dynamic.cc](test/fixed_fixed.cc):** Tests operations on symmetric matrices of dynamic dimension with symmetric matrices of dynamic dimension. Several datatypes and matrix dimensions are tested.

