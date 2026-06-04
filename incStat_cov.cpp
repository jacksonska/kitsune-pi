#include <print>
#include "incStat.hpp"

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

}