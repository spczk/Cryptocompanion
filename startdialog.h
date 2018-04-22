#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>
#include <QWidget>

#include "walletwidget.h"
#include "user.h"
#include "simplecrypt.h"

class QPushButton;

class StartDialog : public QDialog
{
    Q_OBJECT

public:
    StartDialog(QWidget *parent = 0);
    void onRegisterClick();

private:
    User user;
    SimpleCrypt simple;
    QPushButton *registerButton;
    QPushButton *startButton;
    QPushButton *quitButton;

};

#endif // STARTDIALOG_H
