#ifndef __SETTING_WINDOW_H__
#define __SETTING_WINDOW_H__

#include <QtGui>
#include "ui_settings.h"

class CSettingWindow : public QDialog, public Ui::Setting
{
    Q_OBJECT

  public:
    CSettingWindow (QWidget *parent = 0);

  public slots:
    void on_buttonBox_accepted();
    //void on_buttonBox_rejected();

};

#endif
