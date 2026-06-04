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

double cov()
{
    return this->cf3_ / this->w3_;
}

double pcc()
{
    ss = this->incStats_[0].std() * this->incStats_[1].std();
    if (ss != 0)
    {
        return this->cov() / ss;
    }
    return 0.0;
}
