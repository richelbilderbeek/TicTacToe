#ifndef QTHIDEANDSHOWANDTHROWDIALOG_H
#define QTHIDEANDSHOWANDTHROWDIALOG_H





#include "qthideandshowdialog.h"


namespace ribi {

///A QtHideAndShowDialog that can throw
class QtHideAndShowAndThrowDialog : public QtHideAndShowDialog
{
public:
  QtHideAndShowAndThrowDialog(QWidget* parent = nullptr);

public slots:
  ///Throws an exception
  void do_throw();
};

} //~namespace ribi

#endif // QTHIDEANDSHOWANDTHROWDIALOG_H
