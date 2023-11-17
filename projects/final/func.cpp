#include "func.h"

Function::Function(const std::string &name, Expr *expr)
  : m_name(name)
  , m_expr(expr) {
}

Function::~Function() {
  // TODO: deallocate objects if necessary
}
