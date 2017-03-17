#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttictactoemenudialog.h"

#include <cassert>
#include <boost/make_shared.hpp>

#include <QApplication>
#include <QDesktopWidget>

#include "qtaboutdialog.h"
//#include "qtcanvas.h"
//#include "qtcanvasdialog.h"

#include "qttictactoecanvas.h"
#include "qttictactoegamedialog.h"
#include "qttictactoewidget.h"
#include "tictactoemenudialog.h"
#include "tictactoeai.h"

#include "ui_qttictactoemenudialog.h"
#pragma GCC diagnostic pop

ribi::tictactoe::QtTicTacToeMenuDialog::QtTicTacToeMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTicTacToeMenuDialog)
{
  ui->setupUi(this);
}

ribi::tictactoe::QtTicTacToeMenuDialog::~QtTicTacToeMenuDialog() noexcept
{
  delete ui;
}

void ribi::tictactoe::QtTicTacToeMenuDialog::on_button_start_clicked()
{
  const boost::shared_ptr<Ai> player1;
  const boost::shared_ptr<Ai> player2;
  QtTicTacToeGameDialog d(player1,player2);
  this->ShowChild(&d);
}

void ribi::tictactoe::QtTicTacToeMenuDialog::on_button_about_clicked()
{
  About a = TicTacToeMenuDialog().GetAbout();
  a.AddLibrary("QtTicTacToeWidget version: " + tictactoe::QtTicTacToeWidget::GetVersion());
  QtAboutDialog d(a);
  //d.setStyleSheet(styleSheet());
  this->ShowChild(&d);
}

void ribi::tictactoe::QtTicTacToeMenuDialog::on_button_quit_clicked()
{
  close();
}

#ifdef SUPPORT_RETRO_VERSION_OF_TICTACTOE_AGAIN_20150918
void ribi::tictactoe::QtTicTacToeMenuDialog::on_button_start_old_school_clicked()
{
  QtCanvas * const qtcanvas {
    new QtTicTacToeCanvas
  };
  boost::scoped_ptr<QtCanvasDialog> d {
    new QtCanvasDialog(qtcanvas)
  };
  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    d->setGeometry(
      0,0,102,102);
    d->move( screen.center() - this->rect().center() );
  }
  d->setWindowTitle("TicTacToe");
  ShowChild(d.get());
  //canvas will be deleted by QtCanvasDialog
}
#endif // SUPPORT_RETRO_VERSION_OF_TICTACTOE_AGAIN_20150918
