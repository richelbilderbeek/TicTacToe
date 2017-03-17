include(TicTacToeConsole.pri)

SOURCES += \
    $$PWD/qttictactoewinnerdialog.cpp \
    $$PWD/qttictactoemenudialog.cpp \
    $$PWD/qttictactoegamedialog.cpp \
    $$PWD/qttictactoecanvas.cpp

HEADERS  += \
    $$PWD/qttictactoewinnerdialog.h \
    $$PWD/qttictactoemenudialog.h \
    $$PWD/qttictactoegamedialog.h \
    $$PWD/qttictactoecanvas.h

FORMS += \
    $$PWD/qttictactoewinnerdialog.ui \
    $$PWD/qttictactoemenudialog.ui \
    $$PWD/qttictactoegamedialog.ui
