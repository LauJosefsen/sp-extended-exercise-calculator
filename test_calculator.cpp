#include "expr_t.hpp"
#include "var_t.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("Calculate expressions lazily")
{
    auto symbol_table_dictionary = map<string, double>{};
    auto a = expr_t(new var_t("a", 2, symbol_table_dictionary));
    auto b = expr_t(new var_t("b", 3, symbol_table_dictionary));
    auto c = expr_t(new var_t("c", 4, symbol_table_dictionary));
    auto d = expr_t(new var_t("d", 0, symbol_table_dictionary));

    // todo
//    auto a = var_t("a", 2, symbol_table_dictionary);
//    auto b = var_t("b", 3, symbol_table_dictionary);
//    auto c = var_t("c", 4, symbol_table_dictionary);
//    auto d = var_t("d", 0, symbol_table_dictionary);

    auto os = std::ostringstream();

    SUBCASE("Addition of variables")
    {
        CHECK((a + b)(symbol_table_dictionary) == 5);
        CHECK((c + b)(symbol_table_dictionary) == 7);
        CHECK((c + a)(symbol_table_dictionary) == 6);
    }

    SUBCASE("Subtraction of variables")
    {
        CHECK((a - b)(symbol_table_dictionary) == -1);
        CHECK((c - b)(symbol_table_dictionary) == 1);
        CHECK((c - a)(symbol_table_dictionary) == 2);
    }

    SUBCASE("Division of variables")
    {
        CHECK((a / b)(symbol_table_dictionary) == 2.0 / 3);
        CHECK((c / b)(symbol_table_dictionary) == 4.0 / 3);
        CHECK((c / a)(symbol_table_dictionary) == 2);
    }

    SUBCASE("Reading the value of a variable from state")
    {
        CHECK(a(symbol_table_dictionary) == 2);
        CHECK(b(symbol_table_dictionary) == 3);
        CHECK(c(symbol_table_dictionary) == 4);
    }
    SUBCASE("Unary operations")
    {
        CHECK((+a)(symbol_table_dictionary) == 2);
        CHECK((-b)(symbol_table_dictionary) == -3);
        CHECK((-c)(symbol_table_dictionary) == -4);
    }
    SUBCASE("Addition and subtraction")
    {
        CHECK((a + b)(symbol_table_dictionary) == 5);
        CHECK((a - b)(symbol_table_dictionary) == -1);
        // the state should not have changed:
        CHECK(a(symbol_table_dictionary) == 2);
        CHECK(b(symbol_table_dictionary) == 3);
        CHECK(c(symbol_table_dictionary) == 4);
    }
    SUBCASE("Assignment expression evaluation")
    {
        CHECK(c(symbol_table_dictionary) == 4);
        CHECK((c <<= b - a)(symbol_table_dictionary) == 1);
        CHECK(c(symbol_table_dictionary) == 1);

        CHECK((c += b - a * c)(symbol_table_dictionary) == 2);
        CHECK(c(symbol_table_dictionary) == 2);
        CHECK((c += b - a * c)(symbol_table_dictionary) == 1);
        CHECK(c(symbol_table_dictionary) == 1);

        // todo
//        CHECK_THROWS_MESSAGE((c - a += b - c), "assignment destination must be a variable expression");
    }
    SUBCASE("Parenthesis")
    {
        CHECK((a - (b - c))(symbol_table_dictionary) == 3);
        CHECK((a - (b - a))(symbol_table_dictionary) == 1);
    }
    SUBCASE("Evaluation of multiplication and division")
    {
        CHECK((a * b)(symbol_table_dictionary) == 6);
        CHECK((a / b)(symbol_table_dictionary) == 2. / 3);
        CHECK_THROWS_MESSAGE((a / d)(symbol_table_dictionary), "division by zero");
    }
    SUBCASE("Mixed addition and multiplication")
    {
        CHECK((a + a * b)(symbol_table_dictionary) == 8);
        CHECK((a - b / a)(symbol_table_dictionary) == 0.5);
    }

    // todo
    SUBCASE("Constant expressions")
    {
        CHECK((7 + a)(symbol_table_dictionary) == 9);
        CHECK((a - 7.0)(symbol_table_dictionary) == -5);
        CHECK((7.0 + a)(symbol_table_dictionary) == -5);
        CHECK((a - 7)(symbol_table_dictionary) == -5);
    }
//    SUBCASE("Store expression and evaluate lazily")
//    {
//        auto expr = (a + b) * c;
//        auto c_4 = c <<= 4;
//        CHECK(expr(state) == 0);
//        CHECK(c_4(state) == 4);
//        CHECK(expr(state) == 20);
//    }
//    */
}
