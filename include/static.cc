#include <iostream>
#include "../benchmark/Stopwatch.hpp"
#include <random>
#include <eigen3/Eigen/Eigen>
#include "symmat.h"

int main() {
    Eigen::Matrix<int, 3, 3> mat;

    mat << 1,2,3,
           2,2,3,
           3,3,3;

    Eigen::Matrix<int, 3, 3> mat_;
    mat_ = mat + mat;

    SymmetricMatrix<int, 3> symmat(mat);

    std::cout << symmat << std::endl;
    std::cout << std::endl;
    

    SymmetricMatrix<int, 3> res = symmat + mat;
   
    std::cout << res;

    
}

