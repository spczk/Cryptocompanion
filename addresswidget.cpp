#include "adddialog.h"
#include "logindialog.h"
#include "addresswidget.h"

#include <QtWidgets>

AddressWidget::AddressWidget(QWidget *parent)
    : QTabWidget(parent)
{
   //this->login();
    table = new TableModel(this);
    newAddressTab = new NewAddressTab(this);
    connect(newAddressTab, &NewAddressTab::sendDetails,
        this, &AddressWidget::addEntry);

    User user;
    connect(this, &AddressWidget::sendUserFileDetails, this, &AddressWidget::getUserFileDetails);

    addTab(newAddressTab, "Address Book");
    setupTabs();
}

void AddressWidget::showAddEntryDialog()
{
    AddDialog aDialog;

    if (aDialog.exec()) {
        QString name = aDialog.nameText->text();
        QString address = aDialog.addressText->text();
        QString publicKey = aDialog.publicKeyText->text();
        QString passPhrase = aDialog.passPhraseText->text();
        QString privateKey = aDialog.privateKeyText->text();
        QString wordCode = aDialog.wordCodeText->text();
        QString cryptocurrencyName=  aDialog.cryptocurrencyNameText->text();

        addEntry(name, address, publicKey, privateKey, passPhrase, wordCode, cryptocurrencyName);
    }
}

void AddressWidget::addEntry(QString name, QString address, QString publicKey, QString privateKey, QString passPhrase, QString wordCode, QString cryptocurrencyName)
{
    if (!table->getWallets().contains({ name, address, publicKey, privateKey, passPhrase, wordCode, cryptocurrencyName})) {
        table->insertRows(0, 1, QModelIndex());

        QModelIndex index = table->index(0, 0, QModelIndex());
        table->setData(index, name, Qt::EditRole);
        index = table->index(0, 1, QModelIndex());
        table->setData(index, address, Qt::EditRole);

        index = table->index(0, 2, QModelIndex());
        table->setData(index, publicKey, Qt::EditRole);

        index = table->index(0, 3, QModelIndex());
        table->setData(index, privateKey, Qt::EditRole);

        index = table->index(0, 4, QModelIndex());
        table->setData(index, passPhrase, Qt::EditRole);

        index = table->index(0, 5, QModelIndex());
        table->setData(index, wordCode, Qt::EditRole);

        index = table->index(0, 6, QModelIndex());
        table->setData(index, cryptocurrencyName, Qt::EditRole);


        removeTab(indexOf(newAddressTab));
    } else {
        QMessageBox::information(this, tr("Duplicate Name"),
            tr("The name \"%1\" already exists.").arg(name));
    }
}

void AddressWidget::editEntry()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();
    QString name;
    QString address;
    QString publicKey;
    QString passPhrase;
    QString privateKey;
    QString wordCode;
    QString cryptocurrencyName;
    int row = -1;

    foreach (QModelIndex index, indexes) {
        row = proxy->mapToSource(index).row();
        QModelIndex nameIndex = table->index(row, 0, QModelIndex());
        QVariant varName = table->data(nameIndex, Qt::DisplayRole);
        name = varName.toString();

        QModelIndex addressIndex = table->index(row, 1, QModelIndex());
        QVariant varAddr = table->data(addressIndex, Qt::DisplayRole);
        address = varAddr.toString();

        QModelIndex publicKeyIndex = table->index(row, 3, QModelIndex());
        QVariant varPubKey = table->data(publicKeyIndex, Qt::DisplayRole);
        publicKey = varPubKey.toString();

        QModelIndex privateKeyIndex = table->index(row, 4, QModelIndex());
        QVariant varPrivKey = table->data(privateKeyIndex, Qt::DisplayRole);
        privateKey = varPrivKey.toString();

        QModelIndex passPhraseIndex = table->index(row, 5, QModelIndex());
        QVariant varPassPhrase = table->data(passPhraseIndex, Qt::DisplayRole);
        passPhrase = varPassPhrase.toString();

        QModelIndex wordCodeIndex = table->index(row, 6, QModelIndex());
        QVariant varWordCode = table->data(wordCodeIndex, Qt::DisplayRole);
        wordCode = varWordCode.toString();

        QModelIndex cryptoCurrencyNameIndex = table->index(row, 7, QModelIndex());
        QVariant varCurrName = table->data(cryptoCurrencyNameIndex, Qt::DisplayRole);
        cryptocurrencyName = varCurrName.toString();
    }

    AddDialog aDialog;
    aDialog.setWindowTitle(tr("Edit a Contact"));

    aDialog.nameText->setReadOnly(true);
    aDialog.nameText->setText(name);
    aDialog.addressText->setText(address);

    if (aDialog.exec()) {
        QString newAddress = aDialog.addressText->text();
        if (newAddress != address) {
            QModelIndex index = table->index(row, 1, QModelIndex());
            table->setData(index, newAddress, Qt::EditRole);
        }
    }
}

