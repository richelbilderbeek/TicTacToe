#include "qthideandshowdialog.h"

#include <cassert>
#include <QApplication>
#include <QKeyEvent>

ribi::QtHideAndShowDialog::QtHideAndShowDialog(QWidget* parent) noexcept
  : QDialog(parent),
    m_show_child { false }
{

}

ribi::QtHideAndShowDialog::~QtHideAndShowDialog()
{

}

void ribi::QtHideAndShowDialog::close_child()
{
  m_show_child = false;
}

void ribi::QtHideAndShowDialog::closeEvent(QCloseEvent*)
{
  //QDialog::closeEvent(event); //Not needed
  emit close_me();
  //QDialog::closeEvent(event); //Not needed
}

std::string ribi::QtHideAndShowDialog::GetVersion() noexcept
{
  return "1.4";
}

std::vector<std::string> ribi::QtHideAndShowDialog::GetVersionHistory() noexcept
{
  std::vector<std::string> v {
    "2012-11-13: version 1.0: initial version",
    "2012-11-18: version 1.1: added ShowModal member function",
    "2012-11-18: version 1.2: added ",
    "2012-12-31: version 1.3: added keyPressEvent to close on escape"
    "2013-09-16: version 1.4: noexcept"
  };
  return v;
}

void ribi::QtHideAndShowDialog::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Escape)
  {
    close();
    return;
  }
  QDialog::keyPressEvent(event);
}

void ribi::QtHideAndShowDialog::ShowChild(QtHideAndShowDialog * const dialog)
{
  assert(dialog);
  this->hide();
  #if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
  QObject::connect(
    dialog,
    &ribi::QtHideAndShowDialog::close_me,
    this,
    &ribi::QtHideAndShowDialog::close_child
  );
  #else
  QObject::connect(
    dialog,
    SIGNAL(close_me()),
    this,
    SLOT(close_child())
  );
  #endif

  m_show_child = true;
  while (m_show_child)
  {
    dialog->exec();
    qApp->processEvents();
  }
  this->show();
}

void ribi::QtHideAndShowDialog::ShowModal(QtHideAndShowDialog * const dialog)
{
  assert(dialog);
  this->setEnabled(false);
  #if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
  QObject::connect(
    dialog,
    &ribi::QtHideAndShowDialog::close_me,
    this,
    &ribi::QtHideAndShowDialog::close_child
  );
  #else
  QObject::connect(
    dialog,
    SIGNAL(close_me()),
    this,
    SLOT(close_child())
  );
  #endif
  m_show_child = true;
  while (m_show_child)
  {
    dialog->exec();
  }
  this->setEnabled(true);
}
