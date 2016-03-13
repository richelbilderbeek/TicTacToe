//---------------------------------------------------------------------------
/*
TicTacToe, tic-tac-toe game
Copyright (C) 2010-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/GameTicTacToe.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "sfmltictactoegamedialog.h"

#include <cassert>
#include <functional>
#include <stdexcept>

#include <boost/lambda/bind.hpp>

#include "tictactoegame.h"
#include "testtimer.h"
#include "tictactoewidget.h"
#include "sfmltictactoewinnerdialog.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::tictactoe::SfmlGameDialog::SfmlGameDialog(
  const boost::shared_ptr<Ai>& player1,
  const boost::shared_ptr<Ai>& player2
) : m_tictactoe(new Widget)
{
  #ifndef NDEBUG
  Test();
  #endif

  m_tictactoe->m_signal_has_winner.connect(
    boost::bind(&ribi::tictactoe::SfmlGameDialog::HasWinner,this,boost::lambda::_1)
  );

  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,3 * screen.width() / 4,3 * screen.height() / 4);
    this->move( screen.center() - this->rect().center() );
  }
}


std::string ribi::tictactoe::SfmlGameDialog::GetVersion() noexcept
{
  return "1.0";
}

void ribi::tictactoe::SfmlGameDialog::HasWinner(const QtTicTacToeWidget* const)
{

  QtTicTacToeWinnerDialog d;
  switch (m_tictactoe->GetWidget()->GetWinner())
  {
    case Winner::player1: d.SetWinnerCross(); break;
    case Winner::player2: d.SetWinnerCircle(); break;
    case Winner::draw: d.SetDraw(); break;
    case Winner::no_winner:
      assert(!"SfmlGameDialog::HasWinner: should not respond to no winner");
      throw std::logic_error("SfmlGameDialog::HasWinner: should not respond to no winner");
  }
  d.exec();
  m_tictactoe->Restart();
}

void ribi::tictactoe::SfmlGameDialog::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape)
  {
    close();
    return;
  }
}

#ifndef NDEBUG
void ribi::tictactoe::SfmlGameDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
