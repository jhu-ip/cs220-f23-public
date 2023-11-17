#ifndef EXPR_H
#define EXPR_H

#include <vector>

// Base expression class
class Expr {
private:
  // TODO: field(s) to store links to child Expr nodes

  // value semantics are prohibited
  Expr(const Expr &);
  Expr &operator=(const Expr &);

public:
  Expr();
  virtual ~Expr();

  virtual double eval(double x) const = 0;

  // TODO: add member functions
};

// TODO: add derived expression classes

#endif // EXPR_H
