#ifndef CRYPTOCOMPANION_H
#define CRYPTOCOMPANION_H

#include <QMainWindow>
#include "secdialog.h"
#include "user.h"

namespace Ui {
class Cryptocompanion;
}

class Cryptocompanion : public QMainWindow
{
    Q_OBJECT

public:
    explicit Cryptocompanion(QWidget *parent = 0);
    ~Cryptocompanion();


private slots:
    void on_loginButton_clicked();

    void on_registerButton_clicked();


private:
    Ui::Cryptocompanion *ui;
    SecDialog *secDialog;
};

#endif // CRYPTOCOMPANION_H
