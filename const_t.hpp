//
// Created by lau-j on 25/02/2022.
//

#ifndef CALCULATOR_CONST_T_HPP
#define CALCULATOR_CONST_T_HPP

#include "term_t.hpp"

class const_t : public term_t{
    double value;
public:
    double operator()(map<string, double> &var_map) override {
        return value;
    }

    explicit const_t (double value){
        this->value = value;
    }
};

#endif //CALCULATOR_CONST_T_HPP