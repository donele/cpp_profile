#include <string>
#include <benchmark/benchmark.h>
#include <job_chain.h>
using namespace std;

static void split_comma(benchmark::State& state) {
    int id = rand() % 10000;
    int runtime = rand() % 10000;
    int next = rand() % 10000;
    char buf[256];
    sprintf(buf, "%d,%d,%d", id, runtime, next);
    string s(buf);
    for(auto _ : state) {
        split_comma(s);
    }
}
BENCHMARK(split_comma);


static void split_comma_valid(benchmark::State& state) {
    int id = rand() % 10000;
    int runtime = rand() % 10000;
    int next = rand() % 10000;
    char buf[256];
    sprintf(buf, "%d,%d,%d", id, runtime, next);
    string s(buf);
    for(auto _ : state) {
        auto sp = split_comma(s);
        valid(sp);
    }
}
BENCHMARK(split_comma_valid);


static void parse_line(benchmark::State& state) {
    int id = rand() % 10000;
    int runtime = rand() % 10000;
    int next = rand() % 10000;
    char buf[256];
    sprintf(buf, "%d,%d,%d", id, runtime, next);
    string s(buf);
    for(auto _ : state) {
        parse_line(s);
    }
}
BENCHMARK(parse_line);


BENCHMARK_MAIN();
