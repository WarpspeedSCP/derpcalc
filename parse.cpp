//
//  parse.cpp
//  derpcalc
//
//  Created by Raghav on 7/11/17.
//  Copyright © 2017 WarpDev. All rights reserved.
//

#include "parse.hpp"

void parse(const std::vector<std::pair<std::__cxx11::string, char> > &tokens, std::vector< vtype > * out)
{
  std::stack<std::string> opstack;
  bool function = false;

  for(unsigned i = 0; i < tokens.size(); ++i)
  {
    if(tokens[i].second == 'c' || tokens[i].second == 'v')
    {
        if(((i > 0) && tokens[i - 1].first == ")"))
        {
          opstack.push("*");
        }
        {
        if(tokens[i].second == 'c')
          out -> push_back(std::stold(tokens[i].first));
        else
          out -> push_back(tokens[i].first);
        }
        if(!opstack.empty())
          if(opstack.top() == ".-" || opstack.top() == ".+")
          {
            out -> push_back(opstack.top());
            opstack.pop();
          }
    }
    else if(tokens[i].second == 's' || tokens[i].second == 'f')
    {
      if(tokens[i].second == 's')
      {
        switch(tokens[i].first[0])
        {
        case '(' :
          if(((i > 0) && (tokens[i - 1].second == 'c' || tokens[i - 1].second == 'v')))
            opstack.push("*");
          opstack.push("(");
          break;
        case ')' :
          while(opstack.top() != "(" && !opstack.empty())
          {
            out -> push_back(opstack.top());
            opstack.pop();
          }
          opstack.pop();
          if(function)
          {
            function = false;
            out -> push_back(opstack.top());
            opstack.pop();
          }
          break;
        case ',':
          while(opstack.top() != "(" && !opstack.empty())
          {
            out -> push_back(opstack.top());
            opstack.pop();
          }
          break;
        case '-' :
          if((i == 0) || ((i > 0) && (tokens[i - 1].second == 's' || tokens[i - 1].first == "(")))
            opstack.push(".-");
          else
            goto derp;
          break;
        case '+' :
          if(tokens[i - 1].second == 's' || tokens[i - 1].first == "(")
            opstack.push(".+");
          else
            goto derp;
          break;
        default :
          derp:
          if(ops[tokens[i].first].assoc == AS_L)
            while(!opstack.empty() && ops[opstack.top()].prec > ops[tokens[i].first].prec)
            {
              out -> push_back(opstack.top());
              opstack.pop();
            }
          if(ops[tokens[i].first].assoc == AS_R)
            while(!opstack.empty() && ops[opstack.top()].prec >= ops[tokens[i].first].prec)
            {
              out -> push_back(opstack.top());
              opstack.pop();
            }
          opstack.push(tokens[i].first);
        };

      }
      else
      {
        function = true;
        opstack.push(tokens[i].first);
      }
    }
  }

  while(!opstack.empty())
  {
    out -> push_back(opstack.top());
    opstack.pop();
  }
  for(auto i : *out)
  {
    std::cout << i << std::endl;
  }
}
