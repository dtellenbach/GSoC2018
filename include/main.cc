#include <iostream>
#include "../benchmark/Stopwatch.hpp"
#include <random>
#include <eigen3/Eigen/Eigen>
#include "SymmetricMatrix.h"
#include <iomanip>


int main() {
    int maxsize = 7000;

    std::cout << "t0\tt1\tsize\n"; 
    for (int size = 1000; size <= maxsize; size += 500) {
        Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> mat = Eigen::MatrixXi::Random(size,size);
        

        SymmetricMatrix<int> symmat(mat);
    
        for (int i = 0; i < size; i++) {
            for (int j = i; j < size; j++) {
                mat(i,j) = mat(j,i);
            }
        }

        Stopwatch watch0, watch1;

        Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> res;
        SymmetricMatrix<int> res2;

        watch0.start();
        res = mat + mat;
        watch0.stop();
        
        watch1.start();
        res2 = symmat + symmat;
        watch1.stop();
        std::cout << watch0.elapsed<std::chrono::milliseconds>().count() 
                  << "\t" 
                  << watch1.elapsed<std::chrono::milliseconds>().count() << "\t"
                  << size <<"\n";
    }           
}