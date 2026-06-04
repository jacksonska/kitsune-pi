#pragma once

#include <array>
#include <vector>
#include <string>
#include <expected>
#include <exception>


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
    // return radius of a set of incStats
    double radius(const std::vector<incStat>& other_incStats);
    // magintude of this incStat versus others
    double magnitude(const std::vector<incStat>& other_incStats);
    // calculates and pulls all stats on this stream
    std::vector<double> allstats_1D();
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


    private:
};
