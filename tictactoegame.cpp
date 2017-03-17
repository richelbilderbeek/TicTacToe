#include "tictactoegame.h"

#include <cassert>
#include <iostream>

#include "tictactoeai.h"
#include "tictactoeboard.h"
#include "tictactoehelper.h"

ribi::tictactoe::Game::Game() noexcept
  : m_signal_changed{},
    m_board(new Board),
    m_current_player(Player::player1)

{
  assert(GetCurrentTurn() == 0);
}

bool ribi::tictactoe::Game::CanDoMove(const int x, const int y) const noexcept
{
  return GetBoard()->CanDoMove(x,y);
}

void ribi::tictactoe::Game::DoMove(const int x, const int y) noexcept
{
  assert(CanDoMove(x,y));
  m_board->DoMove(x,y,m_current_player);
  m_current_player = (m_current_player == Player::player1 ? Player::player2 : Player::player1);
}

boost::shared_ptr<const ribi::tictactoe::Board> ribi::tictactoe::Game::GetBoard() const noexcept
{
  assert(m_board);
  return m_board;
}

int ribi::tictactoe::Game::GetCurrentTurn() const noexcept
{
  int turn = 0;
  for (int i=0; i!=9; ++i)
  {
    if (GetBoard()->GetSquare(i/3,i%3) != Square::empty) ++turn;
  }
  return turn;
}

int ribi::tictactoe::Game::GetSummarizedState() const noexcept
{
  //MSB: player
  //LSB: board
  int z = m_board->GetSummarizedState();
  z += (PlayerToState(m_current_player) * Helper().IntPower(3,9));
  return z;
}

std::string ribi::tictactoe::Game::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::tictactoe::Game::GetVersionHistory() noexcept
{
  return {
    "2014-03-17: version 1.0: initial version, extracted from Board"
  };
}

ribi::tictactoe::Winner ribi::tictactoe::Game::GetWinner() const noexcept
{
  return GetBoard()->GetWinner();
}

void ribi::tictactoe::Game::Restart() noexcept
{
  m_board->Restart();

  if (m_current_player != Player::player1)
  {
    m_current_player = Player::player1;
    m_signal_changed(this);
  }
}

void ribi::tictactoe::Game::SetSummarizedState(const int original_state) noexcept
{
  if (GetSummarizedState() == original_state) return;

  //MSB: player
  //LSB: board

  //9 for the board, 1 for the current player
  assert(original_state < Helper().IntPower(3,9 + 1));

  int s = original_state;
  m_board->SetSummarizedState(s % Helper().IntPower(3,9));
  s /= Helper().IntPower(3,9);
  m_current_player = StateToPlayer(s);

  //Internal check
  assert(GetSummarizedState()==original_state);

  m_signal_changed(this);
}

std::string ribi::tictactoe::Game::ToTextCanvas() const noexcept
{
  return GetBoard()->ToTextCanvas();
}

std::ostream& ribi::tictactoe::operator<<(std::ostream& os,const ribi::tictactoe::Game& t) noexcept
{
  os << (*t.GetBoard());
  return os;
}

bool ribi::tictactoe::operator==(const ribi::tictactoe::Game& lhs, const ribi::tictactoe::Game& rhs) noexcept
{
  return *lhs.GetBoard() == *rhs.GetBoard()
      && lhs.GetCurrentPlayer() == rhs.GetCurrentPlayer()
  ;
}
