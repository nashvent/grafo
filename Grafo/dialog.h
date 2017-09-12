#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "node.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    void result(string);
    ~Dialog();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
