/*******************************************************************************  
 *  Google Summer of Code - Faster Matrix Multiplication for ATLAS             *
 *  David A. Tellenbach <tellenbach@cip.ifi.lmu.de> - 2018-02-20               *
 *                                                                             *
 *  Example 2 - Basic arithmetic operations                                    *
 *  Topics covered: > Construct a symmetric matrix from std::vector            *
 *                  > Perform addition for two symmetric matrices              *
 *                  > Perform multiplication for two symmetric matrices        *
 ******************************************************************************/

#include "../include/symmat.h"
#include "../include/eigen3/Eigen/Eigen"
#include <iostream>
#include <vector>

int main() {
    // Construct an Eigen::Matrix with dynamic size, fill it with elements
    // and construct a symmetric matrix from it
    Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> mat(3,3);

    mat << 1,2,3,
           1,2,3,
           1,2,3;

    SymMat<int> symmat(mat);

    // Create an std::vector<int> and construct a symmetric matrix out of it.
    // The dimension of the matrix is calculated automatically from the numer
    // of elements the vector contains. However, passing it is optional.
    std::vector<int> vec = {2,2,2,3,3,4};
    SymMat<int> symmat2(vec);

    // Print both symmetric matrices
    std::cout << "Symmat:\n" << symmat << "\n"
              << "Symmat2:\n" << symmat2 << "\n";

    // Perform addition, the result is again symmetric
    auto sum = symmat + symmat2;
    std::cout << "Sum:\n" << sum << "\n";

    // Perform multiplication, the result is in general not symmetric and 
    // therefore of type Eigen::Matrix
    auto product = symmat * symmat2;
    std::cout << "Product:\n" << product << "\n";
}