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
