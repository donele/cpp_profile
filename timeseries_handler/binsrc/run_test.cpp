#include <scm_timeseries.h>
#include <iostream>
using namespace std;

void run_test(TimeSeries* ts) {
    cout << "add " << 0 << " " << 1.0 << endl;
    ts->Add(0, 1.0);
    cout << "0 " << ts->Get(0) << endl;

    cout << "add " << 10 << " " << 2.0 << endl;
    ts->Add(10, 2.0);
    cout << "9 " << ts->Get(9) << endl;
    cout << "10 " << ts->Get(10) << endl;
    cout << "11 " << ts->Get(11) << endl;

    cout << "add " << 5000 << " " << 3.0 << endl;
    ts->Add(5000, 3.0);
    cout << "0 " << ts->Get(0) << endl;
    cout << "4999 " << ts->Get(4999) << endl;
    cout << "5000 " << ts->Get(5000) << endl;
    cout << "5001 " << ts->Get(5001) << endl;
    cout << "20000 " << ts->Get(20000) << endl;

    cout << "add " << 23456 << " " << 4.0 << endl;
    ts->Add(23456, 4.0);
    cout << "18456 " << ts->Get(18456) << endl;
    cout << "23455 " << ts->Get(23455) << endl;
    cout << "23456 " << ts->Get(23456) << endl;
    cout << "23457 " << ts->Get(23457) << endl;
}

int main() {
    cout << "Using map..." << endl;
    TimeSeries* ts = new TimeSeriesMap(5000);
    run_test(ts);
    delete ts;

    cout << "Using vector..." << endl;
    TimeSeries* ts2 = new TimeSeriesVector(5000);
    run_test(ts2);
    delete ts2;

    return 0;
}
