#include <string>
#include <sstream>
#include <memory>
#include <deque>
#include "exception.h"
#include "expr.h"
#include "expr_parser.h"

ExprParser::ExprParser() {
}

ExprParser::~ExprParser() {
}

Expr *ExprParser::parse(std::istream &in) {
  // Recommended strategy: read all of the tokens in the expression
  // from the istream and put them in a sequence collection
  // such as a vector or deque. The call a recursive helper function
  // which parses the tokens and returns a pointer to an Expr object
  // repersenting the parsed expression.
}
