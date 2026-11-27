#ifndef RIBI_QTHIDEANDSHOWDIALOG_H
#define RIBI_QTHIDEANDSHOWDIALOG_H

#include <QDialog>

namespace ribi {

///Dialog that lets parent dialog display children dialogs while being hidden
///from http://richelbilderbeek.nl/CppQtHideAndShowDialog.htm
class QtHideAndShowDialog : public QDialog
{
  Q_OBJECT //!OCLINT
    
public:
  explicit QtHideAndShowDialog(QWidget* parent = nullptr) noexcept;

  ///Virtual destructor as this is a base class
  virtual ~QtHideAndShowDialog();

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Hide the parent, show a child, show the parent
  void ShowChild(QtHideAndShowDialog * const dialog);

  ///Disable the parent, show a child, enable the parent
  void ShowModal(QtHideAndShowDialog * const dialog);

protected:
  ///Shows a child until it emits a close_me signal
  bool m_show_child;

  ///closeEvent that emits the close_me signal
  void closeEvent(QCloseEvent *) override;

  ///Close on escape key
  virtual void keyPressEvent(QKeyEvent* event) override;

signals:
  ///Emit the closeEvent of this dialog
  void close_me();

protected slots:
  ///Slot that needs to be called when a child signals close_me
  void close_child();

};

} //~namespace ribi

#endif // RIBI_QTHIDEANDSHOWDIALOG_H
