#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H


#include <QDialog>

class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = 0);
    QLineEdit *nameText;
    QLineEdit *passwordText;

private:
    QLabel *nameLabel;
    QLabel *passwordLabel;
    QPushButton *loginButton;
    QPushButton *cancelButton;
};

#endif // LOGINDIALOG_H
