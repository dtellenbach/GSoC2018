/*******************************************************************************
 *  This file is part of the evaluation test of the Google Summer of Code 2018 *
 *  project "Faster Matrix Algebra for ATLAS".                                 *
 *                                                                             *
 *  David A. Tellenbach <tellenbach@cip.ifi.lmu.de>                            *
 *                                                                             *
 *  Benchmark - add_fixed                                                      *
 *  Addition of matrices with dynamic dimension                                *
 ******************************************************************************/

#include <benchmark/benchmark.h>

#include <SymmetricMatrix.h>
#include <eigen3/Eigen/Eigen>

template<typename Scalar>
void BM_AddEigenEigen(benchmark::State& state) {
    // This is for plotting purpose
    state.counters["Dimension"] = state.range(0);
    state.counters["Ingroup"] = 0;

    Eigen::Matrix<Scalar, -1, -1> mat1
        = Eigen::Matrix<Scalar, -1, -1>::Random(state.range(0), state.range(0));
    Eigen::Matrix<Scalar, -1, -1> mat2
        = Eigen::Matrix<Scalar, -1, -1>::Random(state.range(0), state.range(0));
    Eigen::Matrix<Scalar, -1, -1> result;

    for (auto _ : state) {
        benchmark::DoNotOptimize(result = mat1 + mat2);
    }
    
}

template<typename Scalar>
void BM_AddSymSym(benchmark::State& state) {
    // This is for plotting purpose
    state.counters["Dimension"] = state.range(0);
    state.counters["Ingroup"] = 1;

    SymmetricMatrix<Scalar> mat1
        = SymmetricMatrix<Scalar>::Random(state.range(0));
    SymmetricMatrix<Scalar> mat2
        = SymmetricMatrix<Scalar>::Random(state.range(0));
    SymmetricMatrix<Scalar> result;

    for (auto _ : state) {
        benchmark::DoNotOptimize(result = mat1 + mat2);
    }
}

template<typename Scalar>
void BM_AddSymEigen(benchmark::State& state) {
    // This is for plotting purpose
    state.counters["Dimension"] = state.range(0);
    state.counters["Ingroup"] = 2;

    SymmetricMatrix<Scalar> mat1
        = SymmetricMatrix<Scalar>::Random(state.range(0));
    Eigen::Matrix<Scalar, -1, -1> mat2
        = Eigen::Matrix<Scalar, -1, -1>::Random(state.range(0), state.range(0));
    Eigen::Matrix<Scalar, -1, -1> result;

    for (auto _ : state) {
        benchmark::DoNotOptimize(result = mat1 + mat2);
    }
}

BENCHMARK_TEMPLATE(BM_AddEigenEigen, int) 
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

BENCHMARK_TEMPLATE(BM_AddSymSym, int) 
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

BENCHMARK_TEMPLATE(BM_AddSymEigen, int) 
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