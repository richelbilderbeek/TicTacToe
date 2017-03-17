#include "tictactoegame.h"

#include <cassert>
#include <iostream>


#include "tictactoeai.h"
#include "tictactoeboard.h"
#include "tictactoehelper.h"

void GameTest() noexcept
{
  const bool verbose{false};
  {
    //Check draw detection
    {
      Game t;
      assert(t.GetCurrentPlayer() == Player::player1);
      assert(t.GetCurrentTurn()   == 0);
      t.DoMove(1,1);
      assert(t.GetCurrentPlayer() == Player::player2);
      assert(t.GetCurrentTurn()   == 1);
      t.DoMove(0,0);
      assert(t.GetCurrentPlayer() == Player::player1);
      assert(t.GetCurrentTurn()   == 2);
      t.DoMove(1,2);
      assert(t.GetCurrentPlayer() == Player::player2);
      assert(t.GetCurrentTurn()   == 3);
      t.DoMove(1,0);
      assert(t.GetCurrentPlayer() == Player::player1);
      assert(t.GetCurrentTurn()   == 4);
      t.DoMove(2,0);
      assert(t.GetCurrentPlayer() == Player::player2);
      assert(t.GetCurrentTurn()   == 5);
      t.DoMove(0,2);
      assert(t.GetCurrentPlayer() == Player::player1);
      assert(t.GetCurrentTurn()   == 6);
      t.DoMove(0,1);
      assert(t.GetCurrentPlayer() == Player::player2);
      assert(t.GetCurrentTurn()   == 7);
      t.DoMove(2,1);
      assert(t.GetCurrentPlayer() == Player::player1);
      assert(t.GetCurrentTurn()   == 8);
      t.DoMove(2,2);
      assert(t.GetCurrentPlayer() == Player::player2);
      assert(t.GetCurrentTurn()   == 9);
      assert(t.GetWinner() == Winner::draw);
    }
    //Check player1 wins horizontally detection
    {
      Game t;
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,0);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,0);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,2);
      assert(t.GetWinner() == Winner::player1);
    }
    //Check player2 wins vertically detection
    {
      Game t;
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,0);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,0);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(2,2);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,2);
      assert(t.GetWinner() == Winner::player2);
    }
    //Check player1 wins diagonally detection
    {
      Game t;
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,0);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,0);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,2);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(2,2);
      assert(t.GetWinner() == Winner::player1);
    }
    //Check no-winner detection
    {
      Game t;
      t.DoMove(1,1);
      t.DoMove(0,0);
      t.DoMove(1,2);
      t.DoMove(1,0);
      t.DoMove(2,0);
      t.DoMove(0,2);
      t.DoMove(0,1);
      t.DoMove(2,1);
      //t.DoMove(2,2); //Final move to make a draw
      assert(t.GetWinner() == Winner::no_winner);
    }
    //Check CanDoMove
    for (int i=0; i!=9; ++i)
    {
      Game t;
      t.DoMove(i/3,i%3);
      assert(t.CanDoMove(i/3,i%3)==false);
    }
    //Check AI's
    {
      for (int a = 0; a!=3; ++a)
      {
        for (int b = 0; b!=3; ++b)
        {
          boost::shared_ptr<Ai> c;
          switch (a)
          {
            case 0: c.reset(new AiEnforceDraw); break;
            case 1: c.reset(new AiEnforceWin); break;
            case 2: c.reset(new AiPlayRandom); break;
          }
          assert(c);
          boost::shared_ptr<Ai> d;
          switch (b)
          {
            case 0: d.reset(new AiEnforceDraw); break;
            case 1: d.reset(new AiEnforceWin); break;
            case 2: d.reset(new AiPlayRandom); break;
          }
          assert(d);
          Game g;
          while (g.GetWinner() == Winner::no_winner)
          {
            const std::pair<int,int> move_1(c->SuggestMove(g));
            assert(g.CanDoMove(move_1.first,move_1.second));
            g.DoMove(move_1.first,move_1.second);
            if (g.GetWinner() != Winner::no_winner) break;
            const std::pair<int,int> move_2(c->SuggestMove(g));
            assert(g.CanDoMove(move_2.first,move_2.second));
            g.DoMove(move_2.first,move_2.second);
          }
          if (verbose) { std::clog << WinnerToName(g.GetWinner()) << '\n'; }
        }
      }
    }
  }
}
