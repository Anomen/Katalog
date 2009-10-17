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

#ifndef __CKATALOG_H__
#define __CKATALOG_H__

#include <QtGui>
#include <string>

class Interface;
class CKatalog : public QApplication
{
    typedef QHash<QString, QTranslator*> Translators_t;

    Q_OBJECT

  public:
    // Configurations
    static const std::string s_ConfigFile;

    // Singleton pattern
    static CKatalog * getInstance();

    // Translators
    static void setLanguage(const QString& locale);

    static const QStringList availableLanguages();

    // Getters
    std::string getServer() const throw();
    int         getPort  () const throw();
    QString     getDefaultLanguage() const throw();

  private:
    CKatalog(int& argc, char* argv[]);

    // For Singleton pattern
    static CKatalog * s_Instance;

    // The main window in the interface
    Interface * m_MainWindow;

    // Translation
    static QTranslator *  s_Current;
    static Translators_t  s_Translators;
};

#include "CKatalog.hxx"

#endif
