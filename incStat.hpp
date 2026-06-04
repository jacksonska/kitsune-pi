#pragma once

#include <array>
#include <vector>
#include <expected>
#include <exception>

#include "incStat_cov.hpp"


class incStat 
{
    public:

    incStat() = delete;
    
    explicit incStat (std::array<double,5> lambda, int id, int init_time=0, int isTypeDiff = false)
        : lambda_(std::move(lambda)), id_(id), lastTimestamp_(init_time), isTypeDiff_(isTypeDiff)
    {}
    // insert covariance value
    // calls processDecay
    void insert(int value, int curr_time=0);
    // 
    void processDecay(int timestamp);
    // return weight
    double weight();
    // return mean
    double mean();
    // return variance
    double var();
    // return current std
    double std();
    // return cov approximation
    std::expected<std::vector<double>&, std::string> cov(int id2);
    // return pcc
    double pcc (int id2);
    // return cov_pcc
    std::expected< std::array<double,2>, std::string> cov_pcc(int id2);
    // return radius of a set of incStats
    double radius(const std::vector<incStat>& other_incStats);
    // magintude of this incStat versus others
    double magnitude(const std::vector<incStat>& other_incStats);
    // calculates and pulls all stats on this stream
    std::vector<double> allstats_1D();
    // calcultes and pulls all stats on this stream, and shared
    // with the indicated stream
    std::vector<double> allstats_2D(int id2);
    // return headers information in 1D
    std::array<std::string,3> getHeaders_1D(bool suffix=true);
    // return headers information in 2D
    std::array<std::string,6> getHeaders_2D(int id2, bool suffix=true);

    
    int id_;
    int lastTimestamp_;

    long cf1_; // = 0l, cf2_ = 0l;
    double weight_; // = 1e-20;
    double curr_mean, curr_var, curr_std;
    bool isTypeDiff_;
    
    std::array<double,5> lambda_;
    std::vector<incStat_cov> covs_;


    private:  
};

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