include(../RibiLibraries/BoostAll.pri)

include($$PWD/ribi_classes/CppAbout/CppAbout.pri)
include($$PWD/ribi_classes/CppFileIo/CppFileIo.pri)
include($$PWD/ribi_classes/CppHelp/CppHelp.pri)
include($$PWD/ribi_classes/CppMenuDialog/CppMenuDialog.pri)
include($$PWD/ribi_classes/CppWtAboutDialog/CppWtAboutDialog.pri)
include($$PWD/ribi_classes/CppWtAutoConfig/CppWtAutoConfig.pri)

#Specific, console
include($$PWD/ribi_classes/CppCanvas/CppCanvas.pri)
include(../DotMatrix/DotMatrix.pri)
include($$PWD/ribi_classes/CppImageCanvas/CppImageCanvas.pri)
include($$PWD/ribi_classes/CppTextCanvas/CppTextCanvas.pri)

#Specific, web
include($$PWD/ribi_classes/CppWtTicTacToeWidget/CppWtTicTacToeWidget.pri)
include(TicTacToe.pri)
include(TicTacToeWebsite.pri)

SOURCES += wtmain.cpp


CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

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
