#ifndef TICTACTOEAIS_H
#define TICTACTOEAIS_H

#include <vector>

#pragma GCC diagnostic push


#include <boost/shared_ptr.hpp>
#include "tictactoefwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace tictactoe {

///To work on Ai's
struct Ais
{
  Ais() {}
  std::vector<boost::shared_ptr<Ai>> GetAll() const noexcept;
};

} //~namespace tictactoe
} //~namespace ribi


#endif // TICTACTOEAIS_H
