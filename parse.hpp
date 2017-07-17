//
//  parse.hpp
//  derpcalc
//
//  Created by Raghav on 7/11/17.
//  Copyright © 2017 WarpDev. All rights reserved.
//

#ifndef parse_hpp
#define parse_hpp

#include <boost/unordered_map.hpp>
#include <boost/variant.hpp>

#include <stack>
#include <string>
#include <vector>
#include <utility>
#include <iostream>

typedef long double real;

typedef boost::variant<
long double,
std::string
> vtype;

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

boost::unordered_map<std::string, op> ops =
{
  {"^", {10, AS_R, 0, "pow"} },
  {".+", {9, AS_R, 1, "abs"} },
  {".-", {9, AS_R, 1, "nabs"} },
  {"*", {8, AS_L, 0, "mul"} },
  {"/", {8, AS_L, 0, "div"} },
  {"+", {5, AS_L, 0, "add"} },
  {"-", {5, AS_L, 0, "sub"} },
  {"(", {0, AS_N, 0, ""} },
  {")", {0, AS_N, 0, ""} },
  {",", {0, AS_N, 0, ""} }
};

void dummy() {}

real expn(const real &base, const real &exp)
{
  return (std::exp( exp * std::log(base)));
}

real logn(const real &base, const real &thing)
{
  return (std::log(thing) / std::log(base));
}


void parse(const std::vector<std::pair<std::string, char> > & , std::vector< vtype > *);

#endif /* parse_hpp */
