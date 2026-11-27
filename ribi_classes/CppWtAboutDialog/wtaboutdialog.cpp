#include "wtaboutdialog.h"

#include <string>

#include <Wt/WBreak.h>
#ifndef _WIN32
#include <Wt/WConfig.h>
#endif
#include <Wt/WLabel.h>
#include <Wt/WTextArea.h>

ribi::WtAboutDialog::WtAboutDialog(
  const About& about_original,
  const bool display_close_button)
  : m_signal_close{},
    m_button_close(new Wt::WPushButton)
{
  About about = about_original;
  about.AddLibrary("Wt version: " + GetWtVersion());
  about.AddLibrary("WtAboutDialog version: " + GetVersion());

  this->setContentAlignment(Wt::AlignmentFlag::Center);
  const int min_width = 800;
  //Display the general about text
  {
    const std::vector<std::string> v = about.CreateAboutText();
    for(const auto& s: v)
    {
      this->addWidget(std::make_unique<Wt::WLabel>(s.c_str()));
    }
  }
  this->addWidget(std::make_unique<Wt::WBreak>());
  //Display the libraries used text
  {
    auto text = std::make_unique<Wt::WTextArea>();
    {
      const std::vector<std::string> v = about.CreateLibrariesUsedText();
      std::string s;
      for(const auto& t: v) {  s+=t; s+="\n"; }
      text->setText(s);
    }
    text->setMinimumSize(min_width,100);
    text->setReadOnly(true);
    this->addWidget(std::move(text));
  }
  this->addWidget(std::make_unique<Wt::WBreak>());
  //Display the version history
  {
    auto text = std::make_unique<Wt::WTextArea>();
    {
      const std::vector<std::string> v = about.CreateVersionHistory();
      std::string s;
      for(const auto& t: v) {  s+=t; s+="\n"; }
      text->setText(s);
    }
    text->setMinimumSize(min_width,100);
    text->setReadOnly(true);
    this->addWidget(std::move(text));
  }
  this->addWidget(std::make_unique<Wt::WBreak>());
  //Display the licence text
  {
    auto text = std::make_unique<Wt::WTextArea>();
    {
      const std::vector<std::string> v = about.CreateLicenceText();
      std::string s;
      for(const auto& t: v) {  s+=t; s+="\n"; }
      text->setText(s);
    }
    text->setMinimumSize(min_width,100);
    text->setReadOnly(true);
    this->addWidget(std::move(text));
  }
  this->addWidget(std::make_unique<Wt::WBreak>());
  {
    const std::string s
      = std::string("Source code built at ")
      + std::string(__DATE__)
      + std::string(" ")
      + std::string(__TIME__)
    ;
    this->addWidget(std::make_unique<Wt::WLabel>(s.c_str()));
    this->addWidget(std::make_unique<Wt::WBreak>());
  }

  if (display_close_button)
  {
    this->addWidget(std::make_unique<Wt::WBreak>());
    m_button_close = addWidget(std::make_unique<Wt::WPushButton>());
    m_button_close->setText("Close");
    m_button_close->clicked().connect(
      this,&ribi::WtAboutDialog::OnClose);
  }
}

std::string ribi::WtAboutDialog::GetVersion()
{
  return "1.5";
}

std::vector<std::string> ribi::WtAboutDialog::GetVersionHistory()
{
  return {
    "2011-01-07: version 1.0: initial version",
    "2011-04-10: version 1.1: displays version numbers of Wt and WtAboutDialog",
    "2011-04-15: version 1.2: made displayal of Close button optional",
    "2011-05-24: version 1.3: made all text areas read-only",
    "2011-05-30: version 1.4: should build date and time",
    "2011-06-26: version 1.5: added newline for displaying build date and time"
  };
}

std::string ribi::WtAboutDialog::GetWtVersion()
{
  return WT_VERSION_STR;
}

void ribi::WtAboutDialog::OnClose()
{
  //emit that this dialog closes
  m_signal_close();
}

