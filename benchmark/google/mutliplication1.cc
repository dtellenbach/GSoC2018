#include <benchmark/benchmark.h>
#include "../../include/symmat.h"
#include "../../include/eigen3/Eigen/Eigen"

static void BM_SymMatAdd(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> mat = Eigen::MatrixXi::Random(state.range(0),state.range(0));
        SymmetricMatrix<int> symmat(mat);
        SymmetricMatrix<int> res;
        state.ResumeTiming();
        res = symmat * symmat;
    }
}

static void BM_EigenMatAdd(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> mat = Eigen::MatrixXi::Random(state.range(0),state.range(0));
        Eigen::MatrixXi res;
        state.ResumeTiming();
        res = mat * mat;
        
    }
}

BENCHMARK(BM_SymMatAdd) 
         ->Args({1000})
         ->Args({2000})
         ->Args({3000});
        //  ->Args({4000})
        //  ->Args({5000})
        //  ->Args({6000})
        //  ->Args({7000})
        //  ->Args({8000})
        //  ->Args({9000})
        //  ->Args({10000});
 

BENCHMARK(BM_EigenMatAdd) 
         ->Args({1000})
         ->Args({2000})
         ->Args({3000});
        //  ->Args({4000})
        //  ->Args({5000})
        //  ->Args({6000})
        //  ->Args({7000})
        //  ->Args({8000})
        //  ->Args({9000})
        //  ->Args({10000});

BENCHMARK_MAIN();