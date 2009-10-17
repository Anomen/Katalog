/*
 * This file is part of Katalog.
 * Copyright (C) 2008-2009  Kevin Vicrey <kevin.vicrey@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "CThread.h"
#include "CFilm.h"
#include "CKatalog.h"
#include "util.h"
#include "CException.h"
#include "CMainWindow.h"

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

    _socket->connectToHost (QString::fromStdString(CKatalog::getInstance()->getServer()), 
            CKatalog::getInstance()->getPort());

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
