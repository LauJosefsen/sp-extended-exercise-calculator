#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
//
// Created by lau-j on 25/02/2022.
//

#ifndef CALCULATOR_EXPR_T_HPP
#define CALCULATOR_EXPR_T_HPP

#include "term_t.hpp"
#include "binary_t.hpp"
#include "const_t.hpp"
#include "unary_t.hpp"
#include <memory>
#include <utility>

using namespace std;

class expr_t {
public:
    expr_t(double value) : term(new const_t(value)) {}

    shared_ptr<term_t> term;

    expr_t(shared_ptr<term_t> term) : term(std::move(term)) {}

    double operator()(unordered_map<string, double> &state) {
        return (*term)(state);
    }

    // binary operators
    expr_t operator+(const expr_t& other) const;
    expr_t operator-(const expr_t& other) const;
    expr_t operator*(const expr_t& other) const;
    expr_t operator/(const expr_t& other) const;

    // unary operators
    expr_t operator-() const;
    expr_t operator+() const;

    // <<=, +=, -=, *=, /=
    expr_t operator<<=(const expr_t &other) const;
    expr_t operator+=(const expr_t &other) const;
    expr_t operator-=(const expr_t &other) const;
    expr_t operator*=(const expr_t &other) const;
    expr_t operator/=(const expr_t &other) const;
};


// NON MEMBER BINARY OPERATORS
inline expr_t operator+(double lhs, const expr_t& rhs){
    return expr_t(lhs) + rhs;
}
inline expr_t operator-(double lhs, const expr_t& rhs){
    return expr_t(lhs) - rhs;
}
inline expr_t operator*(double lhs, const expr_t& rhs){
    return expr_t(lhs) * rhs;
}
inline expr_t operator/(double lhs, const expr_t& rhs){
    return expr_t(lhs) / rhs;
}

#endif //CALCULATOR_EXPR_T_HPP

#pragma clang diagnostic pop