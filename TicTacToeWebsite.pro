include(../RibiLibraries/BoostAll.pri)

include(../RibiClasses/CppAbout/CppAbout.pri)
include(../RibiClasses/CppFileIo/CppFileIo.pri)
include(../RibiClasses/CppHelp/CppHelp.pri)
include(../RibiClasses/CppMenuDialog/CppMenuDialog.pri)
include(../RibiClasses/CppWtAboutDialog/CppWtAboutDialog.pri)
include(../RibiClasses/CppWtAutoConfig/CppWtAutoConfig.pri)

#Specific, console
include(../RibiClasses/CppCanvas/CppCanvas.pri)
include(../DotMatrix/DotMatrix.pri)
include(../RibiClasses/CppImageCanvas/CppImageCanvas.pri)
include(../RibiClasses/CppTextCanvas/CppTextCanvas.pri)
include(../RibiClasses/CppTicTacToe/CppTicTacToe.pri)

#Specific, web
include(../RibiClasses/CppWtTicTacToeWidget/CppWtTicTacToeWidget.pri)
include(TicTacToe.pri)
include(TicTacToeWebsite.pri)

SOURCES += wtmain.cpp

# C++14
CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14

# High warning levels
# Qt and -Weffc++
QMAKE_CXXFLAGS += -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Werror

# Debug and release mode
CONFIG += debug_and_release

# In release mode, define NDEBUG
CONFIG(release, debug|release) {

  DEFINES += NDEBUG
}

# In debug mode, turn on gcov and UBSAN
CONFIG(debug, debug|release) {

  # gcov
  QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
  LIBS += -lgcov

  # UBSAN
  QMAKE_CXXFLAGS += -fsanitize=undefined
  QMAKE_LFLAGS += -fsanitize=undefined
  LIBS += -lubsan
}

# Qt
QT += core gui widgets

# Prevent Qt for failing with this error:
# qrc_[*].cpp:400:44: error: ‘qInitResources_[*]__init_variable__’ defined but not used
# [*]: the resource filename
QMAKE_CXXFLAGS += -Wno-unused-variable

# Fixes
#/usr/include/boost/math/constants/constants.hpp:277: error: unable to find numeric literal operator 'operator""Q'
#   BOOST_DEFINE_MATH_CONSTANT(half, 5.000000000000000000000000000000000000e-01, "5.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-01")
#   ^
QMAKE_CXXFLAGS += -fext-numeric-literals

# Wt
LIBS += -lwt -lwthttp
DEFINES += BOOST_SIGNALS_NO_DEPRECATION_WARNING
