/*******************************************************************************
 *  This file is part of the evaluation test of the Google Summer of Code 2018 *
 *  project "Faster Matrix Algebra for ATLAS".                                 *
 *                                                                             *
 *  David A. Tellenbach <tellenbach@cip.ifi.lmu.de>                            *
 *                                                                             *
 *  Benchmark - mult_fixed                                                     *
 *  Multiplication of matrices with dynamic dimension                          *
 ******************************************************************************/

#include <benchmark/benchmark.h>

#include <SymmetricMatrix.h>
#include <eigen3/Eigen/Eigen>

template<typename Scalar>
void BM_MultEigenEigen(benchmark::State& state) {
    Eigen::Matrix<Scalar, -1, -1> mat1
        = Eigen::Matrix<Scalar, -1, -1>::Random(state.range(0), state.range(0));
    Eigen::Matrix<Scalar, -1, -1> mat2
        = Eigen::Matrix<Scalar, -1, -1>::Random(state.range(0), state.range(0));
    Eigen::Matrix<Scalar, -1, -1> result;

    for (auto _ : state) {
        benchmark::DoNotOptimize(result = mat1 * mat2);
    }
    
}

template<typename Scalar>
void BM_MultSymSym(benchmark::State& state) {
    SymmetricMatrix<Scalar> mat1
        = SymmetricMatrix<Scalar>::Random(state.range(0));
    SymmetricMatrix<Scalar> mat2
        = SymmetricMatrix<Scalar>::Random(state.range(0));
    SymmetricMatrix<Scalar> result;

    for (auto _ : state) {
        benchmark::DoNotOptimize(result = mat1 * mat2);
    }
}

template<typename Scalar>
void BM_MultSymEigen(benchmark::State& state) {
    SymmetricMatrix<Scalar> mat1
        = SymmetricMatrix<Scalar>::Random(state.range(0));
    Eigen::Matrix<Scalar, -1, -1> mat2
        = Eigen::Matrix<Scalar, -1, -1>::Random(state.range(0), state.range(0));
    Eigen::Matrix<Scalar, -1, -1> result;

    for (auto _ : state) {
        benchmark::DoNotOptimize(result = mat1 * mat2);
    }
}

BENCHMARK_TEMPLATE(BM_MultEigenEigen, int) -> Unit(benchmark::kMillisecond)
    -> Args({1000})
    -> Args({2000})
    -> Args({3000})
    -> Args({4000})
    -> Args({5000})
    -> Args({6000})
    -> Args({7000})
    -> Args({8000})
    -> Args({9000})
    -> Args({10000});

BENCHMARK_TEMPLATE(BM_MultSymSym, int) -> Unit(benchmark::kMillisecond)
    -> Args({1000})
    -> Args({2000})
    -> Args({3000})
    -> Args({4000})
    -> Args({5000})
    -> Args({6000})
    -> Args({7000})
    -> Args({8000})
    -> Args({9000})
    -> Args({10000});

BENCHMARK_TEMPLATE(BM_MultSymEigen, int) -> Unit(benchmark::kMillisecond)
    -> Args({1000})
    -> Args({2000})
    -> Args({3000})
    -> Args({4000})
    -> Args({5000})
    -> Args({6000})
    -> Args({7000})
    -> Args({8000})
    -> Args({9000})
    -> Args({10000});

BENCHMARK_MAIN();