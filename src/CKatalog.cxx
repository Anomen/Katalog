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

#include <iostream>

#include "CKatalog.h"
#include "CMainWindow.h"

using std::cout;

CKatalog *              CKatalog::s_Instance    = 0;
const std::string       CKatalog::s_ConfigFile  = "katalog.xml";
QTranslator *           CKatalog::s_Current     = 0;
CKatalog::Translators_t CKatalog::s_Translators;

CKatalog * CKatalog::getInstance()
{
    char *argv[1];
    int   argc = 1;
    return s_Instance ? s_Instance : (s_Instance = new CKatalog(argc, argv));
}

void CKatalog::setLanguage(const QString& locale)
{
    // remove previous
    if (s_Current)
        removeTranslator(s_Current);

    // install new
    s_Current = s_Translators.value(locale, 0);
    if (s_Current)
        installTranslator(s_Current);
}

CKatalog::CKatalog(int& argc, char* argv[])
    : QApplication(argc, argv)
{ 
    m_MainWindow = new Interface();
    m_MainWindow->show();

    // Load translations
    // <language>_<country>.qm
    QDir dir ("./lang");
    QString filter = "*_*.qm";
    QDir::Filters filters = QDir::Files | QDir::Readable;
    QDir::SortFlags sort = QDir::Name;
    QFileInfoList entries = dir.entryInfoList(QStringList() << filter, filters, sort);
    foreach (QFileInfo file, entries)
    {
        // pick country and language out of the file name
        QStringList parts = file.baseName().split("_");
        QString language = parts.at(parts.count() - 2).toLower();
        QString country  = parts.at(parts.count() - 1).toUpper();

        // construct and load translator
        QTranslator* translator = new QTranslator(instance());
        if (translator->load(file.absoluteFilePath()))
        {
            QString locale = language + "_" + country;
            s_Translators.insert(locale, translator);
        }
    }

    CKatalog::setLanguage(getDefaultLanguage());
}

const QStringList CKatalog::availableLanguages()
{
    return QStringList(s_Translators.keys());
}

std::string CKatalog::getServer() const throw()
{
    QString server;
    QFile file (QString::fromUtf8 (CKatalog::s_ConfigFile.c_str()));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";

    QTextStream in(&file);
    in >> server;

    file.close();
    return server.toStdString();
}

QString CKatalog::getDefaultLanguage() const throw()
{
    QString lang;
    QFile file (QString::fromUtf8 (CKatalog::s_ConfigFile.c_str()));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;

    QTextStream in(&file);
    in >> lang >> lang >> lang;

    file.close();
    return lang;
}

int CKatalog::getPort() const throw()
{
    QString port;
    QFile file (QString::fromUtf8 (CKatalog::s_ConfigFile.c_str()));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;

    QTextStream in(&file);
    in >> port >> port;

    file.close();
    return port.toInt();
}
