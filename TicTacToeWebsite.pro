include(../RibiLibraries/BoostAll.pri)
include(../RibiLibraries/Wt.pri)
include(../RibiLibraries/WebApplication.pri)

include(../RibiLibraries/GeneralConsole.pri)
include(../RibiLibraries/GeneralWeb.pri)

#Specific, console
include(../RibiClasses/CppCanvas/CppCanvas.pri)
include(../DotMatrix/DotMatrix.pri)
include(../RibiClasses/CppImageCanvas/CppImageCanvas.pri)
include(../RibiClasses/CppTextCanvas/CppTextCanvas.pri)
include(../RibiClasses/CppTicTacToe/CppTicTacToe.pri)

#Specific, web
include(../RibiClasses/CppWtTicTacToeWidget/CppWtTicTacToeWidget.pri)
include(TicTacToeWebsite.pri)

SOURCES += wtmain.cpp
