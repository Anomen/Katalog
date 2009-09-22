#include <iostream>
#include "util.h"

using namespace std;

void nsUtil::Write (QTcpSocket *socket, string Cmd) throw (nsUtil::CException)
{
    socket->write ((Cmd + "\nFIN").c_str(), Cmd.size()+4);
    if (!socket->waitForBytesWritten (5000))
        throw CException ("Le serveur ne répond pas.");
}

QByteArray nsUtil::Read (QTcpSocket *socket) throw (nsUtil::CException)
{
    QByteArray Res, NewRes;
    int i (0);
    while(1)
    {
        ++i;
        NewRes = socket->readAll();

        if (NewRes.size() == 0) break;

        Res.append (NewRes);
        if (NewRes.right(3) == "FIN") break;

        socket->waitForReadyRead(5000);

    }

    Res = Res.left(Res.size()-4);

    int point  (Res.indexOf ("\n"));
    int Statut (Res.left (point).toInt());

    if (Statut && Statut != 200)
        throw CException (Statut);

    if (Statut)
        Res.remove (0, point);

    return Res;

}
