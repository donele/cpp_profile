#include <string>
#include <benchmark/benchmark.h>
#include <timeseries_handler.h>
using namespace std;

static void BM_map(benchmark::State& state) {
    for(auto _ : state) {
        run_map();
    }
}
BENCHMARK(BM_map)->Iterations(2);


static void BM_vector(benchmark::State& state) {
    for(auto _ : state) {
        run_vector();
    }
}
BENCHMARK(BM_vector)->Iterations(2);


BENCHMARK_MAIN();
