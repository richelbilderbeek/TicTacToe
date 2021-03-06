#include "tictactoewinner.h"

#include <cassert>
#include <stdexcept>

std::string ribi::tictactoe::WinnerToName(const ribi::tictactoe::Winner winner) noexcept
{
  switch (winner)
  {
    case Winner::player1  : return "player1";
    case Winner::player2  : return "player2";
    case Winner::draw     : return "draw";
    case Winner::no_winner: return "no_winner";
  }
  assert(!"Should not get here");
  return "no_winner";
}

std::string ribi::tictactoe::WinnerToStr(const ribi::tictactoe::Winner winner) noexcept
{
  switch (winner)
  {
    case Winner::player1  : return "X";
    case Winner::player2  : return "O";
    case Winner::draw     :
    case Winner::no_winner:
      assert(!"Should not get here");
      return " ";
  }
  assert(!"Should not get here");
  return " ";
}
