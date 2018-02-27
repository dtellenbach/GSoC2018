/*******************************************************************************
 *  This file is part of the evaluation test of the Google Summer of Code 2018 *
 *  project "Faster Matrix Algebra for ATLAS".                                 *
 *                                                                             *
 *  David A. Tellenbach <tellenbach@cip.ifi.lmu.de>                            *
 *                                                                             *
 *  Example 4 - Multiplication                                                 *
 *  Topics covered: > Multiplication of two instances of symmetric matrix      *
 *                  > Multiplication of symmetric and arbitrary matrices       *
 ******************************************************************************/

#include <SymmetricMatrix.h>
#include <eigen3/Eigen/Eigen>
#include <iostream>

int main() {
    // Create an instance of Eigen::Matrix and fill it with values
    Eigen::MatrixXd eigenmat(3, 3);
    eigenmat << 1.0, 2.0, 3.0,
                2.0, 3.0, 4.0,
                3.0, 4.0, 5.0;

    // Create symmetric matrices by passing eigenmat
    SymmetricMatrixXd dsymmat(eigenmat);    // Dynamic size
    SymmetricMatrix3d ssymmat(eigenmat);    // Fixed size

    // Multiply both symmetric matrices. The result will be Eigen::Matrix
    Eigen::MatrixXd res = ssymmat * dsymmat;
    std::cout << "Eigen::Matrix = SymmetricMatrix * SymmetricMatrix\n";
    std::cout << ssymmat << "\n*\n" << dsymmat << "\n=\n" << res << "\n\n";

    // Multiply the symmetric matrix and the Eigen::Matrix
    res = ssymmat * eigenmat;
    std::cout << "Eigen::Matrix = SymmetricMatrix * EigenMatrix\n";
    std::cout << ssymmat << "\n*\n" << dsymmat << "\n=\n" << res << "\n\n";
}
