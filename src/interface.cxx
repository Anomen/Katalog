#include "interface.h"
#include <iostream>
#include "CFilm.h"
#include "CException.h"
#include "util.h"

using namespace std;
using namespace nsCatac;

void Interface::information (QString Msg)
{
    QMessageBox::information (this, "Katalog", 
            QString::fromUtf8 (Msg.toStdString().c_str()));
}

void Interface::information (int NumErr)
{
    switch (NumErr)
    {
      case 301:
        information ("Erreur de connexion à la base de donnée.");
      break;

      case 302:
        information ("Erreur au niveau de la base de donnée.");
      break;

      case 303:
        information ("Aucun film trouvé.");
      break;

      case 304:
        information ("Film déjà ajouté dans la base de donnée.");
      break;

      case 305:
        information ("Erreur dans la ligne de commande.");
      break;

      case 306:
        information ("Erreur sur le choix du film (indice).");
      break;

      default:
        information ("Erreur iconnue (" + QString::number (NumErr) + ")");
      break;
    }
}

void Interface::Write (string Cmd)
{
    try {
        nsUtil::Write (_socket, Cmd);
    } catch (nsUtil::CException & e) {
        information (QString::fromUtf8(e.GetStr().c_str()));
    }

}

void Interface::on_butConnect_clicked()
{
    // Connexion au serveur
    //========================
    _socket->connectToHost (_serveur->text(), _port->text().toInt());
    Write ("LIST");

    if (!_socket->waitForReadyRead (5000))
        return information ("Le serveur ne répond pas.");

    QTextStream stream (QString(_resultat).toStdString().c_str());
    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        if (line.size() == 0) continue;

        int i (line.indexOf (" "));
        int Num (line.left (i).toInt());

        line.remove (0, i+1);

        CFilm *F = new CFilm (QString(line.toUtf8()).toStdString(), Num);
        _liste->addTopLevelItem (F);
        _VFilms.push_back (F);

    }

    // On permet l'ajout
    //======================
    tabAdd->setEnabled(true);
    butAdd->setEnabled(false);

    _thr->start();
}

void Interface::connected()
{
    _serveur  ->setEnabled (false);
    _port     ->setEnabled (false);
    butConnect->setEnabled (false);
    butDisconnect->setEnabled (true);
}

void Interface::disconnected()
{
    _serveur  ->setEnabled (true);
    _port     ->setEnabled (true);
    butConnect->setEnabled (true);
    butDisconnect->setEnabled (false);

    _texte->clear();
    _liste->clear();
    _treeResult->clear();
}

void Interface::ready()
{
    try {
        _resultat = nsUtil::Read (_socket);

    } catch (nsUtil::CException & e) {
        emit error (e.GetNum());

    }

}

void Interface::on_butFind_clicked()
{
    _messageAdd->setText (QString::fromUtf8("Recherche en cours..."));
    _treeResult->clear();
    butAdd->setEnabled(false);
    Write ("SEARCH " + _name->text().toStdString());

    if (!_socket->waitForReadyRead (5000))
        return information ("Le serveur ne répond pas.");

    QTextStream stream (QString(_resultat).toStdString().c_str());
    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        if (line.size() == 0) continue;

        int i (line.indexOf (" "));
        int Num (line.left (i).toInt());

        line.remove (0, i+1);

        CFilm *F = new CFilm (QString(line.toUtf8()).toStdString(), Num);
        _treeResult->addTopLevelItem (F);

    }

    _messageAdd->setText (QString::fromUtf8(""));
}

void Interface::on_butAdd_clicked()
{
    _messageAdd->setText (QString::fromUtf8("Ajout en cours..."));
    CFilm *F = reinterpret_cast<CFilm *> (_treeResult->currentItem());

    ostringstream oss;
    oss << "ADD " << F->GetTitre() << " " << 1;// F->GetNum();
    Write (oss.str());

    if (!_socket->waitForReadyRead (5000))
        return information ("Le serveur ne répond pas.");

    _VFilms.push_back (F);
    _liste->addTopLevelItem (F);
    _messageAdd->setText (QString::fromUtf8((F->GetTitre() + " ajouté.").c_str()));
}

void Interface::on__treeResult_currentItemChanged (QTreeWidgetItem *Item, QTreeWidgetItem *)
{
    butAdd->setEnabled(true);
}

void Interface::on__liste_currentItemChanged (QTreeWidgetItem *Item, QTreeWidgetItem *)
{
    if (!Item) return;

    CFilm *F = reinterpret_cast<CFilm *> (Item);
    string Req ("SHOW " + F->GetTitre());
    Write (Req);

    if (!_socket->waitForReadyRead (5000))
        return information ("Le serveur ne répond pas.");

    F->fromReq (QString(_resultat).toStdString());

    _texte->clear();
    _texte->setText (QString::fromUtf8 (F->Affich().c_str()));
}

void Interface::on_butDisconnect_clicked()
{
    _thr->terminate();
    _VFilms.clear();
    _socket->disconnectFromHost();

    // On interdit l'ajout
    //======================
    tabAdd->setEnabled(false);
}

void Interface::changeImage (const QString &FilmName, const QByteArray Image)
{
    CFilm *F = 0;
    for (VFilms_t::iterator i = _VFilms.begin();
            i < _VFilms.end();
            i++)
        if ((*i)->GetTitre() == FilmName.toStdString())
        {
            F = *i;
            break;
        }

    QPixmap *Img = new QPixmap;
    Img->loadFromData (Image);
    F->setIcon(0, QIcon(*Img));

}
