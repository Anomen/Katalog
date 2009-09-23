#ifndef __INTERFACE_HXX__
#define __INTERFACE_HXX__

inline Interface::Interface (QWidget *parent /* = 0 */)
    : QMainWindow (parent) 
{
    _thr = new nsCatac::CThread (this);
    setupUi (this);
    _socket    = new QTcpSocket (this);

    _liste->sortItems (0, Qt::AscendingOrder);

    QObject::connect (_socket, SIGNAL(connected()), this, SLOT(connected()));
    QObject::connect (_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    QObject::connect (_socket, SIGNAL(readyRead()), this, SLOT(ready()));
    QObject::connect (this   , SIGNAL(error(int)) , this, SLOT(information(int)));

    QObject::connect (_thr, SIGNAL(imageReady(const QString&, const QByteArray)),
            this, SLOT(changeImage(const QString&, const QByteArray)));

}

#endif
