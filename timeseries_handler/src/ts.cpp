#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <scm_timeseries.h>
using namespace std;

void run(TimeSeries* ts) {
    cout << "testing.." << endl;

    for(int i = 0; i < 1000000; ++i) {
        ts->Add(i*3, i);
        for(int j = 0; j < 10; ++j) {
            ts->Get(i*3 - j*176);
        }
    }
}

void run_map(bool verbose) {
    TimeSeries* ts = new TimeSeriesMap(5000);
    run(ts);
    delete ts;
}

void run_vector(bool verbose) {
    TimeSeries* ts = new TimeSeriesVector(5000);
    run(ts);
    delete ts;
}
