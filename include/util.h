#ifndef __UTIL_H__
#define __UTIL_H__

#include <QtGui>
#include <QtNetwork>
#include <string>
#include "CException.h"

namespace nsUtil
{
    void Write (QTcpSocket *socket, std::string Cmd) throw (nsUtil::CException);
    QByteArray Read (QTcpSocket *socket) throw (nsUtil::CException);
}

#endif
