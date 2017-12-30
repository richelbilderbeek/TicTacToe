#include "tictactoesquare.h"

#include <cassert>
#include <stdexcept>

int ribi::tictactoe::SquareToState(const ribi::tictactoe::Square square) noexcept
{
  switch (square)
  {
    case Square::empty  : return 0;
    case Square::player1: return 1;
    case Square::player2: return 2;
  }
  assert(!"Should not get here");
  return 0;
}

std::string ribi::tictactoe::SquareToStr(const tictactoe::Square square) noexcept
{
  switch (square)
  {
    case Square::empty  : return " ";
    case Square::player1: return "X";
    case Square::player2: return "O";
  }
  assert(!"Should not get here");
  return " ";
}

ribi::tictactoe::Square ribi::tictactoe::StateToSquare(const int state)
{
  switch (state)
  {
    case 0: return Square::empty;
    case 1: return Square::player1;
    case 2: return Square::player2;
  }
  assert(!"Should not get here");
  throw std::logic_error("TicTacToe::StateToSquare: unknown state");

}
