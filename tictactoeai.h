#ifndef TICTACTOEAI_H
#define TICTACTOEAI_H

#include <string>
#include <utility>
#include <vector>





#include "tictactoefwd.h"


namespace ribi {
namespace tictactoe {

///An artifical intelligence for a tic tac toe game
struct Ai
{
  Ai() {}
  virtual ~Ai() noexcept {}
  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;
  virtual std::pair<int,int> SuggestMove(const Game& game) const = 0;
  virtual std::string ToStr() const noexcept = 0;
};

///Try to enforce a draw
struct AiEnforceDraw : public Ai
{
  std::pair<int,int> SuggestMove(const Game& game) const;
  std::string ToStr() const noexcept { return "enforce_draw"; }
};

///Try to enforce a win
struct AiEnforceWin : public Ai
{
  std::pair<int,int> SuggestMove(const Game& game) const;
  std::string ToStr() const noexcept { return "enforce_win"; }
};

///Play randomly
struct AiPlayRandom : public Ai
{
  std::pair<int,int> SuggestMove(const Game& game) const;
  std::string ToStr() const noexcept { return "play_random"; }
};

} //~namespace tictactoe
} //~namespace ribi

#endif // TICTACTOEAI_H
