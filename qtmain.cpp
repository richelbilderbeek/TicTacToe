#pragma GCC diagnostic push

#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QApplication>
#include "qttictactoemenudialog.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::tictactoe::QtTicTacToeMenuDialog w;
  w.show();
  return a.exec();
}

