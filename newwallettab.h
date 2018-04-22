#ifndef NEWWALLETTAB_H
#define NEWWALLETTAB_H

#include <QWidget>

class QLabel;
class QPushButton;
class QVBoxLayout;

class NewWalletTab : public QWidget
{
    Q_OBJECT

public:
    NewWalletTab(QWidget *parent = 0);

public slots:
    void addEntry();

signals:
    void sendDetails(QString name, QString cryptocurrencyName, QString address, QString publicKey, QString privateKey, QString passPhrase, QString wordCode);

private:
    QLabel *descriptionLabel;
    QPushButton *addButton;
    QVBoxLayout *mainLayout;

};

#endif
