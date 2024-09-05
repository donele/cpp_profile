#ifndef __scm_timeseries_h__
#define __scm_timeseries_h__
#include <vector>
#include <map>
#include <queue>
#include <ctime>

void run_vector(bool verbose=false);
void run_map(bool verbose=false);

class TimeSeries {
    public:
    virtual ~TimeSeries(){}
    virtual void Add(time_t current_time, double value) = 0;
    virtual double Get(time_t current_time) = 0;
};

class TimeSeriesMap : public TimeSeries {
    public:
    TimeSeriesMap(size_t window):wsize(window){}
    ~TimeSeriesMap() override {}

    void Add(time_t current_time, double value) override {
        while(!q.empty() && q.front() <= current_time - wsize) {
            m.erase(q.front());
            q.pop();
        }
        q.push(current_time);
        m[current_time] = value;
    }
    double Get(time_t desired_time) override {
        if(!q.empty() && desired_time >= q.front()) {
            auto it = m.find(desired_time);
            if(it != m.end()) {
                return it->second;
            } else {
                auto it = m.lower_bound(desired_time);
                return (--it)->second;
            }
        }
        return 0.0;
    }
    private:
    int wsize;
    std::queue<int> q;
    std::map<int, double> m;
};

class TimeSeriesVector : public TimeSeries {
    public:
    TimeSeriesVector(size_t window):wsize(window){
        valid = std::vector<int>(wsize, 0);
        v = std::vector<double>(wsize, 0);
    }
    ~TimeSeriesVector() override {}

    void Add(time_t current_time, double value) override {
        while(!q.empty() && q.front() <= current_time - wsize) {
            int indx = q.front() % wsize;
            v[indx] = 0.0;
            valid[indx] = 0;
            q.pop();
        }
        int indx = current_time % wsize;
        v[indx] = value;
        valid[indx] = 1;
        q.push(current_time);
    }
    double Get(time_t desired_time) override {
        if(!q.empty() && desired_time >= q.front()) {
            int indx = desired_time % wsize;
            for(int i = 0; i < wsize && indx >= 0; ++i) {
                if(valid[indx])
                   break;
                indx = (indx - 1) % wsize;
            }
            return v[indx];
        }
        return 0.0;
    }
    private:
    int wsize;
    std::queue<int> q;
    std::vector<int> valid;
    std::vector<double> v;
};

#endif
