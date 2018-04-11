#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H


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
    QLineEdit *firstNameText;
    QLineEdit *lastNameText;
    QLineEdit *passwordText;

private:
    QLabel *firstNameLabel;
    QLabel *lastNameLabel;
    QLabel *passwordLabel;
    QPushButton *registerButton;
    QPushButton *cancelButton;
};

#endif // REGISTERDIALOG_H
