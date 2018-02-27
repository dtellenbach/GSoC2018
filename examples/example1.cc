/*******************************************************************************
 *  This file is part of the evaluation test of the Google Summer of Code 2018 *
 *  project "Faster Matrix Algebra for ATLAS".                                 *
 *                                                                             *
 *  David A. Tellenbach <tellenbach@cip.ifi.lmu.de>                            *
 *                                                                             *
 *  Example 1 - Basics                                                         *
 *  Topics covered: > Construct a symmetric matrix from an Eigen::Matrix of    *
 *                    fixed size                                               *
 *                  > Print an instance of SymmetricMatrix into console        *
 *                  > Constructing symmetric matrices filled with random       *
 *                    values                                                   *
 *                  > Access elements of the symmetric matrix directly and     *
 *                    change their value                                       *
 ******************************************************************************/

#include <SymmetricMatrix.h>
#include <eigen3/Eigen/Eigen>
#include <iostream>


int main() {
    // Define a 3x3 Eigen::Matrix
    Eigen::Matrix<int, 3, 3> eigenmat;

    // Fill the matrix with elements
    eigenmat << 1, 2, 3,
                1, 2, 3,
                1, 2, 3;

    // Print the Eigen::Matrix
    std::cout << "Eigen::Matrix: \n";
    std::cout << eigenmat << "\n\n";

    // Construct a symmetric matrix from the Eigen::Matrix given above
    SymmetricMatrix<int, 3> symmat(eigenmat);

    // Print the symmetric matrix
    std::cout << "Symmetric Matrix: \n";
    std::cout << symmat << "\n";

    // The symmetric matrix has been constructed although the Eigen::Matrix
    // was not symmetric. Only the upper triangular part was considered. If
    // you want to check ifs an Eigen::Matrix is symmetric you can do something
    // like this:
    if (SymmetricMatrix<int, 3>::isSymmetric(eigenmat)) {
        std::cout << "My Eigen::Matrix is symmetric\n";
    } else {
        std::cout << "My Eigen::Matrix is not symmetric\n";
    }

    // You can access elements of a symmetric matrix directly using the
    // overloaded operator (). In facts this returns a reference to the value
    // and is therefore an assignable expression
    std::cout << "symmat(1, 2) = " << symmat(1, 2) << "\n"
              << "symmat(2, 1) = " << symmat(2, 1) << "\n";
    symmat(1, 2) = 42;
    std::cout << "symmat(1, 2) = " << symmat(1, 2) << "\n"
              << "symmat(2, 1) = " << symmat(2, 1) << "\n";
}