void AddressWidget::removeEntry()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();

    foreach (QModelIndex index, indexes) {
        int row = proxy->mapToSource(index).row();
        table->removeRows(row, 1, QModelIndex());
    }

    if (table->rowCount(QModelIndex()) == 0) {
        insertTab(0, newAddressTab, "Address Book");
    }
}

void AddressWidget::setupTabs()
{
    QStringList groups;
    groups << "ABC" << "DEF" << "GHI" << "JKL" << "MNO" << "PQR" << "STU" << "VW" << "XYZ";

    for (int i = 0; i < groups.size(); ++i) {
        QString str = groups.at(i);
        QString regExp = QString("^[%1].*").arg(str);

        proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(table);
        proxyModel->setFilterRegExp(QRegExp(regExp, Qt::CaseInsensitive));
        proxyModel->setFilterKeyColumn(0);

        QTableView *tableView = new QTableView;
        tableView->setModel(proxyModel);

        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->hide();
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);

        tableView->setSortingEnabled(true);

        connect(tableView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this, &AddressWidget::selectionChanged);

        connect(this, &QTabWidget::currentChanged, this, [this](int tabIndex) {
            auto *tableView = qobject_cast<QTableView *>(widget(tabIndex));
            if (tableView)
                emit selectionChanged(tableView->selectionModel()->selection());
        });

        addTab(tableView, str);
    }
}

void AddressWidget::readFromFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    }

    QList<Wallet> wallets;
    QDataStream in(&file);
    in >> wallets;

    if (wallets.isEmpty()) {
        QMessageBox::information(this, tr("No wallets in file"),
                                 tr("The file you are attempting to open contains no contacts."));
    } else {
        for (const auto &wallet: qAsConst(wallets))
            addEntry(wallet.name, wallet.address, wallet.publicKey, wallet.privateKey, wallet.passPhrase, wallet.wordCode, wallet.cryptocurrencyName);
    }
}

void AddressWidget::writeToFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }

    QDataStream out(&file);
    out << user.getKey() << user.getFirstName() << user.getLastName() << user.getPassword() << table->getWallets();
}

void AddressWidget::login()
{
    hide();
    QString fileName = QFileDialog::getOpenFileName(this);

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    }


    QString encryptedFirstName;
    QString encryptedLastName;
    QString encryptedPassword;
    QString firstName;
    QString lastName;
    QString password;
    quint64 key;
    QDataStream in(&file);
    QList<Wallet> wallets;

    in >> key >> encryptedFirstName >> encryptedLastName >> encryptedPassword >> wallets;

    if (wallets.isEmpty()) {
        QMessageBox::information(this, tr("No contacts in file"),
                                 tr("The file you are attempting to open contains no contacts."));
    } else {
        for (const auto &wallet: qAsConst(wallets))
            addEntry(wallet.name, wallet.address, wallet.publicKey, wallet.privateKey, wallet.passPhrase, wallet.wordCode, wallet.cryptocurrencyName);
    }

    SimpleCrypt simple(key);

    firstName = simple.decryptToString(encryptedFirstName);
    lastName = simple.decryptToString(encryptedLastName);
    password = simple.decryptToString(encryptedPassword);

    QString name = firstName + " " + lastName;

    LoginDialog login;
    if (login.exec())
        {
        QString nameInput = login.nameText->text();
        QString passwordInput = login.passwordText->text();
        if (nameInput == name && passwordInput == password)
            show();
        }

    qInfo() << firstName << lastName << password;
    emit sendUserFileDetails(key, encryptedFirstName, encryptedLastName, encryptedPassword);

}


void AddressWidget::getUserFileDetails(quint64 key ,QString encfirstName, QString enclastName, QString encpassword)
{
   user.setKey(key);
   user.setFirstName(encfirstName);
   user.setLastName(enclastName);
   user.setPassword(encpassword);

}
