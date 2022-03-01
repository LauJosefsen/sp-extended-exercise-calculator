#include "expr_t.hpp"

#include "binary_t.hpp"
#include "unary_t.hpp"

expr_t expr_t::operator+(const expr_t& other) const {
    // construct a new expr_t with binary_t
    return {make_shared<binary_t>(this->term, other.term, ADD)};
}

expr_t expr_t::operator-(const expr_t &other) const {
    return {make_shared<binary_t>(this->term, other.term, SUB)};
}

expr_t expr_t::operator/(const expr_t &other) const {
    return {make_shared<binary_t>(this->term, other.term, DIV)};
}

expr_t expr_t::operator*(const expr_t &other) const {
    return {make_shared<binary_t>(this->term, other.term, MUL)};
}

expr_t expr_t::operator-() const {
    return {make_shared<unary_t>(this->term, NEG)};
}

expr_t expr_t::operator+() const {
    return {make_shared<unary_t>(this->term, POS)};
}

expr_t expr_t::operator<<=(const expr_t &other) const {
    return {make_shared<binary_t>(this->term, other.term, ASSIGN)};
}

///////////////////////////////////////////////////////////////////////////////
// NOTE: After assignment is implemented, we can simply rewrite the expressions of the form +=, -=, *=, /=
// Example:
// a += b
// a = a + b
///////////////////////////////////////////////////////////////////////////////
expr_t expr_t::operator+=(const expr_t &other) const {
    return *this <<= *this + other;
}

expr_t expr_t::operator-=(const expr_t &other) const {
    return *this <<= *this - other;
}

expr_t expr_t::operator*=(const expr_t &other) const {
    return *this <<= *this * other;
}

expr_t expr_t::operator/=(const expr_t &other) const {
    return *this <<= *this / other;
}
