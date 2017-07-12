//
//  token.cpp
//  derpcalc
//
//  Created by WarpDev on 7/11/17.
//  Copyright © 2017 WarpDev. All rights reserved.
//

#include "token.hpp"

/**
 * @brief tokenise - Tokenises the given string into constants, symbols and variables.
 * @param line     - The input string
 * @param tokens   - The output vector
 *
 *        This function tokenises the input string and returns the tokens as a vector.
 */

void tokenise(std::string line, std::vector< std::pair< std::string, char > > * tokens)
{
  int mark, pos;                                      //Variables to mark substrings
  bool v, s, c, invalid = false, found_dot = false;   //Token type flags
  mark = pos = 0;                                     //Initialise with 0

  while(true)                                         //lexer loop
  {
    if((unsigned)pos >= line.length())                //End of line check
      break;

    //Set token flags for the current character
    if(std::isalpha(line[mark]))
      v = true, s = c = false;

    if(std::isdigit(line[mark]) || line[mark] == '.')
    {
      c = true, v = s = false;
      if(line[mark] == '.' && !found_dot)
        found_dot = true;
    }
    if(std::ispunct(line[mark]) && line[mark] != '.')
      s = true, v = c = false;

    for(pos = mark + 1; ; ++pos)                      //Find the first character not of the same type as the mark character
    {                                                 //and push all characters (including mark, not including pos) between onto the vector

      if(line[mark] == ' ')                           //If line[mark] is space, just increment mark.
      {
        mark = pos;
        break;
      }

      if(c && line[pos] == '.' && found_dot)                          //If a constant has more than one decimal point, it is not a valid number
        invalid = true;

      if(v && !(std::isalpha(line[pos]) || line[pos] == '_'))         //Variable check
      {
        v = false;                                                    //Found variable, so stop looking for more alphabets
        tokens -> push_back({line.substr(mark, pos - mark), 'v'});    //Add to vector

#ifdef DEBUG
        //TODO: Implement logger
#endif

        mark = pos;
        break;
      }

      if(c && !(std::isdigit(line[pos]) || line[pos] == '.')) //Decimal point is also checked
      {

        c = false;

        if(invalid)                                           //Invalid constants are ignored
        {
#ifdef DEBUG
          //TODO: Implement logger
#endif
          ;
        }
        else
        {
          tokens -> push_back({line.substr(mark, pos - mark), 'c'});
          invalid = false;

#ifdef DEBUG
          //TODO: Implement logger
#endif
        }

        mark = pos;
        break;
      }

      if(s && (line[mark] != '.' || line[mark] != '_'))  //No need to consider '.' or '_' characters
      {
        pos = mark + 1;
        tokens -> push_back({line.substr(mark, pos - mark), 's'});

#ifdef DEBUG
        //TODO: Implement logger
#endif

        mark = pos;
        break;
      }
    }    //end for
  }    //end while

  {
    std::regex regx("(a?sinh?|a?cosh?|a?tanh?|sech?|csch?|coth?|exp(n|m1|int|2|10)?|pow|root|(sq|cb)rt|log(n|1p|b|2|10)?|pow|add|sub|mul|div|(g|l)t|(g|l|n)?eq)");
    std::smatch match;
    for(auto i : *tokens)
    {
      if(i.second == 'v' && std::regex_search(i.first, match, regx))
      {
        i.second = 'f';
      }
    }
  }
  return;
}
