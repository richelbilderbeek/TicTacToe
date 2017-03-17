#include "qttictactoemenudialog.h"

#include <cassert>
#include <boost/make_shared.hpp>

#include <QApplication>
#include <QDesktopWidget>

#include "qtaboutdialog.h"

#include "qttictactoecanvas.h"
#include "qttictactoegamedialog.h"
#include "qttictactoewidget.h"
#include "tictactoemenudialog.h"
#include "tictactoeai.h"

#include "ui_qttictactoemenudialog.h"

void QtTicTacToeMenuDialogTest() noexcept
{
  {
    const boost::shared_ptr<Ai> player1;
    const boost::shared_ptr<Ai> player2;
    QtTicTacToeGameDialog d(player1,player2);
    assert(!d.GetVersion().empty());
  }
  #ifdef SUPPORT_RETRO_VERSION_OF_TICTACTOE_AGAIN_20150918
  {
    QtCanvas * const qtcanvas {
      new QtTicTacToeCanvas
    };
    boost::scoped_ptr<QtCanvasDialog> d {
      new QtCanvasDialog(qtcanvas)
    };
    assert(d);
  }
  {
    const auto player1 = boost::make_shared<AiEnforceDraw>();
    const auto player2 = boost::make_shared<AiPlayRandom>();
    const QtTicTacToeWidget d(player1,player2);
    assert(!d.GetVersion().empty());
  }
  #endif // SUPPORT_RETRO_VERSION_OF_TICTACTOE_AGAIN_20150918
}
