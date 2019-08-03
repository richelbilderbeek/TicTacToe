#ifndef QTTICTACTOEGAMEDIALOG_H
#define QTTICTACTOEGAMEDIALOG_H
#pragma GCC diagnostic push



#include "qthideandshowdialog.h"

#include <string>

#include <boost/shared_ptr.hpp>

#include "tictactoefwd.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTicTacToeGameDialog;
}

namespace ribi {
namespace tictactoe {

class QtTicTacToeGameDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTicTacToeGameDialog(
    const boost::shared_ptr<Ai>& player1,
    const boost::shared_ptr<Ai>& player2,
    QWidget *parent = 0
  );
  QtTicTacToeGameDialog(const QtTicTacToeGameDialog&) = delete;
  QtTicTacToeGameDialog& operator=(const QtTicTacToeGameDialog&) = delete;
  ~QtTicTacToeGameDialog() noexcept;
  static std::string GetVersion() noexcept;

protected:
  void keyPressEvent(QKeyEvent *event);

private:
  Ui::QtTicTacToeGameDialog *ui;
  boost::shared_ptr<QtTicTacToeWidget> m_tictactoe;

private slots:
  void HasWinner(const QtTicTacToeWidget* const);
};

} //~namespace tictactoe
} //~namespace ribi

#endif // QTTICTACTOEGAMEDIALOG_H
