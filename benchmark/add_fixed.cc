/*******************************************************************************
 *  This file is part of the evaluation test of the Google Summer of Code 2018 *
 *  project "Faster Matrix Algebra for ATLAS".                                 *
 *                                                                             *
 *  David A. Tellenbach <tellenbach@cip.ifi.lmu.de>                            *
 *                                                                             *
 *  Benchmark - Addition Fixed                                                 *
 *  Measures the time consumption of addition of instances of SymmetricMatrix  *     
 *  and Eigen::Matrix for several fixed dimensions.                            *
 ******************************************************************************/

#include <iostream>

#include <SymmetricMatrix.h>
#include <eigen3/Eigen/Eigen>
#include "Stopwatch.h"

template<typename Scalar, int Dimension, int Steps>
class Add_Fixed {
 public:
    void run() {
        Stopwatch watch0, watch1;
        {
            Eigen::Matrix<Scalar, Dimension, Dimension> eigenmat1 
                = Eigen::Matrix<Scalar, Dimension, Dimension>::Random();
            Eigen::Matrix<Scalar, Dimension, Dimension> eigenmat2 
                = Eigen::Matrix<Scalar, Dimension, Dimension>::Random();
            Eigen::Matrix<Scalar, Dimension, Dimension> result;

            watch0.start();
            result = eigenmat1 + eigenmat2;
            watch0.stop();
        }
        {
            SymmetricMatrix<int, 10> symmat1 = SymmetricMatrix<int, 10>::Random();
            SymmetricMatrix<int, 10> symmat2 = SymmetricMatrix<int, 10>::Random();
            SymmetricMatrix<int, 10> result;

            watch1.start();
            result = symmat1 + symmat2;
            watch1.stop();
        }
        std::cout << Dimension << "\t"
                << watch0.elapsed<std::chrono::nanoseconds>().count() 
                << "ns\t\t"
                << watch1.elapsed<std::chrono::nanoseconds>().count() 
                << "ns\n";
        Add_Fixed<Scalar, Dimension-Steps, Steps> add_fixed;
        
        add_fixed.run();
    }
};

template<typename Scalar, int Steps>
class Add_Fixed<Scalar, 0, Steps> {
 public:
    void run() {
        
    }
};

int main() {
    std::cout << "Size\tEigen::Matrix\tSymmetricMatrix\n"
              << "***************************************\n";;

    Add_Fixed<int, 100, 10> benchmark;
    benchmark.run();
    

}