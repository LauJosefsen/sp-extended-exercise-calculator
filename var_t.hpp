//
// Created by lau-j on 25/02/2022.
//

#ifndef CALCULATOR_VAR_T_HPP
#define CALCULATOR_VAR_T_HPP

#include <map>
#include <string>
#include "term_t.hpp"

using namespace std;

class var_t : public term_t {
public:
    double operator()(map<string, double> &vars) override{
        return vars[name];
    }

    var_t(const string &name, double value, map<string,double > &vars){
        this->name = name;
        vars[name] = value;
    }

    string name;
};

#endif //CALCULATOR_VAR_T_HPP
