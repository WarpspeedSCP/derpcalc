//
//  parse.cpp
//  derpcalc
//
//  Created by Raghav on 7/11/17.
//  Copyright © 2017 WarpDev. All rights reserved.
//

#include "parse.hpp"

enum ASSOC
{
  AS_N = 0,
  AS_L,
  AS_R
};


typedef mpfr::real<1024> real;

typedef boost::varient<

boost::function0<void>,
boost::function1<const real *, const real *>,
boost::function2<const real *, unsigned long int, const real *>,
boost::function2<const real *, const real *, const real *>

> bfn;

typedef boost::unordered_map<std::string, bfn> tokenmap;

struct op
{
  int prec;
  int assoc;
  int unary;
  std::string fn;
};

boost::unordered_map<std::string, op> ops =

{
  {"-", {10, AS_R, 1, "abs"} },
  {"+", {10, AS_R, 1, "nabs"} },
  {"^", {9, AS_R, 0, "pow"} },
  {"*", {8, AS_L, 0, "mul"} },
  {"/", {8, AS_L, 0, "div"} },
  {"+", {5, AS_L, 0, "add"} },
  {"-", {5, AS_L, 0, "sub"} },
  {"(", {0, AS_N, 0, ""} },
  {")", {0, AS_N, 0, ""} }
};

void dummy() {}

real expn(const real * base, const real * exp)
{
  return (mpfr::exp( *exp * mpfr::log(*base) ));
}

real logn(const real * base, const real * thing)
{
  return (mpfr::log(*thing) / mpfr::log(*base));
}

tokenmap fnmp(
{
  {"", &dummy},

  {"sin", &mpfr::sin},
  {"cos", &mpfr::cos},
  {"tan", &mpfr::tan},
  {"sec", &mpfr::sec},
  {"csc", &mpfr::csc},
  {"cot", &mpfr::cot},

  {"sinh", &mpfr::sinh},
  {"cosh", &mpfr::cosh},
  {"tanh", &mpfr::tanh},
  {"sech", &mpfr::sech},
  {"csch", &mpfr::csch},
  {"coth", &mpfr::coth},

  {"asin", &mpfr::asin},
  {"acos", &mpfr::acos},
  {"atan", &mpfr::atan},

  {"asinh", &mpfr::asinh},
  {"acosh", &mpfr::acosh},
  {"atanh", &mpfr::atanh},

  {"pow", &mpfr::pow},
  {"root", &mpfr::root},
  {"sqrt", &mpfr::sqrt},
  {"cbrt", &mpfr::cbrt},

  {"exp", &mpfr::exp},
  {"exp2", &mpfr::exp2},
  {"exp10", &mpfr::exp10},
  {"expint", &mpfr::expint},
  {"expm1", &mpfr::expm1},
  {"expn", &expn},

  {"log", &mpfr::log},
  {"log2", &mpfr::log2},
  {"log10", &mpfr::log10},
  {"logb", &mpfr::logb},
  {"log1p", &mpfr::log1p},
  {"logn", &logn},

  {"add", &mpfr::operator +},
  {"sub", &mpfr::operator -},
  {"mul", &mpfr::operator *},
  {"div", &mpfr::operator /},

  {"gt", &mpfr::operator >},
  {"lt", &mpfr::operator >},
  {"eq", &mpfr::operator ==},
  {"neq", &mpfr::operator !=},
  {"geq", &mpfr::operator >=},
  {"leq", &mpfr::operator <=},

}
);

void parse(const std::vector<std::pair<std::string, char>> * tokens, std::vector<std::string> * out)
{
  std::stack<std::string> opstack;
  bool expect_parens = false;

  for(auto i : *tokens)
  {
    if(i.second == 'c' || i.second == 'v')
    {
      out -> push_back(i.first);
    }
    else if(i.second == 's')
    {
      if(i.first == "(")
      {
        opstack.push (i.first);
        expect_parens = false;
      }
      else if(i.first == ")")
        while(!opstack.empty() && opstack.top() != "(" )
        {
          out -> push_back(opstack.top());
          opstack.pop();
        }
      else
      {
        if(expect_parens)
          std::cout << "malformed function! : " << i.first << std::endl;
        else
          while(!opstack.empty() && (ops[opstack.top()].prec >= ops[i.first].prec))
          {
            out -> push_back(opstack.top());
            opstack.pop();
          }
        opstack.push(i.first);
      }
    }
    else if(i.second == 'f')
    {
      expect_parens = true;
      opstack.push(i.first);
    }
    //else
      //out -> push_back(opstack.top());
  }

  std::cout << "parsed" <<std::endl;

  for(auto i : *out)
  {
    std::cout << i;
  }
}
