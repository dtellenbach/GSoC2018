#include <iostream>
#include "../benchmark/Stopwatch.hpp"
#include <random>
#include <eigen3/Eigen/Eigen>
#include "SymmetricMatrix.h"

int main() {


    Eigen::MatrixXi mat = Eigen::MatrixXi::Random(1000, 1000);
    
    SymmetricMatrix<int> dynamicmat(mat);
    SymmetricMatrix<int, 1000> staticmat(mat);

    Stopwatch watch0, watch1;

    watch0.start();
    dynamicmat = dynamicmat + dynamicmat;
    watch0.stop();
    watch1.start();
    staticmat = staticmat + staticmat;
    watch1.stop();

    std::cout << "t0 = " << watch0.elapsed<std::chrono::microseconds>().count() << std::endl;
    std::cout << "t1 = " << watch1.elapsed<std::chrono::microseconds>().count() << std::endl;
}

