//
// Created by lau-j on 25/02/2022.
//

#ifndef CALCULATOR_VAR_T_HPP
#define CALCULATOR_VAR_T_HPP

#include <unordered_map>
#include <string>
#include "term_t.hpp"

using namespace std;

class var_t : public term_t {
public:
    double operator()(unordered_map<string, double> &vars) override{
        return vars[name];
    }

    var_t(const string &name, double value, unordered_map<string,double > &vars){
        // initialize the name and the value of the variable
        this->name = name;
        vars[name] = value;
    }

    string name;
};

#endif //CALCULATOR_VAR_T_HPP
