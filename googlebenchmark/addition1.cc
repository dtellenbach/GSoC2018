#include <benchmark/benchmark.h>
#include "../include/SymmetricMatrix.h"
#include "../include/eigen3/Eigen/Eigen"


static void BM_SymPlusSym(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> mat = Eigen::MatrixXi::Random(state.range(0),state.range(0));
        SymmetricMatrix<int> symmat(mat);
        SymmetricMatrix<int> res;
        state.ResumeTiming();
        res = symmat + symmat;
    }
}

static void BM_SymPlusEigen(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> mat = Eigen::MatrixXi::Random(state.range(0),state.range(0));
        SymmetricMatrix<int> symmat(mat);
        Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> res;
        state.ResumeTiming();
        res = symmat + mat;
    }
}

BENCHMARK(BM_SymPlusSym) -> Unit(benchmark::kMicrosecond)
         ->Args({1000})
         ->Args({2000})
         ->Args({3000})
         ->Args({4000})
         ->Args({5000})
         ->Args({6000})
         ->Args({7000})
         ->Args({8000})
         ->Args({9000})
         ->Args({10000});
 

BENCHMARK(BM_SymPlusEigen) -> Unit(benchmark::kMicrosecond)
         ->Args({1000})
         ->Args({2000})
         ->Args({3000})
         ->Args({4000})
         ->Args({5000})
         ->Args({6000})
         ->Args({7000})
         ->Args({8000})
         ->Args({9000})
         ->Args({10000});

BENCHMARK_MAIN();