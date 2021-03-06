



#include "tictactoewidget.h"

#include <cassert>
#include <sstream>
#include "tictactoegame.h"


ribi::tictactoe::Widget::Widget()
  : m_signal_changed{},
    m_game{new Game},
    m_x{1},
    m_y{1}
{

}

bool ribi::tictactoe::Widget::CanSelect(const int x, const int y) const noexcept
{
  return GetGame()->CanDoMove(x,y);
}

void ribi::tictactoe::Widget::DoMove() noexcept
{
  assert(GetGame()->CanDoMove(m_x,m_y));
  m_game->DoMove(m_x,m_y);
}

ribi::tictactoe::Player ribi::tictactoe::Widget::GetCurrentPlayer() const noexcept
{
  return GetGame()->GetCurrentPlayer();
}

int ribi::tictactoe::Widget::GetSummarizedState() const noexcept
{
  return GetGame()->GetSummarizedState();
}

std::string ribi::tictactoe::Widget::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::tictactoe::Widget::GetVersionHistory() noexcept
{
  std::vector<std::string> v {
    "2014-xx-xx: version 1.0: initial version, in GameTicTacToe folder",
    "2014-03-17: version 1.1: moved from the game TicTacToe to CppTicTacToeFolder, improved interface"
  };
  return v;
}

ribi::tictactoe::Winner ribi::tictactoe::Widget::GetWinner() const noexcept
{
  return GetGame()->GetWinner();
}

void ribi::tictactoe::Widget::PressKey(const ribi::tictactoe::Key key) noexcept
{
  switch (key)
  {
    case Key::up    : if (m_y > 0) --m_y; m_signal_changed(); break;
    case Key::right : if (m_x < 2) ++m_x; m_signal_changed(); break;
    case Key::down  : if (m_y < 2) ++m_y; m_signal_changed(); break;
    case Key::left  : if (m_x > 0) --m_x; m_signal_changed(); break;
    case Key::select:
    {
      if (m_game->CanDoMove(m_x,m_y))
      {
        m_game->DoMove(m_x,m_y);
        m_signal_changed();
      }
    }
    break;
  }
}

void ribi::tictactoe::Widget::Restart() noexcept
{
  m_game->Restart();
}

void ribi::tictactoe::Widget::Select(const int x, const int y) noexcept
{
  assert(CanSelect(x,y));
  if (m_x != x || m_y != y)
  {
    m_x = x;
    m_y = y;
    m_signal_changed();
  }
}

std::string ribi::tictactoe::Widget::ToTextCanvas() const noexcept
{
  std::string canvas {m_game->ToTextCanvas()};

  if (m_game->GetWinner() == Winner::player1
   || m_game->GetWinner() == Winner::player2)
  {
    std::stringstream s;
    for (int i=0; i!=3; ++i)
    {
      for (int j=0; j!=3; ++j)
      {
        s << (m_game->GetWinner() == Winner::player1 ? 'X': 'O');
      }
      s << '\n';
    }
    canvas = s.str();
    assert(!canvas.empty());
    canvas.pop_back();
  }

  //Add selectdeness
  const int cursor_pos = (m_y * 4) + m_x;
  assert(cursor_pos >= 0);
  assert(cursor_pos < static_cast<int>(canvas.size()));
  const char c =  canvas[cursor_pos];
  char d = ' ';
  switch (c)
  {
    case ' ': d = '.'; break;
    case '.': d = ' '; break;
    case 'O': d = 'o'; break;
    case 'X': d = 'x'; break;
    case 'o': d = 'O'; break;
    case 'x': d = 'X'; break;
  }

  canvas[cursor_pos] = d;
  return canvas;
}
