#include "tictactoeboard.h"
#include "tictactoehelper.h"

#include <boost/test/unit_test.hpp>

using namespace ribi::tictactoe;

BOOST_AUTO_TEST_CASE(tictactoe_board)
{
  {
    //Check empty board state
    {
      Board t;
      const int s = t.GetSummarizedState();
      Board u(s);
      assert(u == t);
    }
    //Check one-move states
    for (int i=0; i!=9; ++i)
    {
      Board t;
      t.DoMove(i/3,i%3,Player::player1);
      const int s = t.GetSummarizedState();
      Board u(s);
      assert(u == t);
    }
    //Check two-move states
    for (int i=0; i!=8; ++i)
    {
      Board t;
      t.DoMove(i/3,i%3,Player::player1);
      t.DoMove(i/3,(i+1)%3,Player::player2);
      const int s = t.GetSummarizedState();
      Board u(s);
      assert(u == t);
    }
    //Check draw detection
    {
      Board t;
      t.DoMove(1,1,Player::player1);
      t.DoMove(0,0,Player::player2);
      t.DoMove(1,2,Player::player1);
      t.DoMove(1,0,Player::player2);
      t.DoMove(2,0,Player::player1);
      t.DoMove(0,2,Player::player2);
      t.DoMove(0,1,Player::player1);
      t.DoMove(2,1,Player::player2);
      t.DoMove(2,2,Player::player1);
      assert(t.GetWinner() == Winner::draw);
    }
    //Check player1 wins horizontally detection
    {
      Board t;
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,0,Player::player1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,0,Player::player2);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,1,Player::player1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,1,Player::player2);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,2,Player::player1);
      assert(t.GetWinner() == Winner::player1);
    }
    //Check player2 wins vertically detection
    {
      Board t;
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,0,Player::player1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,0,Player::player2);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,1,Player::player1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,1,Player::player2);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(2,2,Player::player1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,2,Player::player2);
      assert(t.GetWinner() == Winner::player2);
    }
    //Check player1 wins diagonally detection
    {
      Board t;
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,0,Player::player1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,0,Player::player2);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,1,Player::player1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,2,Player::player2);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(2,2,Player::player1);
      assert(t.GetWinner() == Winner::player1);
    }
    //Check no-winner detection
    {
      Board t;
      t.DoMove(1,1,Player::player1);
      t.DoMove(0,0,Player::player2);
      t.DoMove(1,2,Player::player1);
      t.DoMove(1,0,Player::player2);
      t.DoMove(2,0,Player::player1);
      t.DoMove(0,2,Player::player2);
      t.DoMove(0,1,Player::player1);
      t.DoMove(2,1,Player::player2);
      //t.DoMove(2,2); //Final move to make a draw
      assert(t.GetWinner() == Winner::no_winner);
    }
    //Check CanDoMove
    for (int i=0; i!=9; ++i)
    {
      Board t;
      t.DoMove(i/3,i%3,Player::player1);
      assert(!t.CanDoMove(i/3,i%3));
    }
    //Check all states
    for (int i=0; i!=Helper().IntPower(3,9); ++i)
    {
      try
      {
        Board t(i);
        assert(t.GetSummarizedState() == i);
      }
      catch (std::exception&)
      {
        //No problem
      }
    }
  }
}

