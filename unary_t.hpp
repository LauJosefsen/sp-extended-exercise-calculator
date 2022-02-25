//
// Created by lau-j on 25/02/2022.
//

#ifndef CALCULATOR_UNARY_T_HPP
#define CALCULATOR_UNARY_T_HPP

#include <utility>

#include "term_t.hpp"

class unary_t : public term_t {
    shared_ptr<term_t> expr;
    op_t op;
public:
    unary_t(shared_ptr<term_t> expr, op_t op){
        this->expr = std::move(expr);
        this->op = op;
    }

    double operator()(map<string, double> &var_map) override{
        switch (op) {
            case NEG:
                return -expr->operator()(var_map);
            case POS:
                return expr->operator()(var_map);
            default:
                throw std::logic_error{"unsupported operation"};
        }
    }
};

#endif //CALCULATOR_UNARY_T_HPP
