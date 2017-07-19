#include <ncurses.h>

#include "token.hpp"
#include "parse.hpp"
#include "eval.hpp"
#include "io.hpp"


/**
 * @brief init_curses - starts curses mode
 *
 * This function starts curses mode with cbreak and keypad enabled.
 */
void init_curses()
{
  initscr();
  cbreak();
  keypad(stdscr, true);  //To properly handle backspace, insert, etc.
}

int main()
{

  //bool running = true;

  std::string line;
  std::vector< std::pair< std::string, char > > tokens;
  std::vector< std::string > history, parsed;

#ifndef DEBUG

  init_curses();

  while(running == true)
  {
    line.clear();
    line = input();
    history.push_back(line);
    tokenise(line, &tokens);
    parse(tokens, &parsed);
    output(out);
    refresh();
  }

#endif

#ifdef DEBUG

  line.clear();
  init_curses();

  line = input("");
  endwin();

  tokenise(line, &tokens);

  parse(tokens, &parsed);

  evaluate(parsed);

#endif

  return 0;
}
