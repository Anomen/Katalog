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
#include "CSettingWindow.h"
#include "CKatalog.h"

CSettingWindow::CSettingWindow (QWidget * parent /* = 0 */)
    : QDialog (parent)
{
    setupUi (this);
    serverEdit->setText(QString::fromStdString(CKatalog::getInstance()->getServer()));
    portEdit  ->setText(QString::number(CKatalog::getInstance()->getPort  ()));

    _languages->insertItem (0, "fr_FR");
    _languages->insertItems (1, CKatalog::availableLanguages());
    _languages->setCurrentIndex (_languages->findText(
                CKatalog::getInstance()->getDefaultLanguage()));

    //int num (1);
    //QStringList Langs = CKatalog::availableLanguages();
    //for (QStringList::iterator i = Langs.begin();
    //        i != Langs.end(); i++)
    //    _languages->insertItem (num++, *i);
}

void CSettingWindow::on_buttonBox_accepted()
{
    QFile file (QString::fromStdString(CKatalog::s_ConfigFile));

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    out << serverEdit->text() << "\n"
        << portEdit->text() << "\n"
        << _languages->currentText();

    file.close();

    CKatalog::setLanguage(_languages->currentText());
}
