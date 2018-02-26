/*******************************************************************************
 *  This file is part of the evaluation test of the Google Summer of Code 2018 *
 *  project "Faster Matrix Algebra for ATLAS".                                 *
 *                                                                             *
 *  David A. Tellenbach <tellenbach@cip.ifi.lmu.de>                            *
 *                                                                             *
 *  Benchmark - Access                                                         *
 *  Time consumption of accessing all elements of an instance of               * 
 *  SymmetricMatrix and Eigen::Matrix for different dimensions.                *
 ******************************************************************************/

#include <iostream>

#include <SymmetricMatrix.h>
#include <eigen3/Eigen/Eigen>
#include "Stopwatch.h"

int main() {
    const int maxDim = 50000;
    uint64_t sum = 0;

    std::cout << "Size\tEigen::Matrix\tSymmetricMatrix\n"
              << "***************************************\n";
    for (int dim = 500; dim <= maxDim; dim += 500) {
        Eigen::MatrixXi eigenmat = Eigen::MatrixXi::Random(dim, dim);
        SymmetricMatrixXi symmat = SymmetricMatrixXi::Random(dim);

        Stopwatch watch0, watch1;

        // Eigen::Matrix
        watch0.start();
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                sum += eigenmat(i, j);
            }
        }
        watch0.stop();

        // SymmetricMatrix
        watch1.start();
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                sum += symmat(i, j);
            }
        }
        watch1.stop();
        std::cout << dim << "\t" 
                  << watch0.elapsed<std::chrono::milliseconds>().count() 
                  << "ms\t\t"
                  << watch1.elapsed<std::chrono::milliseconds>().count() 
                  << "ms\n";
    }
    printf("%llu\n", sum); // To prevent compiler optimization
}
