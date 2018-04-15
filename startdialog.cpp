#include "startdialog.h"
#include "registerdialog.h"
#include "addresswidget.h"

#include <QtWidgets>



StartDialog::StartDialog(QWidget *parent) : QDialog(parent)
{
    registerButton = new QPushButton("Register");
    startButton = new QPushButton("Start");
    cancelButton = new QPushButton("Cancel");

    QGridLayout *gLayout = new QGridLayout;
    gLayout->setColumnStretch(3, 1);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(registerButton);
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 1, 3, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(registerButton, &QAbstractButton::clicked, this, &StartDialog::onRegisterClick);
    connect(startButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle("Cryptocompanion");

}

void StartDialog::onRegisterClick()
{
    RegisterDialog regist;

    if (regist.exec()) {
        QString firstName = regist.firstNameText->text();
        QString lastName = regist.lastNameText->text();
        QString password = regist.passwordText->text();

        QString fileName = QFileDialog::getSaveFileName(this);

        if (!fileName.isEmpty()){

            QFile file(fileName);

            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::information(this, tr("Unable to open file"), file.errorString());
                return;
            }

            //User user(firstName, lastName, password);

           // Cryptography crypto;
            SimpleCrypt simple;
            quint64 key = simple.generateKey();
            quint32 recoveryCode = simple.generateRecoveryCode();
            QString recovery = QString::number(recoveryCode);
            simple.setKey(key);

            QMessageBox::information(this, "Your recovery code", "Your recovery code, save it somewhere to be able to reset your password: \n\n" + recovery);

            QString encryptedFirstName= simple.encryptToString(firstName);
            QString encryptedLastName = simple.encryptToString(lastName);
            QString encryptedPassword = simple.encryptToString(password);
            QString encryptedRecoveryCode = simple.encryptToString(recovery);
            QDataStream out(&file);

            out << key << encryptedFirstName << encryptedLastName << encryptedPassword << encryptedRecoveryCode;
        }
        emit sendUserDetails(firstName, lastName, password);
    }
}

//void StartDialog::onStartClick()
//{
//    QString fileName = QFileDialog::getOpenFileName(this);

//    QFile file(fileName);

//    if (!file.open(QIODevice::ReadOnly)) {
//        QMessageBox::information(this, tr("Unable to open file"),
//            file.errorString());
//        return;
//    }


//    QString encryptedFirstName;
//    QString encryptedLastName;
//    QString encryptedPassword;
//    QString firstName;
//    QString lastName;
//    QString password;
//    quint64 key;
//    QDataStream in(&file);
//    in >> key >> encryptedFirstName >> encryptedLastName >> encryptedPassword;

//    SimpleCrypt simple(key);

//    firstName = simple.decryptToString(encryptedFirstName);
//    lastName = simple.decryptToString(encryptedLastName);
//    password = simple.decryptToString(encryptedPassword);

//    qInfo() << firstName << lastName << password;

//}
