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

#if !defined __CTHREAD_H__
#define      __CTHREAD_H__

#include <string>
#include <QtGui>
#include <QtNetwork>

class Interface;
namespace nsCatac
{
    class CThread : public QThread
    {
        Q_OBJECT

      public:
        CThread (Interface *Int = 0);

      public slots:
        void ready();
        void connected();
        void askServer (const QString &FilmName);

      signals:
        void imageReady (const QString&, const QByteArray);

      protected:
        void run();

      private:
        Interface  *_int;
        QTcpSocket *_socket;
        QByteArray  _resultat;

        void Write (std::string Str);
    };
}

#include "CThread.hxx"

#endif
