#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <QtGui>
#include <QtNetwork>
#include "ui_interface.h"
#include "CThread.h"
#include <vector>

namespace nsCatac { class CFilm; }
class Interface : public QMainWindow, public Ui::Interface
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

  public slots:
    void on_butConnect_clicked();
    void on_butDisconnect_clicked();
    void on_butFind_clicked();
    void on_butAdd_clicked();
    void on__treeResult_currentItemChanged (QTreeWidgetItem *, QTreeWidgetItem *);
    void on__liste_currentItemChanged (QTreeWidgetItem *, QTreeWidgetItem *);
    void information (QString Msg);
    void information (int NumErr);
    void connected();
    void disconnected();
    void ready();
    
    void changeImage (const QString &FilmName, const QByteArray Image);

  signals:
    void error (int);

};

#include "interface.hxx"

#endif
