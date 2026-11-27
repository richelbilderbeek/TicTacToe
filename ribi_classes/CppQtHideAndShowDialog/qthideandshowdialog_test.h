#ifndef RIBI_QTHIDEANDSHOWDIALOG_TEST_H
#define RIBI_QTHIDEANDSHOWDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {

class QtHideAndShowDialogTest : public QObject
{
    Q_OBJECT

private slots:
  void default_construct();
  void parent_can_show_child();
  void parent_can_show_potentially_throwing_child();

  ///From https://github.com/richelbilderbeek/Brainweaver/issues/84
  void destroy_cleanly_upon_exception_in_derived_class();
};

} //~namespace ribi

#endif // RIBI_QTHIDEANDSHOWDIALOG_TEST_H
