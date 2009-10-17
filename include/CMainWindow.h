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

#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <QtGui>
#include <QtNetwork>
#include "ui_main.h"
#include "CThread.h"
#include <vector>

namespace nsCatac { class CFilm; }
class Interface : public QMainWindow, public Ui::Main
{
    friend class CThread;
    Q_OBJECT

  public:
    typedef std::vector<nsCatac::CFilm*> VFilms_t;
    Interface (QWidget *parent = 0);
    VFilms_t            _VFilms;

  private:
    QTcpSocket         *_socket;
    QByteArray          _resultat;
    nsCatac::CThread   *_thr;

    void Write (std::string Cmd);

  protected:
    void changeEvent(QEvent* event);

  public slots:
    void on_actionConnect_triggered();
    void on_butFind_clicked();
    void on_butAdd_clicked();
    void on__treeResult_currentItemChanged (QTreeWidgetItem *, QTreeWidgetItem *);
    void on__liste_currentItemChanged (QTreeWidgetItem *, QTreeWidgetItem *);
    void information (QString Msg);
    void information (int NumErr);
    void connected();
    void disconnected();
    void ready();

    // Menu
    void on_actionSettings_triggered();
    void on_actionQuitter_triggered();
    
    void changeImage (const QString &FilmName, const QByteArray Image);

  signals:
    void error (int);

};

#include "CMainWindow.hxx"

#endif
