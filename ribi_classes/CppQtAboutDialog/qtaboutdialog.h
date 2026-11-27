#ifndef QTABOUTDIALOG_H
#define QTABOUTDIALOG_H

#include <string>
#include <vector>

#include "about.h"
#include "qthideandshowdialog.h"

namespace Ui {
  class QtAboutDialog;
}

namespace ribi {

///An About dialog
class QtAboutDialog : public QtHideAndShowDialog
{
  Q_OBJECT //!OCLINT

public:
  explicit QtAboutDialog(const ribi::About& about, QWidget* parent = nullptr) noexcept;
  QtAboutDialog(const QtAboutDialog&) = delete;
  QtAboutDialog& operator=(const QtAboutDialog&) = delete;
  virtual ~QtAboutDialog() noexcept;


  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

private:
  Ui::QtAboutDialog *ui;
};

} //~namespace ribi

#endif // QTABOUTDIALOG_H
