/******************************************************************************* 
 *  Google Summer of Code - Faster Matrix Multiplication for ATLAS             *
 *  David A. Tellenbach <tellenbach@cip.ifi.lmu.de> - 2018-02-20               *
 *                                                                             *
 *  Example 1 - Basics                                                         *
 *  Topics covered: > Construct a symmetric matrix from an Eigen::Matrix       *
 *                  > Print symmetric matrix onto console                      *
 *                  > Test if an Eigen::Matrix is symmetric or not             *
 ******************************************************************************/

#include "../include/SymmetricMatrix.h"
#include "../include/eigen3/Eigen/Eigen"
#include <iostream>

int main() {
    // Define a 3x3 Eigen::Matrix of dynamic size
    Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> mat(3, 3);

    // Fill the matrix with elements
    mat << 1,2,3,
           1,2,3,
           1,2,3;

    // Print the Eigen::Matrix
    std::cout << "Eigen::Matrix: \n";
    std::cout << mat << "\n\n";

    // Construct a symmetric matrix from the Eigen::Matrix given above
    SymmetricMatrix<int> symmat(mat);

    // Print the symmetric matrix
    std::cout << "Symmetric Matrix: \n";
    std::cout << symmat << "\n";

    // The symmetric matrix has been constructed although the Eigen::Matrix
    // was not symmetric. Only the upper triangular part was considered. If
    // you want to check ifs an Eigen::Matrix is symmetric you can do somethin
    // like this:
    if (SymmetricMatrix<int>::isSymmetric(mat)) {
        std::cout << "My Eigen::Matrix is symmetric\n";
    } else {
        std::cout << "My Eigen::Matrix is not symmetric\n";
    }
   
}