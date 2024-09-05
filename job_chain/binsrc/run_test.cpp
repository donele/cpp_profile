#include <job_chain.h>
#include <iostream>
using namespace std;

int main() {
    const string filename = "input.txt";

    cout << "Using unordered map::extract, parse_line..." << endl;
    process_jobs_map(filename, true);

    return 0;
}
