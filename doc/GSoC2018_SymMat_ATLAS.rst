Google Summer of Code - Faster Matrix Multiplication for ATLAS - Evaluation Test
================================================================================



This documents gives an overview on how I solved the evaluation test for 2018's
Google Summer of Code project *Faster Matrix Algebra for ATLAS*.

Task
----

effef

Specification
^^^^^^^^^^^^^

The task was to design a standalone matrix class for handling symmetric matrices, i.e. square matrices of a dimension :math:`n` for that the following holds:

.. math::

    \forall 0 \le i, j \le n ~\alpha_{ij} = \alpha{ji}

The class should fulfill the following specifications:
    - Only the upper triangular part of the matrix should be stored
    - A constructor to build a symmetric matrix from an arbitrary matrix of type ``Eigen::Matrix`` must be contained
    - Accessor functions should reflect the symmetric nature of the matrix
    - The class must contain functions for addition and substraction of both symmetric with symmetric and arbitrary with arbitrary matrices
    - The class must contain a functions for multipliying both symmetric with symmetric and arbitrary with arbitrary matrices

The code should compile on an ordinary Linux system using C++11 and clang or gcc.

Design goals
^^^^^^^^^^^^

While creating the matrix class, I tried to focus on the following design goals:

#. Fullfill the specification
#. Use overloaded operators instead of standalone functions, i.e., provide functionality to peform ``symmat1 + symmat2`` instead of ``add(symmat1, symmat2)``
#. Try to decrease memory consumption in compare to use a matrix of type ``Eigen::Matrix``
#. Try to increase time performance in compare to use a matrix of type ``Eigen::Matrix```
#. Use compile-time functionality when handling small matrices (this reflects the design of Eigen)

Implementation
--------------

All specifications have been fulfilled. In particular the following is contained. The class ``SymmetricMatrix`` is a class template that takes use of the following template parameters:

``typename Scalar``
    A scalar type like ``int``, ``double`` or ``std::complex<T>`` that represents the type of the matrix elements.
``int Dimension = Eigen::Dynamic``
    The dimension of the symmetric matrix. If no dimension is specified, the value ``Eigen::Dynamic`` is used. Defining a dimension ca heavily increase performance since a lot of operations can be performed at compile-time. However, this allocates memory on the stack and is therefore not well-suited for large matrices.
``StorageMode = RowMajor```
    The storage type of the matrix. This is described in detail in the next section. The default value is ``RowMajor``.

Storage
^^^^^^^

One design goal was to store only the upper triangular matrix. By doing this, all :math:`n^2` elements of an :math:`n\text{-dimensional}` matrix can described by storing only

.. math::
    \frac{n(n+1)}{2}

elements.

In the default case of the ``Eigen::Dynamic`` template parameter, the elements are stored in ``std::vector<T>`` which is efficently resizeable and can achieve a performance similar to ``T*``.

In the case of a fixed dimension, the elements are stored in ``std::array<T, N>`` which cannot be resized but has a better performance since a lot can be done during the compilation process.

Using the template parameter ``StorageMode`` which can have the values ``RowMajor`` or ``ColumnMajor``, the storage order of the elements in the underlying container can be determined.

``RowMajor`` stores the elements like this:

.. image:: img/RowMajor.pdf

The storing order can be significant for the performance of operations. Since the C++ standard guarantees the underlying containers to allocate a continuous memory block, the storage order will directly determine how elements are loaded into cache.

Accessing elements
^^^^^^^^^^^^^^^^^^

To access element

