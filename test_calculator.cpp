#include "expr_t.hpp"
#include "var_t.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("Calculate expressions lazily")
{
    // setup symbol table with unordered map
    auto st = unordered_map<string, double>{};

    // setup expression
    auto a = expr_t(make_shared<var_t>("a", 2, st));
    auto b = expr_t(make_shared<var_t>("b", 3, st));
    auto c = expr_t(make_shared<var_t>("c", 4, st));
    auto d = expr_t(make_shared<var_t>("d", 0, st));

    auto os = std::ostringstream();

    SUBCASE("Addition of variables")
    {
        CHECK((a + b)(st) == 5);
        CHECK((c + b)(st) == 7);
        CHECK((c + a)(st) == 6);
    }

    SUBCASE("Subtraction of variables")
    {
        CHECK((a - b)(st) == -1);
        CHECK((c - b)(st) == 1);
        CHECK((c - a)(st) == 2);
    }

    SUBCASE("Division of variables")
    {
        CHECK((a / b)(st) == 2.0 / 3);
        CHECK((c / b)(st) == 4.0 / 3);
        CHECK((c / a)(st) == 2);
    }

    SUBCASE("Reading the value of a variable from state")
    {
        CHECK(a(st) == 2);
        CHECK(b(st) == 3);
        CHECK(c(st) == 4);
    }
    SUBCASE("Unary operations")
    {
        CHECK((+a)(st) == 2);
        CHECK((-b)(st) == -3);
        CHECK((-c)(st) == -4);
    }
    SUBCASE("Addition and subtraction")
    {
        CHECK((a + b)(st) == 5);
        CHECK((a - b)(st) == -1);
        // the state should not have changed:
        CHECK(a(st) == 2);
        CHECK(b(st) == 3);
        CHECK(c(st) == 4);
    }
    SUBCASE("Assignment expression evaluation")
    {
        CHECK(c(st) == 4);
        CHECK((c <<= b - a)(st) == 1);
        CHECK(c(st) == 1);

        CHECK((c += b - a * c)(st) == 2);
        CHECK(c(st) == 2);
        CHECK((c += b - a * c)(st) == 1);
        CHECK(c(st) == 1);

        CHECK_THROWS_MESSAGE((c - a += b - c)(st), "assignment destination must be a variable expression");
    }
    SUBCASE("Parenthesis")
    {
        CHECK((a - (b - c))(st) == 3);
        CHECK((a - (b - a))(st) == 1);
    }
    SUBCASE("Evaluation of multiplication and division")
    {
        CHECK((a * b)(st) == 6);
        CHECK((a / b)(st) == 2. / 3);
        CHECK_THROWS_MESSAGE((a / d)(st), "division by zero");
    }
    SUBCASE("Mixed addition and multiplication")
    {
        CHECK((a + a * b)(st) == 8);
        CHECK((a - b / a)(st) == 0.5);
    }
    SUBCASE("Constant expressions")
    {
        CHECK((7 + a)(st) == 9);
        CHECK((a - 7.0)(st) == -5);
        CHECK((7.0 + a)(st) == 9);
        CHECK((a - 7)(st) == -5);
    }
    SUBCASE("Store expression and evaluate lazily")
    {
        auto expr = (a + b) * c;
        auto c_4 = c <<= 0;
        CHECK(expr(st) == 20);
        CHECK(c_4(st) == 0);
        CHECK(expr(st) == 0);
    }
}
