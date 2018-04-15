#ifndef CHANGEPASSWORDDIALOG_H
#define CHANGEPASSWORDDIALOG_H


#include <QDialog>

class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;

class ChangePasswordDialog : public QDialog
{
    Q_OBJECT

public:
    ChangePasswordDialog(QWidget *parent = 0);
    QLineEdit *recoveryCodeText;
    QLineEdit *newPasswordText;

private:
    QLabel *recoveryCodeLabel;
    QLabel *newPasswordLabel;
    QPushButton *changeButton;
    QPushButton *cancelButton;
};

#endif // CHANGEPASSWORDDIALOG_H
