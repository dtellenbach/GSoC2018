#include <iostream>
#include "../benchmark/Stopwatch.hpp"
#include <eigen3/Eigen/Eigen>
#include "SymmetricMatrix.h"

int main() {
    Eigen::MatrixXi eigenmat(3,3);

    eigenmat << 1,2,3,
                2,2,3,
                3,3,3;


    SymmetricMatrix<int> symmat(eigenmat);
    SymmetricMatrix<int> res = symmat + symmat;
    std::cout << res<< "should be the same as\n" << (eigenmat + eigenmat) << std::endl;
    res = symmat * symmat;
    std::cout << res<< "should be the same as\n" << (eigenmat * eigenmat) << std::endl;
    res = symmat - symmat;
    std::cout << res<< "should be the same as\n" << (eigenmat - eigenmat) << std::endl;
}