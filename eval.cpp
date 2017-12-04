#include "eval.hpp"
#include <limits>

namespace mathfn
{
  auto add = [](real a, real b) -> real {return a + b;};
  auto sub = [](real a, real b) -> real {return a - b;};
  auto mul = [](real a, real b) -> real {return a * b;};
  auto div = [](real a, real b) -> real {if (b != 0) return a / b; else return std::numeric_limits<real>::infinity();};
  auto mod = [](real a, real b) -> real {return (real)((integer)a % (integer)b);};

  auto sin = [](real a) -> real {return std::sin(a);};
  auto cos = [](real a) -> real {return std::cos(a);};
  auto tan = [](real a) -> real {return std::tan(a);};

  auto sec = [](real a) -> real {return 1/std::cos(a);};
  auto csc = [](real a) -> real {return 1/std::sin(a);};
  auto cot = [](real a) -> real {return 1/std::tan(a);};

  auto pow = [](real a, real b) -> real {return std::pow(a, b);};
}

std::string evaluate(const std::vector<std::string> &in)
{
  std::stack<std::string> operands;
  real a, b;

  std::regex regx("(a?sinh?|a?cosh?|a?tanh?|sech?|csch?|coth?|\
  exp(n|m1|int|2|10)?|pow|root|(sq|cb)rt|log(n|1p|b|2|10)?|pow|add|sub|mul|div|(g|l)t|(g|l|n)?eq)");
  std::smatch match;

  for(auto i : in)
  {
    if((std::isdigit(i[0]) || i[0] == '_' || i[0] == '.') && !std::regex_search(i, match, regx))
    {
      operands.push(i);
    }
    else if(std::ispunct(i[0]) && !(i[0] == '_' || i[0] == '.'))
    {
      if(i[0] != '$')
      {
        b = std::stold(operands.top());
        operands.pop();
      }
      a = std::stold(operands.top());
      operands.pop();

      if(i[0] == '+')
      {
        std::cout << mathfn::add(a, b) << std::endl;
        operands.push(boost::lexical_cast<std::string>(mathfn::add(a, b)));
      }
      if(i[0] == '-')
      {
        std::cout << mathfn::sub(a, b) << std::endl;
        operands.push(boost::lexical_cast<std::string>(mathfn::sub(a, b)));
      }
      if(i[0] == '*')
      {
        std::cout << mathfn::mul(a, b) << std::endl;
        operands.push(boost::lexical_cast<std::string>(mathfn::mul(a, b)));
      }
      if(i[0] == '/')
      {
        std::cout << mathfn::div(a, b) << std::endl;
        operands.push(boost::lexical_cast<std::string>(mathfn::div(a, b)));
      }
      if(i[0] == '%')
      {
        std::cout << mathfn::mod(a, b) << std::endl;
        operands.push(boost::lexical_cast<std::string>(mathfn::mod(a, b)));
      }
      if(i[0] == '^')
      {
        std::cout << mathfn::pow(a, b) << std::endl;
        operands.push(boost::lexical_cast<std::string>(mathfn::mod(a, b)));
      }
      if(i[0] == '$')
        operands.push(boost::lexical_cast<std::string>(-a));
    }
    else if(std::regex_search(i, match, regx))
    {
      if(i == "sin")
      {
        a = std::stold(operands.top());
        operands.pop();

        std::cout << mathfn::sin(a) << std::endl;
        operands.push(boost::lexical_cast<std::string>(mathfn::sin(a)));
      }
      if(i == "cos")
      {
        a = std::stold(operands.top());
        operands.pop();

        std::cout << mathfn::cos(a) << std::endl;
        operands.push(boost::lexical_cast<std::string>(mathfn::cos(a)));
      }
      if(i == "tan")
      {
        a = std::stold(operands.top());
        operands.pop();

        std::cout << mathfn::tan(a) << std::endl;
        operands.push(boost::lexical_cast<std::string>(mathfn::tan(a)));
      }


    }
  }
  return operands.top();
}
