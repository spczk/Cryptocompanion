#ifndef ADDRESSWIDGET_H
#define ADDRESSWIDGET_H

#include "newaddresstab.h"
#include "tablemodel.h"
#include "simplecrypt.h"

#include <QItemSelection>
#include <QTabWidget>

class QSortFilterProxyModel;
class QItemSelectionModel;

class AddressWidget : public QTabWidget
{
    Q_OBJECT

public:
    AddressWidget(QWidget *parent = 0);
    void readFromFile(const QString &fileName);
    void writeToFile(const QString &fileName);

public slots:
    void showAddEntryDialog();
    void addEntry(QString name, QString address);
    void editEntry();
    void removeEntry();
    void login();
    void getUserFileDetails(quint64 key ,QString encfirstName, QString enclastName, QString encpassword);

signals:
    void selectionChanged (const QItemSelection &selected);
    void sendUserFileDetails(quint64 key ,QString encfirstName, QString enclastName, QString encpassword);

private:
    void setupTabs();

    SimpleCrypt simple;
    User user;
    TableModel *table;
    NewAddressTab *newAddressTab;
    QSortFilterProxyModel *proxyModel;
};

#endif // ADDRESSWIDGET_H
