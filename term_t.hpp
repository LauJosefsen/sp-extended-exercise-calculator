//
// Created by lau-j on 25/02/2022.
//

#ifndef CALCULATOR_TERM_T_HPP
#define CALCULATOR_TERM_T_HPP

#include <map>
#include <string>
#include <memory>

using namespace std;

enum op_t {
    ADD,
    SUB,
    MUL,
    DIV,
    POS,
    NEG,
    ASSIGN,
};

class term_t {
public:
    virtual double operator()(map<string, double> &state) = 0;

};

#endif //CALCULATOR_TERM_T_HPP
