#include <iostream>
#include "CSettingWindow.h"
#include "CKatalog.h"

CSettingWindow::CSettingWindow (QWidget * parent /* = 0 */)
    : QDialog (parent)
{
    setupUi (this);
    serverEdit->setText(QString::fromStdString(CKatalog::getInstance()->getServer()));
    portEdit  ->setText(QString::number(CKatalog::getInstance()->getPort  ()));
}

void CSettingWindow::on_buttonBox_accepted()
{
    QFile file (QString::fromStdString(CKatalog::s_ConfigFile));

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    out << serverEdit->text() << "\n"
        << portEdit->text();

    file.close();

}
