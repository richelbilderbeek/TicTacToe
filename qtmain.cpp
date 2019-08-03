



#include <QApplication>
#include "qttictactoemenudialog.h"


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::tictactoe::QtTicTacToeMenuDialog w;
  w.show();
  return a.exec();
}

