#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    AddDialog(QWidget *parent = 0);
    QLineEdit *nameText;
    QLineEdit *addressText;
    QLineEdit *publicKeyText;
    QLineEdit *passPhraseText;
    QLineEdit *privateKeyText;
    QLineEdit *wordCodeText;
    QLineEdit *cryptocurrencyNameText;

private:
    QLabel *nameLabel;
    QLabel *addressLabel;
    QLabel *publicKeyLabel;
    QLabel *privateKeyLabel;
    QLabel *passPhraseLabel;
    QLabel *wordCodeLabel;
    QLabel *cryptocurrencyNameLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // ADDDIALOG_H
