#include "cryptocompanion.h"
#include "ui_cryptocompanion.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QPixmap>


Cryptocompanion::Cryptocompanion(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Cryptocompanion)
{
    ui->setupUi(this);
}

Cryptocompanion::~Cryptocompanion()
{
    delete ui;
}


//void Cryptocompanion::loadTextFile()
//  {
//      QFile inputFile(":/input.txt");
//      inputFile.open(QIODevice::ReadOnly);

//      QTextStream in(&inputFile);
//      QString line = in.readAll();
//      inputFile.close();

//      ui->textEdit->setPlainText(line);
//      QTextCursor cursor = ui->textEdit->textCursor();
//      cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);
//  }

void Cryptocompanion::on_loginButton_clicked()
{
    QString Name = ui->Name_lineEdit->text();
    QString password = ui->login_password_lineEdit->text();

    if(Name ==  "Jan Kowalski" && password == "test") {
        QMessageBox::information(this, "Login", "Succesful Login!");
        hide();
        secDialog = new SecDialog(this);
        secDialog->show();
    }
    else {
        QMessageBox::warning(this,"Login", "Name and password is not correct");
    }
}

void Cryptocompanion::on_registerButton_clicked()
{


    QMessageBox::information(this, "Register", "Succesful Register!");
    hide();
    secDialog = new SecDialog(this);
    secDialog->show();
    User user;
    user.setFirstName(ui->firstName_lineEdit->text());
    user.setLastName(ui->lastName_lineEdit->text());
    user.setPassword(ui->register_password_lineEdit->text());
}

