/*******************************************************************************
 *  This file is part of the evaluation test of the Google Summer of Code 2018 *
 *  project "Faster Matrix Algebra for ATLAS".                                 *
 *                                                                             *
 *  David A. Tellenbach <tellenbach@cip.ifi.lmu.de>                            *
 *                                                                             *
 *  Example 3 - Addition and Subtraction                                       *
 *  Topics covered: > Addition and subtraction for two instances of symmetric  * 
 *                    matrix                                                   *
 *                  > Addition and subtraction for symmetric matrices and      *
 *                    arbitrary matrices                                       *
 ******************************************************************************/

#include <iostream>
#include <SymmetricMatrix.h>
#include <eigen3/Eigen/Eigen>


int main() {
    // Matrices with fixed size
    // Create an instance of Eigen::Matrix
    Eigen::Matrix<int, 3, 3> eigenmat;
    eigenmat << 1,2,3,
                2,3,3,
                3,3,4;

    // Create symmetric matrices from eigenmat
    SymmetricMatrix3i symmat(eigenmat);

    // Addition of symmetric matrices
    SymmetricMatrix3i symadd = symmat + symmat;
    std::cout << "SymmetricMatrix = SymmetricMatrix + SymmetricMatrix\n";
    std::cout << symmat << "\n+\n" << symmat << "\n=\n" << symadd << "\n\n";

    // Subtraction of symmetric matrices
    SymmetricMatrix3i symsub = symadd - symmat;
    std::cout << "SymmetricMatrix = SymmetricMatrix - SymmetricMatrix\n";
    std::cout << symadd << "\n-\n" << symmat << "\n=\n" << symsub << "\n\n";

    // This also works with dynamically sized matrices. You can even mix 
    // dynamic and fixed size under some circumstances

    // Addition and subtraction also works with arbitrary matrices. The result
    // will be an instance of Eigen::Matrix
    std::cout << "Eigen::Matrix = SymmetricMatrix + Eigen::Matrix\n";
    Eigen::Matrix3i result = symmat + eigenmat;
    std::cout << symmat << "\n+\n" << eigenmat << "\n=\n" << result << "\n\n";

    // You currently can't do smoothing like eigenmat + symmat, since this would
    // require modification of the Eigen::Matrix class
}