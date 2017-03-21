#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "tictactoemenudialog.h"

#include <boost/test/unit_test.hpp>

using namespace ribi::tictactoe;

BOOST_AUTO_TEST_CASE(tictactoe_menu_dialog)
{
  TicTacToeMenuDialog d;
  BOOST_CHECK_NO_THROW(
    d.Execute( { "TicTacToeMenuDialog","--1h","--2h", "--silent" } )
  );
}
