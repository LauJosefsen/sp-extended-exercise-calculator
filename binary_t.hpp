//
// Created by lau-j on 25/02/2022.
//

#ifndef CALCULATOR_BINARY_T_HPP
#define CALCULATOR_BINARY_T_HPP

#include <utility>

#include "term_t.hpp"
#include "var_t.hpp"

using namespace std;

class binary_t : public term_t {
    shared_ptr<term_t> term1;
    shared_ptr<term_t> term2;
    op_t op;
public:
    binary_t(shared_ptr<term_t> term1, shared_ptr<term_t> term2, op_t op) : term1(std::move(term1)), term2(std::move(term2)), op(op) {}

    double operator()(unordered_map<string, double> &var_map) override{
        switch (op) {
            case ADD:
                return (*term1)(var_map) + (*term2)(var_map);
            case SUB:
                return (*term1)(var_map) - (*term2)(var_map);
            case MUL:
                return (*term1)(var_map) * (*term2)(var_map);
            case DIV: {
                // evaluate second term
                double expr2_val = (*term2)(var_map);
                if (expr2_val == 0) {
                    throw runtime_error("division by zero");
                }
                return (*term1)(var_map) / expr2_val;
            }
            case ASSIGN: {
                // cast term1 term to var_t
                auto var = dynamic_pointer_cast<var_t>(term1);

                // if term1 is not a var_t, throw exception
                if(!var)
                    throw runtime_error("assignment destination must be a variable expression");

                var_map[var->name] = (*term2)(var_map);
                return var_map[var->name];
            }
            default:
                throw logic_error{"unsupported operation"};
        }
    }
};

#endif //CALCULATOR_BINARY_T_HPP
