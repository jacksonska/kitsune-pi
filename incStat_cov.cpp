#include <print>
#include <cmath>
#include "incStat_cov.hpp"

void incStat_cov::update_cov(int id, int value, int time)
{
    int inc = -1;
    if (id == this->incStats_[0].id_)
    {
        inc = 0;
    }
    else if (id == this->incStats_[1].id_)
    {
        inc = 1;
    }
    else
    {
        std::println("id {} is not in either stream", id);
        return;
    }
    int not_inc = inc == 0 ? 1 : 0;
    // decay other incStat
    this->incStats_[not_inc].processDecay(time);

    // decay residuals
    this->processDecay(time, inc);

    // compute and update residual
    double residual {value - this->incStats_[inc].mean()};
    double resid {residual * this->lastRes_[not_inc]};
    this->cf3_ += resid;
    this->w3_ += 1;
    this->lastRes_[inc] = res;
}

double incStat_cov::processDecay(std::size_t time, int micro_inc_indx)
{
    double factor {1.0};
    // check for decay cf3
    int timeDiffs_cf3 {time - this->lastTimestamp_cf3_};
    if (timeDiffs_cf3 > 0)
    {
        factor = std::pow(2, (-this->incStats_[micro_inc_indx].Lambda) * timeDiffs_cf3);
        this->cf3_ *= factor;
        this->w3_ *= factor;
        this->lastTimestamp_cf3_ = time;
        this->lastRes_[micro_inc_indx] *= factor;
    }
    return factor;
}

double incStat_cov::cov()
{
    return this->cf3_ / this->w3_;
}

double incStat_cov::pcc()
{
    ss = this->incStats_[0].std() * this->incStats_[1].std();
    if (ss != 0)
    {
        return this->cov() / ss;
    }
    return 0.0;
}

std::array<double,2> incStat_cov::get_stats1() // nrvo
{
    std::array<double,2> retval {this->cov(), this->pcc()};
    return retval;
}

std::array<double,4> incStats_cov::get_stats2() // nrvo
{
    std::array<double,4> retval {
        this->incStats_[0].radius(this->incStats_[1]),
        this->incStats_[0].magnitude(this->incStats[1]),
        this->cov(),
        this->pcc()
    };
    return retval;
}

// NOTE: this presumes that incstats has values..
std::array<double,8> incStats_cov::get_stats3()
{
    std::array<double,8>  retval {
        this->incStats_[0].w_,
        this->incStats_[0].mean(),
        this->incStats_[0].std(),
        this->incStats_[1].w_,
        this->incStats_[1].mean(),
        this->incStats_[1].std(),
        this->cov(),
        this->pcc()
    };
    return retval;
}

std::array<double,10> incStats_cov::get_stats4()
{
    std::array<double,10> retval {
        this->incStats_[0].w_,
        this->incStats_[0].mean(),
        this->incStats_[0].std(),
        this->incStats_[1].w_,
        this->incStats_[1].mean(),
        this->incStats_[1].std(),
        this->incStats_[0].radius(this->incStats_[1]),
        this->incStats_[0].magnitude(this->incStats_[1]),
        this->cov(),
        this->pcc()
    };
    return retval;
}

std::vector<std::string> getHeaders(std::size_t ver, bool suffix=true)
{
    std:vector<std::string> headers {};
    headers.reserve(10);
    std::string s0 {"0"};
    std::string s1 {"1"};

    if (suffix)
    {
        
    }
}