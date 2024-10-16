#include <timeseries_handler.h>
#include <iostream>
using namespace std;

int main() {
    cout << "Using vector..." << endl;
    run_vector();

    cout << "Using map..." << endl;
    run_map();

    return 0;
}
