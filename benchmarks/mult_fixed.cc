/*******************************************************************************
 *  This file is part of the evaluation test of the Google Summer of Code 2018 *
 *  project "Faster Matrix Algebra for ATLAS".                                 *
 *                                                                             *
 *  David A. Tellenbach <tellenbach@cip.ifi.lmu.de>                            *
 *                                                                             *
 *  Benchmark - add_fixed                                                      *
 *  Multiplication of matrices with fixed dimension                            *
 ******************************************************************************/

#include <benchmark/benchmark.h>

#include <SymmetricMatrix.h>
#include <eigen3/Eigen/Eigen>

template<typename Scalar, int Dimension>
void BM_MultEigenEigen(benchmark::State& state) {
    Eigen::Matrix<Scalar, Dimension, Dimension> mat1 
        = Eigen::Matrix<Scalar, Dimension, Dimension>::Random();
    Eigen::Matrix<Scalar, Dimension, Dimension> mat2 
        = Eigen::Matrix<Scalar, Dimension, Dimension>::Random();
    Eigen::Matrix<Scalar, Dimension, Dimension> result;

    for (auto _ : state) {
        benchmark::DoNotOptimize(result = mat1 * mat2);
    }
}

template<typename Scalar, int Dimension>
void BM_MultSymSym(benchmark::State& state) {
    SymmetricMatrix<Scalar, Dimension> mat1 
        = SymmetricMatrix<Scalar, Dimension>::Random();
    SymmetricMatrix<Scalar, Dimension> mat2 
        = SymmetricMatrix<Scalar, Dimension>::Random();
    Eigen::Matrix<Scalar, Dimension, Dimension> result;

    for (auto _ : state) {
        benchmark::DoNotOptimize(result = mat1 * mat2);
    }
}

template<typename Scalar, int Dimension>
void BM_MultSymEigen(benchmark::State& state) {
    SymmetricMatrix<Scalar, Dimension> mat1 
            = SymmetricMatrix<Scalar, Dimension>::Random();
    Eigen::Matrix<Scalar, Dimension, Dimension> mat2 
            = Eigen::Matrix<Scalar, Dimension, Dimension>::Random();
   Eigen::Matrix<Scalar, Dimension, Dimension> result;

    for (auto _ : state) {
        benchmark::DoNotOptimize(result = mat1 * mat2);
    }
}

BENCHMARK_TEMPLATE(BM_MultEigenEigen, int, 10);
BENCHMARK_TEMPLATE(BM_MultEigenEigen, int, 20);
BENCHMARK_TEMPLATE(BM_MultEigenEigen, int, 30);
BENCHMARK_TEMPLATE(BM_MultEigenEigen, int, 40);
BENCHMARK_TEMPLATE(BM_MultEigenEigen, int, 50);
BENCHMARK_TEMPLATE(BM_MultEigenEigen, int, 60);
BENCHMARK_TEMPLATE(BM_MultEigenEigen, int, 70);
BENCHMARK_TEMPLATE(BM_MultEigenEigen, int, 80);
BENCHMARK_TEMPLATE(BM_MultEigenEigen, int, 90);
BENCHMARK_TEMPLATE(BM_MultEigenEigen, int, 100);

BENCHMARK_TEMPLATE(BM_MultSymSym, int, 10);
BENCHMARK_TEMPLATE(BM_MultSymSym, int, 20);
BENCHMARK_TEMPLATE(BM_MultSymSym, int, 30);
BENCHMARK_TEMPLATE(BM_MultSymSym, int, 40);
BENCHMARK_TEMPLATE(BM_MultSymSym, int, 50);
BENCHMARK_TEMPLATE(BM_MultSymSym, int, 60);
BENCHMARK_TEMPLATE(BM_MultSymSym, int, 70);
BENCHMARK_TEMPLATE(BM_MultSymSym, int, 80);
BENCHMARK_TEMPLATE(BM_MultSymSym, int, 90);
BENCHMARK_TEMPLATE(BM_MultSymSym, int, 100);

BENCHMARK_TEMPLATE(BM_MultSymEigen, int, 10);
BENCHMARK_TEMPLATE(BM_MultSymEigen, int, 20);
BENCHMARK_TEMPLATE(BM_MultSymEigen, int, 30);
BENCHMARK_TEMPLATE(BM_MultSymEigen, int, 40);
BENCHMARK_TEMPLATE(BM_MultSymEigen, int, 50);
BENCHMARK_TEMPLATE(BM_MultSymEigen, int, 60);
BENCHMARK_TEMPLATE(BM_MultSymEigen, int, 70);
BENCHMARK_TEMPLATE(BM_MultSymEigen, int, 80);
BENCHMARK_TEMPLATE(BM_MultSymEigen, int, 90);
BENCHMARK_TEMPLATE(BM_MultSymEigen, int, 100);

BENCHMARK_MAIN();