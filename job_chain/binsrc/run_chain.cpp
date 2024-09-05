#include <job_chain.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    vector<string> filenames = {"input_few.txt", "input_many.txt"};
    for(string& filename : filenames) {
        cout << filename << endl;

        cout << "Using vector..." << endl;
        process_jobs_vector(filename, true);

        cout << "Using map..." << endl;
        process_jobs_map(filename, true);

        cout << "Using unordered map..." << endl;
        process_jobs_unordered_map(filename, true);
    }

    return 0;
}
