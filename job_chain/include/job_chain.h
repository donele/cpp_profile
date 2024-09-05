#ifndef __job_chain_h__
#define __job_chain_h__
#include<string>
#include<vector>

struct Job {
    int id;
    int runtime;
    int next;
    bool valid;
    Job(int _id, int _runtime, int _next, bool v):id(_id), runtime(_runtime), next(_next), valid(v){}
};

std::vector<std::string> split_comma(const std::string& s);
bool valid(const std::vector<std::string>& v);
Job parse_line(const std::string& s);

bool process_jobs_vector(const std::string& filename, bool verbose=false);
bool process_jobs_map(const std::string& filename, bool verbose=false);
bool process_jobs_unordered_map(const std::string& filename, bool verbose=false);
bool process_jobs_map_vector(const std::string& filename, bool verbose=false);

#endif
