//
// Created by lau-j on 25/02/2022.
//

#ifndef CALCULATOR_CONST_T_HPP
#define CALCULATOR_CONST_T_HPP

#include "term_t.hpp"

class const_t : public term_t{
    double value;
public:

    double operator()(unordered_map<string, double> &var_map) override {
        (void) var_map;
        return value;
    }

    explicit const_t(double value) : value(value) {}
};

#endif //CALCULATOR_CONST_T_HPP
