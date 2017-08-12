//
//  parse.cpp
//  derpcalc
//
//  Created by Raghav on 7/11/17.
//  Copyright © 2017 WarpDev. All rights reserved.
//

#include "parse.hpp"


boost::unordered_map<std::string, op> ops =  //operand precedance, associativity, and other information
{
  {"^", {10, AS_R, 0, "pow"} },
  {"#", {9, AS_R, 1, "abs"} },
  {"$", {9, AS_R, 1, "nabs"} },
  {"*", {8, AS_L, 0, "mul"} },
  {"/", {8, AS_L, 0, "div"} },
  {"+", {5, AS_L, 0, "add"} },
  {"-", {5, AS_L, 0, "sub"} },
  {"(", {0, AS_N, 0, ""} },
  {")", {0, AS_N, 0, ""} },
  {",", {0, AS_N, 0, ""} }
};



void parse(
           const std::vector<std::pair<std::string, char> > &tokens, //You may wonder if std::map could replace this monstrosity. It can't, as it is not as flexible in its usage.
           std::vector< std::string > * out // The parsed output vector of tokens in postfix order.
           )
{
  std::stack<std::string> opstack;  //Stores operators.
  bool function = false;            //A flag for indicating if we are inside a function.

  for(unsigned i = 0; i < tokens.size(); ++i)                //The main parser loop.
  {
    if(tokens[i].second == 'c' || tokens[i].second == 'v')   //Check for numbers and such.
      {
        if( (i > 0) && tokens[i - 1].first == ")" )          //If the previous character was a ")", it implies a multiplication.
          {
            opstack.push("*");                               //And so, we push a "*" onto the operator stack.
          }
        {
          //if(tokens[i].second == 'c')                 I don't remember why I needed this redundant stuff, so it's
          //  out -> push_back((tokens[i].first));        commented out for now.
          // else
          out -> push_back(tokens[i].first);          //Push operand to output vector.
        }
        if(!opstack.empty())                                     //Safety first. Always check for empty container.
          if(opstack.top() == "#" || opstack.top() == "$")       //Unary operator check
            {
              out -> push_back(opstack.top());                   //Push the unary operator to the output vector.
              opstack.pop();                                     //Pop from operator stack.
            }
      }
    else if(tokens[i].second == 's' || tokens[i].second == 'f')  //If the current token is a symbol or a function.
      {
        if(tokens[i].second == 's')                              //Symbol.
          {
            switch(tokens[i].first[0])                           //Symbols are only single characters.
              {
              case '(' :
                if((i > 0) && (tokens[i - 1].second == 'c' || tokens[i - 1].second == 'v'))
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
                if((i == 0) || ((i > 0) && ((tokens[i - 1].second == 's' && tokens[i - 1].first != ")") || tokens[i - 1].first == "(")))
                  opstack.push("$");
                else
                  goto derp;
                break;
              case '+' :
                if((i == 0) || ((i > 0) && ((tokens[i - 1].second == 's' && tokens[i - 1].first != ")") || tokens[i - 1].first == "(")))
                  opstack.push("#");
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
