#include "adddialog.h"
#include "logindialog.h"
#include "walletwidget.h"
#include "changepassworddialog.h"

#include <QtWidgets>
#include <QProcess>

WalletWidget::WalletWidget(QWidget *parent)
    : QTabWidget(parent)
{
    table = new TableModel(this);
    newAddressTab = new NewAddressTab(this);
    connect(newAddressTab, &NewAddressTab::sendDetails,
        this, &WalletWidget::addEntry);

    User user;
    connect(this, &WalletWidget::sendUserFileDetails, this, &WalletWidget::getUserFileDetails);

    addTab(newAddressTab, "Wallet information");
    setupTabs();
}

void WalletWidget::showAddEntryDialog()
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

void WalletWidget::addEntry(QString name, QString address, QString publicKey, QString privateKey, QString passPhrase, QString wordCode, QString cryptocurrencyName)
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

void WalletWidget::editEntry()
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
    aDialog.setWindowTitle(tr("Edit Wallet information"));

    aDialog.nameText->setReadOnly(true);
    aDialog.nameText->setText(name);
    aDialog.addressText->setText(address);
    aDialog.publicKeyText->setText(publicKey);
    aDialog.privateKeyText->setText(privateKey);
    aDialog.passPhraseText->setText(passPhrase);
    aDialog.wordCodeText->setText(wordCode);
    aDialog.cryptocurrencyNameText->setText(cryptocurrencyName);

    if (aDialog.exec()) {
        QString newAddress = aDialog.addressText->text();
        if (newAddress != address) {
            QModelIndex index = table->index(row, 1, QModelIndex());
            table->setData(index, newAddress, Qt::EditRole);
        }
        QString newPublicKey = aDialog.publicKeyText->text();
        if (newPublicKey != publicKey) {
          QModelIndex  index = table->index(row, 2, QModelIndex());
            table->setData(index, newPublicKey, Qt::EditRole);
        }
        QString newPrivateKey = aDialog.privateKeyText->text();
        if (newPrivateKey != privateKey) {
           QModelIndex index = table->index(row, 3, QModelIndex());
            table->setData(index, newPrivateKey, Qt::EditRole);
        }
        QString newPassPhrase = aDialog.passPhraseText->text();
        if (newPassPhrase != passPhrase) {
           QModelIndex index = table->index(row, 4, QModelIndex());
            table->setData(index, newPassPhrase, Qt::EditRole);
        }
        QString newWordCode = aDialog.wordCodeText->text();
        if (newWordCode != wordCode) {
           QModelIndex index = table->index(row, 5, QModelIndex());
            table->setData(index, newWordCode, Qt::EditRole);
        }
        QString newCryptocurrencyName = aDialog.cryptocurrencyNameText->text();
        if (newCryptocurrencyName != cryptocurrencyName) {
          QModelIndex  index = table->index(row, 6, QModelIndex());
            table->setData(index, newCryptocurrencyName, Qt::EditRole);
        }
    }
}

void WalletWidget::removeEntry()
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
        insertTab(0, newAddressTab, "Wallet information");
    }
}

void WalletWidget::setupTabs()
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
            this, &WalletWidget::selectionChanged);

        connect(this, &QTabWidget::currentChanged, this, [this](int tabIndex) {
            auto *tableView = qobject_cast<QTableView *>(widget(tabIndex));
            if (tableView)
                emit selectionChanged(tableView->selectionModel()->selection());
        });

        addTab(tableView, str);
    }
}

void WalletWidget::readFromFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    }

    QList<Wallet> wallets;

    quint64 key;
    QString encryptedFirstName;
    QString encryptedLastName;
    QString encryptedPassword;
    QString encryptedRecoveryCode;

    QDataStream in(&file);
    in >> key >> encryptedFirstName >> encryptedLastName >> encryptedPassword >> encryptedRecoveryCode >> wallets;

    if (wallets.isEmpty()) {
        QMessageBox::information(this, tr("No wallet information in file"),
                                 tr("The file you are attempting to open contains no wallet information."));
    } else {
        for (const auto &wallet: qAsConst(wallets))
            addEntry(wallet.name, wallet.address, wallet.publicKey, wallet.privateKey, wallet.passPhrase, wallet.wordCode, wallet.cryptocurrencyName);
    }
}

void WalletWidget::writeToFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }

    QDataStream out(&file);
    out << user.getKey() << user.getFirstName() << user.getLastName() << user.getPassword() << user.getRecoveryCode() << table->getWallets();
}

void WalletWidget::login()
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
    QString encryptedRecoveryCode;
    QString firstName;
    QString lastName;
    QString password;
    quint64 key;
    QDataStream in(&file);
    QList<Wallet> wallets;

    in >> key >> encryptedFirstName >> encryptedLastName >> encryptedPassword >> encryptedRecoveryCode >> wallets;

    if (wallets.isEmpty()) {
        QMessageBox::information(this, tr("No wallet information in file"),
                                 tr("The file you are attempting to open contains no wallet information."));
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
        else
            {
                QMessageBox::warning(this, "Login failed", "Wrong Name/Password. Try Again.");
                QMetaObject::invokeMethod(qApp, "quit",
                    Qt::QueuedConnection);
                QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
            }
        }

    emit sendUserFileDetails(key, encryptedFirstName, encryptedLastName, encryptedPassword, encryptedRecoveryCode);
}


void WalletWidget::getUserFileDetails(quint64 key ,QString encFirstName, QString encLastName, QString encPassword, QString encRecoveryCode)
{
   user.setKey(key);
   user.setFirstName(encFirstName);
   user.setLastName(encLastName);
   user.setPassword(encPassword);
   user.setRecoveryCode(encRecoveryCode);

}

void WalletWidget::changePassword()
{
    ChangePasswordDialog changeDialog;
    SimpleCrypt simple(user.getKey());

    if (changeDialog.exec()) {
        QString recoveryCode = changeDialog.recoveryCodeText->text();
        QString newPassword = changeDialog.newPasswordText->text();

        if (recoveryCode == simple.decryptToString(user.getRecoveryCode()))
        {
            QString encryptedNewPassword = simple.encryptToString(newPassword);
            user.setPassword(encryptedNewPassword);
            QMessageBox::information(this, "Change password", "Password changed succesfully");




            QString fileName = QFileDialog::getSaveFileName(this);
            QFile file(fileName);

            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::information(this, tr("Unable to open file"), file.errorString());
                return;
            }

            QDataStream out(&file);
            out << user.getKey() << user.getFirstName() << user.getLastName() << user.getPassword() << user.getRecoveryCode() << table->getWallets();

        }
    } else QMessageBox::warning(this, "Change password", "Wrong recovery code, password hasn't changed");
}
