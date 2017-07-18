#include "eval.hpp"

void c2tree(const std::vector<std::string> &in, tree<std::string> *out)
{
  tree<std::string>::iterator top, current;
  top = out -> begin();

  for(std::vector<string>::iterator i = in.rbegin(); i != in.rend(); ++i)
  {
    if(*i.length() == 1)
    {
      if(!std::isalnum(*i[0]))
      {
        out -> insert(top, *i);
      }
    }
  }
}

void evaluate(const std::vector<std::string> &in)
{

}
