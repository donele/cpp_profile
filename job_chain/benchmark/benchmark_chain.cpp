#include <string>
#include <benchmark/benchmark.h>
#include <job_chain.h>
using namespace std;

const string file1 = "input_few.txt";

static void BM_vector_few(benchmark::State& state) {
    for(auto _ : state) {
        process_jobs_vector(file1);
    }
}
BENCHMARK(BM_vector_few)->Iterations(2);


static void BM_map_vector_few(benchmark::State& state) {
    for(auto _ : state) {
        process_jobs_map_vector(file1);
    }
}
BENCHMARK(BM_map_vector_few)->Iterations(2);


//static void BM_map_few(benchmark::State& state) {
//    for(auto _ : state) {
//        process_jobs_map(file1);
//    }
//}
//BENCHMARK(BM_map_few)->Iterations(2);


static void BM_unordered_map_few(benchmark::State& state) {
    for(auto _ : state) {
        process_jobs_unordered_map(file1);
    }
}
BENCHMARK(BM_unordered_map_few)->Iterations(2);


const string file2 = "input_many.txt";

static void BM_vector_many(benchmark::State& state) {
    for(auto _ : state) {
        process_jobs_vector(file2);
    }
}
BENCHMARK(BM_vector_many)->Iterations(1);


static void BM_map_many(benchmark::State& state) {
    for(auto _ : state) {
        process_jobs_map(file2);
    }
}
BENCHMARK(BM_map_many)->Iterations(1);


static void BM_unordered_map_many(benchmark::State& state) {
    for(auto _ : state) {
        process_jobs_unordered_map(file2);
    }
}
BENCHMARK(BM_unordered_map_many)->Iterations(1);


static void BM_map_vector_many(benchmark::State& state) {
    for(auto _ : state) {
        process_jobs_map_vector(file2);
    }
}
BENCHMARK(BM_map_vector_many)->Iterations(1);


BENCHMARK_MAIN();
