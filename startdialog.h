#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>
#include <QWidget>

#include "addresswidget.h"
#include "user.h"
#include "simplecrypt.h"
#include "cryptography.h"

class QPushButton;

class StartDialog : public QDialog, public Cryptography
{
    Q_OBJECT

public:
    StartDialog(QWidget *parent = 0);

public slots:
    void onRegisterClick();
    //void onStartClick();

signals:
    void sendUserDetails(QString firstName, QString lastName, QString password);
    void sendFileDetails();
private:
    User user;
    SimpleCrypt simple;
    Cryptography crypto;
    QPushButton *registerButton;
    QPushButton *startButton;
    QPushButton *cancelButton;

};

#endif // STARTDIALOG_H
