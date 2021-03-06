

#include "tictactoemenudialog.h"

#include <cassert>
#include <iostream>

#include "dotmatrixchar.h"
#include "tictactoeai.h"
#include "tictactoeais.h"
#include "tictactoeboard.h"

#include "tictactoegame.h"
#include "tictactoewidget.h"



ribi::tictactoe::TicTacToeMenuDialog::TicTacToeMenuDialog()
{

}

int ribi::tictactoe::TicTacToeMenuDialog::ExecuteSpecific(const std::vector<std::string>& args) noexcept
{
  bool silent{false};
  if (std::count(args.begin(),args.end(),"-s") || std::count(args.begin(),args.end(),"--silent"))
  {
    silent = true;
  }

  boost::shared_ptr<Ai> p1;
  boost::shared_ptr<Ai> p2;
  for (const auto& arg: args)
  {
    if (arg == "-e" || arg == "--1e") p1.reset(new AiEnforceDraw);
    if (arg == "-m" || arg == "--1m") p1.reset(new AiPlayRandom);
    if (arg == "-h" || arg == "--1h") p1.reset(new AiEnforceWin);
    if (arg == "-E" || arg == "--2e") p2.reset(new AiEnforceDraw);
    if (arg == "-M" || arg == "--2m") p2.reset(new AiPlayRandom);
    if (arg == "-H" || arg == "--2h") p2.reset(new AiEnforceWin);
  }

  if (silent)
  {
    if (!p1 || !p2) { return 0; } //Cannot test a live game in silent mode
  }
  tictactoe::Game t;

  while (1)
  {
    if (!silent) { std::cout << t.ToTextCanvas() << std::endl; }

    if (t.GetWinner() != tictactoe::Winner::no_winner) break;


    auto ai = t.GetCurrentPlayer() == Player::player1 ? p1 : p2;
    if (ai)
    {
      const auto move(ai->SuggestMove(t));
      t.DoMove(move.first,move.second);
    }
    else
    {
      int x = 0;
      int y = 0;
      std::cout << "Please enter input:\n";
      std::cin >> x >> y;
      if (t.CanDoMove(x,y)) t.DoMove(x,y);
    }
  }
  return 0;
}

ribi::About ribi::tictactoe::TicTacToeMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TicTacToe",
    "tic-tac-toe game",
    "September 18th of 2015",
    "2010-2015",
    "http://www.richelbilderbeek.nl/GameTicTacToe.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("DotMatrix version: " + DotMatrixChar::GetVersion());
  a.AddLibrary("tictactoe::Board version: " + tictactoe::Board::GetVersion());
  a.AddLibrary("tictactoe::Game version: " + tictactoe::Game::GetVersion());
  a.AddLibrary("tictactoe::Widget version: " + tictactoe::Widget::GetVersion());
  return a;
}

ribi::Help ribi::tictactoe::TicTacToeMenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {
      Help::Option('e',"1e","Player 1: easy"),
      Help::Option('m',"1m","Player 1: medium"),
      Help::Option('h',"1h","Player 1: hard"),
      Help::Option('s',"silent","no output"),
      Help::Option('E',"2e","Player 2: easy"),
      Help::Option('M',"2m","Player 2: medium"),
      Help::Option('H',"2h","Player 2: hard")
    },
    {
      GetAbout().GetFileTitle(),
      GetAbout().GetFileTitle() + " -e",
      GetAbout().GetFileTitle() + " --1e -E",
      GetAbout().GetFileTitle() + " --1h -2h"
    }
  );
}

std::string ribi::tictactoe::TicTacToeMenuDialog::GetVersion() const noexcept
{
  return "1.9";
}

std::vector<std::string> ribi::tictactoe::TicTacToeMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-09-24: Version 1.0: initial version",
    "2010-11-20: Version 1.1: fixed menu",
    "2011-01-07: version 1.2: merge with Wt TicTacToe game",
    "2011-01-07: version 1.3: seperated wtmain.cpp in multiple units",
    "2011-04-15: version 1.4: major architectural changes",
    "2011-04-16: version 1.5: added use of WtAutoConfig (for web application)"
    "2014-02-10: version 1.6: added retro version",
    "2014-06-05: version 1.7: first step in adding AI",
    "2014-08-07: version 1.8: added silent flag in console version",
    "2015-09-18: version 1.9: removed retro version"
  };
}
