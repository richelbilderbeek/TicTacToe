win32 {
  # Windows only
  message("Boost, all libraries, built for Windows")

  #LIBS += -L/home/richel/GitHubs/RibiLibraries/mxe/usr/i686-w64-mingw32.static/lib
  #LIBS += -L/home/richel/GitHubs/RibiLibraries/mxe/usr/i686-w64-mingw32.static/qt5/lib/
  #LIBS += -L/home/richel/GitHubs/RibiLibraries/mxe/usr/i686-w64-mingw32.static/lib
  #LIBS += -L/home/richel/GitHubs/RibiLibraries/mxe/usr/i686-w64-mingw32.static
  #LIBS += -L/C:/boost_1_62_0/bin.v2/libs \
  #INCLUDEPATH += C:/boost_1_62_0

  LIBS += \
    -lboost_date_time-mt \
    -lboost_filesystem-mt \
    -lboost_graph-mt \
    -lboost_locale-mt \
    -lboost_program_options-mt \
    -lboost_regex-mt \
    -lboost_signals-mt \
    -lboost_system-mt
}

macx {
  # Mac only
  message("Boost, all libraries, built for Mac")
  INCLUDEPATH += \
    ../../Libraries/boost_1_55_0
  LIBS += \
    -lboost_date_time \
    -lboost_filesystem \
    -lboost_graph \
    -lboost_locale \
    -lboost_program_options \
    -lboost_regex \
    -lboost_signals \
    -lboost_system
}

unix:!macx{
  # Linux only
  message("Boost, all libraries, built for Linux")
  INCLUDEPATH += \
    ../../Libraries/boost_1_55_0
  LIBS += \
    -lboost_date_time \
    -lboost_filesystem \
    -lboost_graph \
    -lboost_locale \
    -lboost_program_options \
    -lboost_regex \
    -lboost_system
}

