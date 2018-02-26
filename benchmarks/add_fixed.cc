/*******************************************************************************
 *  This file is part of the evaluation test of the Google Summer of Code 2018 *
 *  project "Faster Matrix Algebra for ATLAS".                                 *
 *                                                                             *
 *  David A. Tellenbach <tellenbach@cip.ifi.lmu.de>                            *
 *                                                                             *
 *  Benchmark - add_fixed                                                      *
 *  Addition of matrices with fixed dimension                                  *
 ******************************************************************************/

#include <benchmark/benchmark.h>

#include <SymmetricMatrix.h>
#include <eigen3/Eigen/Eigen>

template<typename Scalar, int Dimension>
void BM_AddEigenEigen(benchmark::State& state) {
    Eigen::Matrix<Scalar, Dimension, Dimension> mat1 
        = Eigen::Matrix<Scalar, Dimension, Dimension>::Random();
    Eigen::Matrix<Scalar, Dimension, Dimension> mat2 
        = Eigen::Matrix<Scalar, Dimension, Dimension>::Random();
    Eigen::Matrix<Scalar, Dimension, Dimension> result;

    for (auto _ : state) {
        benchmark::DoNotOptimize(result = mat1 + mat2);
    }
}

template<typename Scalar, int Dimension>
void BM_AddSymSym(benchmark::State& state) {
    SymmetricMatrix<Scalar, Dimension> mat1 
        = SymmetricMatrix<Scalar, Dimension>::Random();
    SymmetricMatrix<Scalar, Dimension> mat2 
        = SymmetricMatrix<Scalar, Dimension>::Random();
    SymmetricMatrix<Scalar, Dimension> result;

    for (auto _ : state) {
        benchmark::DoNotOptimize(result = mat1 + mat2);
    }
}

template<typename Scalar, int Dimension>
void BM_AddSymEigen(benchmark::State& state) {
    SymmetricMatrix<Scalar, Dimension> mat1 
            = SymmetricMatrix<Scalar, Dimension>::Random();
    Eigen::Matrix<Scalar, Dimension, Dimension> mat2 
            = Eigen::Matrix<Scalar, Dimension, Dimension>::Random();
   Eigen::Matrix<Scalar, Dimension, Dimension> result;

    for (auto _ : state) {
        benchmark::DoNotOptimize(result = mat1 + mat2);
    }
}

BENCHMARK_TEMPLATE(BM_AddEigenEigen, int, 10);
BENCHMARK_TEMPLATE(BM_AddEigenEigen, int, 20);
BENCHMARK_TEMPLATE(BM_AddEigenEigen, int, 30);
BENCHMARK_TEMPLATE(BM_AddEigenEigen, int, 40);
BENCHMARK_TEMPLATE(BM_AddEigenEigen, int, 50);
BENCHMARK_TEMPLATE(BM_AddEigenEigen, int, 60);
BENCHMARK_TEMPLATE(BM_AddEigenEigen, int, 70);
BENCHMARK_TEMPLATE(BM_AddEigenEigen, int, 80);
BENCHMARK_TEMPLATE(BM_AddEigenEigen, int, 90);
BENCHMARK_TEMPLATE(BM_AddEigenEigen, int, 100);

BENCHMARK_TEMPLATE(BM_AddSymSym, int, 10);
BENCHMARK_TEMPLATE(BM_AddSymSym, int, 20);
BENCHMARK_TEMPLATE(BM_AddSymSym, int, 30);
BENCHMARK_TEMPLATE(BM_AddSymSym, int, 40);
BENCHMARK_TEMPLATE(BM_AddSymSym, int, 50);
BENCHMARK_TEMPLATE(BM_AddSymSym, int, 60);
BENCHMARK_TEMPLATE(BM_AddSymSym, int, 70);
BENCHMARK_TEMPLATE(BM_AddSymSym, int, 80);
BENCHMARK_TEMPLATE(BM_AddSymSym, int, 90);
BENCHMARK_TEMPLATE(BM_AddSymSym, int, 100);

BENCHMARK_TEMPLATE(BM_AddSymEigen, int, 10);
BENCHMARK_TEMPLATE(BM_AddSymEigen, int, 20);
BENCHMARK_TEMPLATE(BM_AddSymEigen, int, 30);
BENCHMARK_TEMPLATE(BM_AddSymEigen, int, 40);
BENCHMARK_TEMPLATE(BM_AddSymEigen, int, 50);
BENCHMARK_TEMPLATE(BM_AddSymEigen, int, 60);
BENCHMARK_TEMPLATE(BM_AddSymEigen, int, 70);
BENCHMARK_TEMPLATE(BM_AddSymEigen, int, 80);
BENCHMARK_TEMPLATE(BM_AddSymEigen, int, 90);
BENCHMARK_TEMPLATE(BM_AddSymEigen, int, 100);

BENCHMARK_MAIN();