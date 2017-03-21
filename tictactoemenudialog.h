#ifndef TICTACTOEMENUDIALOG_H
#define TICTACTOEMENUDIALOG_H

#include "menudialog.h"

namespace ribi {
namespace tictactoe {

struct TicTacToeMenuDialog final : public ::ribi::MenuDialog
{
  TicTacToeMenuDialog();
  About GetAbout() const noexcept override;
  Help GetHelp() const noexcept override;
  std::string GetVersion() const noexcept override;
  std::vector<std::string> GetVersionHistory() const noexcept override;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept override;
};

} //~namespace tictactoe
} //~namespace ribi

#endif // TICTACTOEMENUDIALOG_H
