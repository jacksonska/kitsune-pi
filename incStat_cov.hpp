#pragma once

#include <array>
#include <vector>
#include <string>
#include <cstddef>

#include "incStat.hpp"


// @brief like incStat, but maintains stats between two streams
class incStat_cov
{
public:
    incStat_cov() = delete;

    incStat_cov(incStat is1, incStat is2, int init_time = 0)
    : incStats_({is1, is2}), lastRes_({0, 0}), cf3_(0), w3_(1e-20), lastTimestamp_cf3_(init_time)
    {}

    // update the stream with the value at a given time.
    void update_cov(int id, int value, int time);
    // process the decay of index at time
    double processDecay(std::size_t time, int micro_inc_indx);
    // covariance approximation
    double cov();
    // Pearson corl. coef
    double pcc();
    // calculates and pulls all correlative stats
    std::array<double,2> get_stats1();
    // calculates and pulls all correlative stats AND 2D stats from both streams
    std::array<double,4> get_stats2();
    // calculates and pulls all correlative stats AND 2D stats AND the regular stats from both streams (incStat)
    std::array<double,8> get_stats3();
    // calculates and pulls all correlative stats AND the regular stats from both incStats AND 2D stats
    std::array<double,10> get_stats4();
    // get headers
    std::vector<std::string> getHeaders(std::size_t ver, bool suffix=true);


    // references to the stream's incStats
    std::array<incStat,2> incStats_;
    std::array<double, 2> lastRes_;

    // init sum product residuals
    int cf3_; // 0
    double w3_; // 1e-20
    int lastTimestamp_cf3_;

    private:

};
