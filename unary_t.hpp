//
// Created by lau-j on 25/02/2022.
//

#ifndef CALCULATOR_UNARY_T_HPP
#define CALCULATOR_UNARY_T_HPP

#include <utility>
#include "term_t.hpp"

using namespace std;

class unary_t : public term_t {
    shared_ptr<term_t> term;
    op_t op;
public:
    unary_t(shared_ptr<term_t> expr, op_t op) : term(move(expr)), op(op) {}

    ~unary_t() = default;

    double operator()(unordered_map<string, double> &var_map) override{
        switch (op) {
            case NEG:
                return -term->operator()(var_map);
            case POS:
                return term->operator()(var_map);
            default:
                throw logic_error{"unsupported operation"};
        }
    }
};

#endif //CALCULATOR_UNARY_T_HPP
