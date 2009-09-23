#include <QApplication>
#include <QtGui>

#include "CKatalog.h"

int main (int argc, char **argv)
{
    QApplication app(argc, argv);

    CKatalog::getInstance();
    
    return app.exec();

}
