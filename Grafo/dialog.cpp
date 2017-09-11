#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

void Dialog::result(string val)
{
    QString qstr = QString::fromStdString(val);
    ui->brow_result->setText(qstr);
}

Dialog::~Dialog()
{
    delete ui;
}
