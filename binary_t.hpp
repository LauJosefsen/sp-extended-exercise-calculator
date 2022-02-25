//
// Created by lau-j on 25/02/2022.
//

#ifndef CALCULATOR_BINARY_T_HPP
#define CALCULATOR_BINARY_T_HPP

#include <utility>

#include "term_t.hpp"
#include "var_t.hpp"

class binary_t : public term_t {
    shared_ptr<term_t> expr1;
    shared_ptr<term_t> expr2;
    op_t op;
public:
    binary_t(shared_ptr<term_t> expr1, shared_ptr<term_t> expr2, op_t op){
        this->expr1 = std::move(expr1);
        this->expr2 = std::move(expr2);
        this->op = op;
    }

    double operator()(map<string, double> &var_map) override{
        switch (op) {
            case ADD:
                return (*expr1)(var_map) + (*expr2)(var_map);
            case SUB:
                return (*expr1)(var_map) - (*expr2)(var_map);
            case MUL:
                return (*expr1)(var_map) * (*expr2)(var_map);
            case DIV: {
                // evaluate second expr
                double expr2_val = (*expr2)(var_map);
                if (expr2_val == 0) {
                    throw runtime_error("division by zero");
                }
                return (*expr1)(var_map) / expr2_val;
            }
            case ASSIGN: {
                // cast expr1 term to var_t
                auto var = dynamic_pointer_cast<var_t>(expr1);

                // if expr1 is not a var_t, throw exception
                if(!var)
                    throw runtime_error("assignment destination must be a variable expression");

                var_map[var->name] = (*expr2)(var_map);
                return var_map[var->name];
            }
            default:
                throw std::logic_error{"unsupported operation"};
        }
    }
};

#endif //CALCULATOR_BINARY_T_HPP
