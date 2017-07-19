#include "eval.hpp"

namespace mathfn
{
auto add = [](real a, real b) -> real {return a + b;};
auto sub = [](real a, real b) -> real {return a - b;};
auto mul = [](real a, real b) -> real {return a * b;};
auto div = [](real a, real b) -> real {if (b != 0) return a / b; else return 0;};
auto mod = [](real a, real b) -> real {return (real)((integer)a % (integer)b);};
};

void evaluate(const std::vector<std::string> &in)
{
  std::stack<std::string> operands;
  real a, b;

  std::regex regx("(a?sinh?|a?cosh?|a?tanh?|sech?|csch?|coth?|\
  exp(n|m1|int|2|10)?|pow|root|(sq|cb)rt|log(n|1p|b|2|10)?|pow|add|sub|mul|div|(g|l)t|(g|l|n)?eq)");
  std::smatch match;

  for(auto i : in)
  {
    {
      if((std::isdigit(i[0]) || i[0] == '_' || i[0] == '.') && !std::regex_search(i, match, regx))
      {
        operands.push(i);
      }
      else if((std::ispunct(i[0]) && !(i[0] == '_' || i[0] == '.')) || std::regex_search(i, match, regx))
      {
        b = std::stold(operands.top());
        operands.pop();
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
      }
    }
  }
}
