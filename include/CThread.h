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
