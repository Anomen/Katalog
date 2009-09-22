#include <QApplication>
#include <QtGui>

#include "interface.h"

int main (int argc, char **argv)
{
    QApplication app(argc, argv);

    Interface Int;
    Int.show();
    
    return app.exec();

}
