#include <iostream>
#include <datell/Stopwatch.hpp>
#include <random>
#include <eigen3/Eigen/Eigen>
#include "symmat.h"


int main() {
    const int size = 2000;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(-300, 300);

    Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> mat(size,size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mat(i,j) = dist(rd);
        }
    }

    SymMat<int> symmat(mat);
    Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> symmat2(size,size);
    symmat2 = mat;
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            symmat2(i,j) = symmat2(j,i);
        }
    }


    printf("Initialization finished...\n");
    Stopwatch watch0, watch1;

    Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> res;
    SymMat<int> res2;

    watch0.start();
    printf("Using Eigen::Matrix...\n");
    res = symmat2 * symmat2;
    watch0.stop();
    std::cout << "t0 = " << watch0.elapsed<std::chrono::milliseconds>().count() 
              << "ms\n";
    watch1.start();
    printf("Using SymMat...\n");
    res = symmat * symmat;
    watch1.stop();
    std::cout << "t1 = " << watch1.elapsed<std::chrono::milliseconds>().count() 
              << "ms\n";
    
}