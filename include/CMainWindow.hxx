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
