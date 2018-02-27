/*******************************************************************************
 *  This file is part of the evaluation test of the Google Summer of Code 2018 *
 *  project "Faster Matrix Algebra for ATLAS".                                 *
 *                                                                             *
 *  David A. Tellenbach <tellenbach@cip.ifi.lmu.de>                            *
 *                                                                             *
 *  Example 2 - Basic arithmetic operations                                    *
 *  Topics covered: > Difference between matrices with fixed and with dynamic  * 
 *                    size                                                     *
 *                  > Typedefs for several classes of class template           * 
 *                    SymmetricMatrix                                          *
 *                  > Constructing symmetric matrices filled with random       *
 *                    values                                                   *
 ******************************************************************************/

#include <SymmetricMatrix.h>
#include <eigen3/Eigen/Eigen>
#include <iostream>


int main() {
    // The class template SymmetricMatrix<T, N> expects to template parameters:
    // The type of the elements and the dimension. A symmetric matrix of doubles
    // with dimension 3 can be created like this:
    SymmetricMatrix<double, 3> ssymmat;

    // The above matrix has fixed dimension 3. This allows to do a lot of work
    // at compile time. However if you want a more flexible matrix you can use
    // the special dimension Eigen::Dynamic. This is in fact the default
    // template parameter for the dimension.
    SymmetricMatrix<double> dsymmat;    // same as SymmetricMatrix<double,
                                        // Eigen::Dynamic> dsymmat;

    // According to the design of Eigen, there exist typedefs for a lot of
    // different concrete classes of SymmetricMatrix
    SymmetricMatrixXcd csymmat;     // Matrix of complex doubles with dynamic
                                    // dimension
    SymmetricMatrix2i isymmat;      // Matrix of ints with fixed dimension 2

    // In the above cases no element of the matrices is set. The dynamic sized
    // matrices have dimension 0 and nothing is stored. The fixed sized matrices
    // have allocated all memory but the values are not initialized and can
    // contain arbitrary values.

    // As shown in example1.cc a symmetric matrix can be constructed by passing
    // an instance of Eigen::Matrix. There also exists the possibility to
    // construct a symmetric matrix filled with random values
    SymmetricMatrix<double, 3> rndMatrix = SymmetricMatrix<double, 3>::Random();

    // In the dynamic case the dimension has to be passed as argument
    SymmetricMatrixXi rndDmatrix = SymmetricMatrixXi::Random(3);

    // Let's take a look at these matrices
    std::cout << "Random matrix filled with doubles:\n" << rndMatrix << "\n"
              << "Random matrix filled with ints:\n"   << rndDmatrix << "\n";
}
