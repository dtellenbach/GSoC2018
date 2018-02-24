#include <iostream>
#include <datell/Stopwatch.hpp>
#include <random>
#include <vector>
#include <thread>
#include <eigen3/Eigen/Eigen>
#include "SymmetricMatrix.h"

int main() {
    
    const int size = 500500;
    // const int size = 1000;
    
    std::vector<int> vec;


    for (int j = 0; j < size; j++) {
        vec.push_back(j);
    }
    
    SymmetricMatrix<int> symmat(vec);

    std::cout << symmat.dim() << std::endl;
    // free(vec);
    
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    // for (int i = 0; i < 1000; i++) {
    //     for (int j = 0; j < 1000; j++) {
    //         symmat(i,j);
    //     }
    // }
   
}