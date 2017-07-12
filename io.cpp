//
//  io.cpp
//  derpcalc
//
//  Created by Raghav on 7/11/17.
//  Copyright © 2017 WarpDev. All rights reserved.
//

#include "io.hpp"


/**
 * @brief input  - Gets keyboard input with ncurses
 * @return out   - The entered string.
 */
std::string input(std::string prompt = "")
{
  std::string out, temp;
  
  unsigned pos = 0;                                                   //Points to the current character in out
  short ch;
  bool insert = false;                                                //To check for insert mode
  int y, x, mx = getmaxx(stdscr), minx = prompt.length();             //x & y are the currently recorded positions on the screen
  addstr(prompt.c_str());
  
  while(true)
  {
    ch = getch();                                                     //Get next character
    getyx(stdscr, y, x);                                              //Get current cursor position
    {
      if(pos <= 0)                                                    //Check if pos is out of bounds & correct its value
        pos = 0;                                                      //
      else if(pos > out.length())                                     //
        pos = out.length();                                           //
    }

    if(ch == '\n')                                                    //Check for line's end
      break;                                                          //

    else if(ch == KEY_BACKSPACE)                                      //Backspace behaviour defined here
    {
      if(!out.empty())                                                //ALWAYS check for empty strings
      {
        if(pos == 0)                                                  //No characters to delete at the start of a line
        {                                                             //
          ;                                                           //
        }                                                             //
        else                                                          //
          out.erase(--pos, 1);                                        //Erase preceding character
        
        if(pos == out.length())                                       //End of the line
        {
          addch(' ');                                                 //No need for fancy stuff here
          move(y, x);                                                 //
        }
        else
        {
          temp = out.substr(pos, out.length() - pos);                 //Save portion of the string which comes after the deleted character
          for (int i = pos; i < mx; ++i) addch(' ');                  //Fill the space behind (and including) the deleted character with whitespace
          mvaddnstr(y, x, temp.c_str(), temp.length());               //Move to currently recorded position on the screen and write over the deleted character
          move(y, x);                                                 //Move cursor back to currently recorded position
        }
      }
    }

    else if(ch == KEY_DC)                                             //Delete behaviour defined here
    {
      if(!out.empty() || pos < (out.length() - 1))                    //Check that pos is not at the last character, as well as for empty string
      {
        out.erase(pos, 1);                                            //Erase current character
        temp = out.substr(pos, out.length() - pos);                   //Like in the backspace handling code
        for (int i = pos; i < mx; ++i) addch(' ');
        mvaddnstr(y, x, temp.c_str(), temp.length());
        move(y, x);
      }
      else
      {
        ;                                                             //If pos is at the end of the string, pressing delete does nothing.
      }

    }

    else if(ch == KEY_IC)                                             //Insert behaviour defined here
    {
      if(!insert)                                                     //Toggle insert
        insert = true;                                                //
      else                                                            //
        insert = false;                                               //
    }

    else if(ch == KEY_LEFT && pos > 0)                                //Can't move further left at the beginning of the string
    {
      move(y, --x);                                                   //Update currently recorded position of the cursor on the spot
      pos--;
    }

    else if(ch == KEY_RIGHT && pos < out.length() )                   //Can't move further right at the end of the string
    {
      move(y, ++x);
      pos++;
    }

    else if(std::isalnum(ch) || std::isspace(ch) || std::ispunct(ch)) //Normal characters
    {
      if(!insert)                                                     //If insert is off
      {
        out.insert(pos++, 1, ch);                                     //Character inserted normally
        if(pos < out.length())                                        //If the character is inserted from anywhere but the end of the string
        {
          std::string temp = out.substr(pos, out.length() - pos);     //Similar to backspace & delete code
          for (int i = pos; i < mx; ++i) addch(' ');
          int tmp = x;
          mvaddnstr(y, x, temp.c_str(), temp.length());
          move(y, tmp);
        }

      }
      else                                                            //Insert is on
      {
        out[pos++] = ch;                                              //Overwrite characters & increment
      }

    }

  }

  return out;
}

void output(std::string line)
{
  addstr(line.c_str());
  addch('\n');
}
