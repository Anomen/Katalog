#include <QApplication>
#include <QtGui>

#include "CKatalog.h"

int main (int argc, char **argv)
{
    //QApplication app(argc, argv);

    //CKatalog::translator.load("lang/katalog_en");
    //app.installTranslator(&CKatalog::translator);

    //CKatalog::getInstance();
    
    return CKatalog::getInstance()->exec();
    
    //return app.exec();

}
