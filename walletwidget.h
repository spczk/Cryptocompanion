#ifndef WALLETWIDGET_H
#define WALLETWIDGET_H

#include "newwallettab.h"
#include "tablemodel.h"
#include "simplecrypt.h"

#include <QItemSelection>
#include <QTabWidget>

class QSortFilterProxyModel;
class QItemSelectionModel;

class WalletWidget : public QTabWidget
{
    Q_OBJECT

public:
    WalletWidget(QWidget *parent = 0);
    void readFromFile(const QString &fileName);
    void writeToFile(const QString &fileName);
    void changePassword();
    void login();

public slots:
    void showAddEntryDialog();
    void addEntry(QString name, QString cryptocurrencyName, QString address, QString publicKey, QString privateKey, QString passPhrase, QString wordCode);
    void editEntry();
    void removeEntry();
    void getUserFileDetails(quint64 key ,QString encFirstName, QString encLastName, QString encPassword, QString encRecoveryCode);

signals:
    void selectionChanged (const QItemSelection &selected);
    void sendUserFileDetails(quint64 key ,QString encFirstName, QString encLastName, QString encPassword, QString encRecoveryCode);

private:
    void setupTabs();

    SimpleCrypt simple;
    User user;
    TableModel *table;
    NewWalletTab *newWalletTab;
    QSortFilterProxyModel *proxyModel;
    QSortFilterProxyModel *allModel;
};

#endif // WALLETWIDGET_H
