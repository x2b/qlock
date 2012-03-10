#include <csignal>
using namespace std;

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QMessageBox>

#include "AuthCreator.hpp"
#include "AuthVerifier.hpp"

void usage()
{
  qWarning() << "Usage: qlock [options]" << endl
    << "Available options:" << endl
    << "-c, --create\t create new password file" << endl
    << "-d, --debug\t launch qlock without grabbing "
      "mouse or keyboard" << endl
    << "-h, --help\t display this help"
    << endl; 
}

int main(int argc, char** argv)
{
  QStringList args;
  QStringList::const_iterator it;
  bool create = false;
  bool debug  = false;
  QWidget* window = 0;
  int r; 
  
  QDir::setCurrent(QDir::homePath());
  QApplication app(argc, argv);
  
  signal(SIGTERM, SIG_IGN);
  
  args = QCoreApplication::arguments();
  
  for(it = args.begin() + 1; it != args.end(); ++it)
  {
    if("-c" == *it || "--create" == *it)
    {
      create = true;
    }
    else if("-d" == *it || "--debug" == *it)
    {
      debug = true;
    }
    else if("-h" == *it || "--help" == *it)
    {
      usage();
      return 0;
    }
    else
    {
      qWarning() << "Unknow option: " << *it;
      usage();
      return 1;
    }
  }
  
  if(!create)
  {
    try
    {
      window = new AuthVerifier();
    }
    catch(exception e)
    {
      qCritical("Can't open password file");
      QMessageBox::critical(0, "Can't open password file",
        "Unable to read password file, please make sure that "
        "the file exists and is readable");
      return 1;
    }
  }
  else
  {
    window = new AuthCreator();
  }
  
  if(!(debug || create))
  {
    window->showFullScreen();
    window->grabMouse();
    window->grabKeyboard();
  }
  else
  {
    window->show();
  }
  
  r = app.exec();
  delete window;
  return r;
}
