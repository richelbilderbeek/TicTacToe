#pragma GCC diagnostic push


#include "tictactoeboard.h"

#include <algorithm>
#include <cassert>
#include <cmath>

#include <iostream>
#include <stdexcept>

#include "tictactoehelper.h"
#pragma GCC diagnostic pop

///TicTacToe default contructor creates an empty board,
///where the current turn is to player1.
ribi::tictactoe::Board::Board() noexcept
  : m_signal_changed{},
    m_board(boost::extents[3][3])
{
  for (int i=0; i!=9; ++i)
  {
    m_board[i/3][i%3] = Square::empty;
  }
}

ribi::tictactoe::Board::Board(const int state)
  : m_signal_changed{},
    m_board(boost::extents[3][3])
{
  SetSummarizedState(state);
}

bool ribi::tictactoe::Board::CanDoMove(const int x, const int y) const noexcept
{
  if (!CanGetSquare(x,y)) return false;
  if (m_board[x][y] != Square::empty) return false;
  return true;
}

bool ribi::tictactoe::Board::CanGetSquare(const int x, const int y) const noexcept
{
  if (x < 0) return false;
  if (y < 0) return false;
  if (x >= 3) return false;
  if (y >= 3) return false;
  return true;
}

void ribi::tictactoe::Board::DoMove(const int x, const int y, const Player player) noexcept
{
  assert(CanDoMove(x,y));
  //std::clog << "Player " << m_current_player
  //  << ": (" << x << "," << y << ")\n";
  m_board[x][y] = Helper().PlayerToSquare(player);
  m_signal_changed(this);
}


ribi::tictactoe::Square ribi::tictactoe::Board::GetSquare(const int x, const int y) const noexcept
{
  assert(CanGetSquare(x,y));
  return m_board[x][y];
}

int ribi::tictactoe::Board::GetSummarizedState() const noexcept
{
  int z = SquareToState(m_board[0][0]);
  for (int i=1; i!=9; ++i)
  {
    z += (SquareToState(m_board[i/3][i%3]) * Helper().IntPower(3,i));
  }
  return z;
}

std::string ribi::tictactoe::Board::GetVersion() noexcept
{
  return "1.6";
}

std::vector<std::string> ribi::tictactoe::Board::GetVersionHistory() noexcept
{
  std::vector<std::string> v {
    "2010-09-19: version 1.3: made CanDoMove method a const member function",
    "2014-01-27: version 1.4: added ToTextCanvas",
    "2014-02-03: version 1.5: added m_signal_changed",
    "2014-03-17: version 1.6: use enum classes, use of noexcept, extracted Game"
  };
  return v;
}

ribi::tictactoe::Winner ribi::tictactoe::Board::GetWinner() const noexcept
{
  //Check rows
  for (int y=0; y!=3; ++y)
  {
    if (m_board[0][y] != Square::empty
     && m_board[0][y] == m_board[1][y]
     && m_board[1][y] == m_board[2][y])
      return Helper().SquareToWinner(m_board[0][y]);
  }
  //Check collumns
  for (int x=0; x!=3; ++x)
  {
    if (m_board[x][0] != Square::empty
     && m_board[x][0] == m_board[x][1]
     && m_board[x][1] == m_board[x][2])
       return Helper().SquareToWinner(m_board[x][0]);
  }
  //Check diagonal
  if (m_board[0][0] != Square::empty
   && m_board[0][0] == m_board[1][1]
   && m_board[1][1] == m_board[2][2])
    return Helper().SquareToWinner(m_board[1][1]);
  //Check other diagonal
  if (m_board[0][2] != Square::empty
   && m_board[0][2] == m_board[1][1]
   && m_board[1][1] == m_board[2][0])
    return Helper().SquareToWinner(m_board[1][1]);
  //Check for draw
  if (NoEmptySquares()) return Winner::draw;
  //No winner
  return Winner::no_winner;
}

bool ribi::tictactoe::Board::NoEmptySquares() const noexcept
{
  for (int i=0; i!=9; ++i)
  {
    if (m_board[i/3][i%3] == Square::empty) return false;
  }
  return true;
}



void ribi::tictactoe::Board::Restart() noexcept
{
  if (GetSummarizedState() == 0) return;

  for (int i=0; i!=9; ++i)
  {
    m_board[i/3][i%3] = Square::empty;
  }
  m_signal_changed(this);
}

void ribi::tictactoe::Board::SetBoard(const boost::multi_array<Square,2>& board) noexcept
{
  if (m_board == board) return;
  m_board = board;
  m_signal_changed(this);
}

void ribi::tictactoe::Board::SetSquare(
  const int x, const int y, const Square square_state) noexcept
{
  if (m_board[x][y] == square_state) return;

  m_board[x][y] = square_state;

  //Internal test
  assert(GetSquare(x,y)==square_state);

  m_signal_changed(this);
}

void ribi::tictactoe::Board::SetSummarizedState(const int original_state) noexcept
{
  if (GetSummarizedState() == original_state) return;

  assert(original_state >= 0);
  assert(original_state < Helper().IntPower(3,9));

  int s = original_state;
  for (int i=0; i!=9; ++i)
  {
    m_board[i/3][i%3] = StateToSquare(s % 3);
    s/=3;
  }

  //Internal check
  assert(GetSummarizedState()==original_state);

  m_signal_changed(this);
}

std::string ribi::tictactoe::Board::ToTextCanvas() const noexcept
{
  std::stringstream s;
  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      s << SquareToStr(GetSquare(x,y));
    }
    s << '\n';
  }
  std::string t{s.str()};
  assert(!t.empty());
  t.pop_back();
  return t;
}


std::ostream& ribi::tictactoe::operator<<(std::ostream& os,const ribi::tictactoe::Board& t) noexcept
{
  os
    << SquareToStr(t.GetSquare(0,0))
    << SquareToStr(t.GetSquare(1,0))
    << SquareToStr(t.GetSquare(2,0))
    << '\n'
    << SquareToStr(t.GetSquare(0,1))
    << SquareToStr(t.GetSquare(1,1))
    << SquareToStr(t.GetSquare(2,1))
    << '\n'
    << SquareToStr(t.GetSquare(0,2))
    << SquareToStr(t.GetSquare(1,2))
    << SquareToStr(t.GetSquare(2,2))
  ;
  return os;
}

bool ribi::tictactoe::operator==(const ribi::tictactoe::Board& lhs, const ribi::tictactoe::Board& rhs) noexcept
{
  return lhs.GetBoard() == rhs.GetBoard();
}
