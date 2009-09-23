#include "CKatalog.h"
#include "CMainWindow.h"

CKatalog * CKatalog::s_Instance = 0;
const std::string CKatalog::s_ConfigFile = "katalog.xml";

CKatalog * CKatalog::getInstance()
{
    return s_Instance ? s_Instance : (s_Instance = new CKatalog);
}

CKatalog::CKatalog()
{ 
    m_MainWindow = new Interface();
    m_MainWindow->show();
}

std::string CKatalog::getServer() const throw()
{
    QString server;
    QFile file (QString::fromUtf8 (CKatalog::s_ConfigFile.c_str()));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";

    QTextStream in(&file);
    in >> server;

    file.close();
    return server.toStdString();
}

int CKatalog::getPort() const throw()
{
    QString port;
    QFile file (QString::fromUtf8 (CKatalog::s_ConfigFile.c_str()));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;

    QTextStream in(&file);
    in >> port >> port;

    file.close();
    return port.toInt();
}
