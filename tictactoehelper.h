#ifndef TICTACTOEHELPER_H
#define TICTACTOEHELPER_H




#include "tictactoeplayer.h"
#include "tictactoesquare.h"
#include "tictactoewinner.h"


namespace ribi {
namespace tictactoe {

struct Helper
{
  Helper() {}

  Player GetOtherPlayer(const Player player) const noexcept;

  ///From http://www.richelbilderbeek.nl/CppIntPower.htm
  int IntPower(const int base, const int exponent) const noexcept;


  Square PlayerToSquare(const Player player) const noexcept;
  Player SquareToPlayer(const Square square) const;
  Winner SquareToWinner(const Square square) const;
};

} //~namespace tictactoe
} //~namespace ribi


#endif // TICTACTOEHELPER_H
