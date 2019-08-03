#ifndef QTTICTACTOEMENUDIALOG_H
#define QTTICTACTOEMENUDIALOG_H





#include "qthideandshowdialog.h"


namespace Ui {
  class QtTicTacToeMenuDialog;
}

namespace ribi {
namespace tictactoe {

class QtTicTacToeMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTicTacToeMenuDialog(QWidget *parent = 0);
  QtTicTacToeMenuDialog(const QtTicTacToeMenuDialog&) = delete;
  QtTicTacToeMenuDialog& operator=(const QtTicTacToeMenuDialog&) = delete;
  ~QtTicTacToeMenuDialog() noexcept;

private:
  Ui::QtTicTacToeMenuDialog *ui;

private slots:
  void on_button_quit_clicked();
  void on_button_about_clicked();
  void on_button_start_clicked();
};

} //~namespace tictactoe
} //~namespace ribi

#endif // QTTICTACTOEMENUDIALOG_H
