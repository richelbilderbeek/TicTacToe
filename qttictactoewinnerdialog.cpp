#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttictactoewinnerdialog.h"

#include <cassert>


#include "ui_qttictactoewinnerdialog.h"

#pragma GCC diagnostic pop

ribi::tictactoe::QtTicTacToeWinnerDialog::QtTicTacToeWinnerDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTicTacToeWinnerDialog)
{
  ui->setupUi(this);
}

ribi::tictactoe::QtTicTacToeWinnerDialog::~QtTicTacToeWinnerDialog() noexcept
{
  delete ui;
}

void ribi::tictactoe::QtTicTacToeWinnerDialog::SetDraw()
{
  ui->label_title->setText("Draw");
  this->setWindowTitle("Draw");
  ui->label_winner->setText(" ");
}

void ribi::tictactoe::QtTicTacToeWinnerDialog::SetWinnerCross()
{
  ui->label_winner->setPixmap(QPixmap(":/images/X.png"));
}

void ribi::tictactoe::QtTicTacToeWinnerDialog::SetWinnerCircle()
{
  ui->label_winner->setPixmap(QPixmap(":/images/O.png"));
}

