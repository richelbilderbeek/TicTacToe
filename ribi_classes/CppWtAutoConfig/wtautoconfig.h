#ifndef WTAUTOCONFIG_H
#define WTAUTOCONFIG_H

#include <string>
#include <vector>
#include <memory>

namespace Wt
{
  struct WApplication;
  struct WEnvironment;
}

namespace ribi {

///WtAutoConfig is a class to automatically start a Wt
///server in a default configuration.
struct WtAutoConfig
{
  typedef std::unique_ptr<Wt::WApplication> (*FunctionType)(const Wt::WEnvironment&);

  WtAutoConfig(const int argc, char ** const argv, const FunctionType function);
  int Run();

  private:
  const int m_argc;
  char ** const m_argv; //m_argv must be non-const for boost::program_options::parse_command_line
  const FunctionType m_function;

  public:
  static std::vector<std::string> CreateDefaultStylesheet();

  ///Obtain the version of this class
  static std::string GetVersion();

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory();
  static void SaveDefaultStylesheet();

};

} //~namespace ribi

#endif // WTAUTOCONFIG_H
