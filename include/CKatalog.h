#ifndef __CKATALOG_H__
#define __CKATALOG_H__

#include <QtGui>
#include <string>

class Interface;
class CKatalog : public QApplication
{
    typedef QHash<QString, QTranslator*> Translators_t;

    Q_OBJECT

  public:
    // Configurations
    static const std::string s_ConfigFile;

    // Singleton pattern
    static CKatalog * getInstance();

    // Translators
    static void setLanguage(const QString& locale);

    static const QStringList availableLanguages();

    // Getters
    std::string getServer() const throw();
    int         getPort  () const throw();
    QString     getDefaultLanguage() const throw();

  private:
    CKatalog(int& argc, char* argv[]);

    // For Singleton pattern
    static CKatalog * s_Instance;

    // The main window in the interface
    Interface * m_MainWindow;

    // Translation
    static QTranslator *  s_Current;
    static Translators_t  s_Translators;
};

#include "CKatalog.hxx"

#endif
