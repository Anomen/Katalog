#ifndef __CKATALOG_H__
#define __CKATALOG_H__

#include <string>

class Interface;
class CKatalog
{
  public:
    // Configurations
    static const std::string s_ConfigFile;

    // Singleton pattern
    static CKatalog * getInstance();

    std::string getServer() const throw();
    int         getPort  () const throw();

  private:
    CKatalog();

    // For Singleton pattern
    static CKatalog * s_Instance;

    // The main window in the interface
    Interface * m_MainWindow;
};

#include "CKatalog.hxx"

#endif
