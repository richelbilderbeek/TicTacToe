#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttictactoegamedialog.h"

#include <cassert>
#include <functional>
#include <stdexcept>

#include <boost/lambda/bind.hpp>

#include <QKeyEvent>
#include <QDesktopWidget>

#include "tictactoegame.h"

#include "tictactoewidget.h"
#include "qttictactoewidget.h"
#include "qttictactoewinnerdialog.h"

#include "ui_qttictactoegamedialog.h"

#pragma GCC diagnostic pop

ribi::tictactoe::QtTicTacToeGameDialog::QtTicTacToeGameDialog(
  const boost::shared_ptr<Ai>& player1,
  const boost::shared_ptr<Ai>& player2,
  QWidget *parent
) : QtHideAndShowDialog(parent),
    ui(new Ui::QtTicTacToeGameDialog),
    m_tictactoe(new QtTicTacToeWidget(player1,player2))
{
  ui->setupUi(this);
  ui->layout->addWidget(m_tictactoe.get());


  m_tictactoe->m_signal_has_winner.connect(
    boost::bind(&ribi::tictactoe::QtTicTacToeGameDialog::HasWinner,this,boost::lambda::_1)
  );
  //QObject::connect(m_tictactoe.get(),&QtTicTacToeWidget::m_signal_has_winner,
  //  this,&ribi::tictactoe::QtTicTacToeGameDialog::HasWinner
  //);

  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,3 * screen.width() / 4,3 * screen.height() / 4);
    this->move( screen.center() - this->rect().center() );
  }
}

ribi::tictactoe::QtTicTacToeGameDialog::~QtTicTacToeGameDialog() noexcept
{
  delete ui;
}

std::string ribi::tictactoe::QtTicTacToeGameDialog::GetVersion() noexcept
{
  return "1.2";
}

void ribi::tictactoe::QtTicTacToeGameDialog::HasWinner(const QtTicTacToeWidget* const)
{

  QtTicTacToeWinnerDialog d;
  switch (m_tictactoe->GetWidget()->GetWinner())
  {
    case Winner::player1: d.SetWinnerCross(); break;
    case Winner::player2: d.SetWinnerCircle(); break;
    case Winner::draw: d.SetDraw(); break;
    case Winner::no_winner:
      assert(!"QtTicTacToeGameDialog::HasWinner: should not respond to no winner");
      throw std::logic_error("QtTicTacToeGameDialog::HasWinner: should not respond to no winner");
  }
  d.exec();
  m_tictactoe->Restart();
}

void ribi::tictactoe::QtTicTacToeGameDialog::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape)
  {
    close();
    return;
  }
}
