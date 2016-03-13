#!/bin/bash
cd ..
pwd
ls
git clone https://github.com/richelbilderbeek/RibiClasses
git clone https://github.com/richelbilderbeek/RibiLibraries
cd TicTacToe
qmake TicTacToeConsole.pro
make
qmake TicTacToeDesktopQt.pro
make
qmake TicTacToeDesktopSfml.pro
make
qmake TicTacToeWebsite.pro
make
