#ifndef TYPES_HPP
#define TYPES_HPP

#include "tree.hh"

typedef long double real;
typedef long long integer;

enum ASSOC
{
  AS_N = 0,
  AS_L,
  AS_R
};

struct op
{
  int prec;
  int assoc;
  bool unary;
  std::string fn;
};

#endif // TYPES_HPP
