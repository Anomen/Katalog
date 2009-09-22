#include "CThread.h"
#include "CFilm.h"
#include "util.h"
#include "CException.h"
#include "interface.h"

#include <iostream>
    
using namespace std;
using namespace nsCatac;

void CThread::askServer (const QString &FilmName)
{
    Write (string ("IMAGE " + FilmName.toStdString()));

    if (!_socket->waitForReadyRead (5000))
        return _int->information ("Le serveur ne répond pas.");

    //QPixmap *Img = new QPixmap;
    //Img->loadFromData (_resultat);

    emit imageReady (FilmName, _resultat);
}

void CThread::run()
{
    sleep(1);

    _socket = new QTcpSocket;
    QObject::connect (_socket, SIGNAL(readyRead()), this, SLOT(ready()), Qt::DirectConnection);

    _socket->connectToHost (_int->_serveur->text(), 
            _int->_port->text().toInt());

    if (_socket->waitForConnected(1000))
        connected();

    //exec();

}

void CThread::connected()
{
    for (Interface::VFilms_t::iterator i = _int->_VFilms.begin();
            i < _int->_VFilms.end(); i++)
    {
        QString name ((*i)->GetTitre().c_str());
        askServer (name);
    }
}

void CThread::Write (string Str)
{
    try {
        nsUtil::Write (_socket, Str);

    } catch (nsUtil::CException) { }
}

void CThread::ready()
{
    try {
        _resultat = nsUtil::Read (_socket);

    } catch (nsUtil::CException) { }

}
