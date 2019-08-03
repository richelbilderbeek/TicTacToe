#pragma GCC diagnostic push



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

