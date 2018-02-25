#include <benchmark/benchmark.h>
#include <SymmetricMatrix.h>
#include <eigen3/Eigen/Eigen>

// static void BM_SymAccess(benchmark::State& state) {
//     for (auto _ : state) {
//         state.PauseTiming();
//         SymmetricMatrixXi symmat = SymmetricMatrixXi::Random(state.range(0));
//         int sum = 0;
//         state.ResumeTiming();
//         for (int i = 0; i < state.range(0); ++i) {
//             for (int j = 0; j < state.range(0); ++j) {
//                 sum += symmat(i, j);
//             }
//         }
//     }
// }

static void BM_SymAccess(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        SymmetricMatrixXi symmat = SymmetricMatrixXi::Random(1000);
        int sum = 0;
        state.ResumeTiming();
        for (int i = 0; i < 1000; ++i) {
            for (int j = 0; j < 1000; ++j) {
                sum += symmat(i, j);
            }
        }
    }
}

BENCHMARK(BM_SymAccess) -> Unit(benchmark::kMillisecond);
        //  ->Args({1000})
        //  ->Args({2000})
        //  ->Args({3000})
        //  ->Args({4000})
        //  ->Args({5000})
        //  ->Args({6000})
        //  ->Args({7000})
        //  ->Args({8000})
        //  ->Args({9000})
        //  ->Args({10000});

BENCHMARK_MAIN();