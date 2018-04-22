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
    newWalletTab = new NewWalletTab(this);
    connect(newWalletTab, &NewWalletTab::sendDetails, this, &WalletWidget::addEntry);

    User user;
    connect(this, &WalletWidget::sendUserFileDetails, this, &WalletWidget::getUserFileDetails);

    addTab(newWalletTab, "Wallet information");
    setupTabs();
}

void WalletWidget::showAddEntryDialog() //Shows dialog with blank fields for adding new information
                                        //then adds it to the program
{
    AddDialog aDialog;

    if (aDialog.exec()) {
        QString name = aDialog.nameText->text();
        QString cryptocurrencyName=  aDialog.cryptocurrencyNameText->text();
        QString address = aDialog.addressText->text();
        QString publicKey = aDialog.publicKeyText->text();
        QString passPhrase = aDialog.passPhraseText->text();
        QString privateKey = aDialog.privateKeyText->text();
        QString wordCode = aDialog.wordCodeText->text();

        addEntry(name, cryptocurrencyName, address, publicKey, privateKey, passPhrase, wordCode);
    }
}

void WalletWidget::addEntry(QString name, QString cryptocurrencyName, QString address, QString publicKey, QString privateKey, QString passPhrase, QString wordCode)
{
    //Adding our entried data to table model on appropriate index and column
    if (!table->getWallets().contains({ name, address, publicKey, privateKey, passPhrase, wordCode, cryptocurrencyName})) {
        table->insertRows(0, 1, QModelIndex());

        QModelIndex index = table->index(0, 0, QModelIndex());
        table->setData(index, name, Qt::EditRole);

        index = table->index(0, 1, QModelIndex());
        table->setData(index, cryptocurrencyName, Qt::EditRole);

        index = table->index(0, 2, QModelIndex());
        table->setData(index, address, Qt::EditRole);

        index = table->index(0, 3, QModelIndex());
        table->setData(index, publicKey, Qt::EditRole);

        index = table->index(0, 4, QModelIndex());
        table->setData(index, privateKey, Qt::EditRole);

        index = table->index(0, 5, QModelIndex());
        table->setData(index, passPhrase, Qt::EditRole);

        index = table->index(0, 6, QModelIndex());
        table->setData(index, wordCode, Qt::EditRole);


        removeTab(indexOf(newWalletTab));
    }
    //This fragment blocks adding wallet with the same name, but it's not necessary
    /*else {
        QMessageBox::information(this, tr("Duplicate Name"),
            tr("The name \"%1\" already exists.").arg(name));
    }*/
}

void WalletWidget::editEntry()
{
    //Getting pointers to currently selected data
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();

    //Creating variables to get data from model
    QString name;
    QString cryptocurrencyName;
    QString address;
    QString publicKey;
    QString passPhrase;
    QString privateKey;
    QString wordCode;
    int row = 1;

    //Getting data from table model

    foreach (QModelIndex index, indexes) {
        row = proxy->mapToSource(index).row();
        QModelIndex nameIndex = table->index(row, 0, QModelIndex());
        QVariant varName = table->data(nameIndex, Qt::DisplayRole);
        name = varName.toString();

        QModelIndex cryptoCurrencyNameIndex = table->index(row, 1, QModelIndex());
        QVariant varCurrName = table->data(cryptoCurrencyNameIndex, Qt::DisplayRole);
        cryptocurrencyName = varCurrName.toString();

        QModelIndex addressIndex = table->index(row, 2, QModelIndex());
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
    }

    //Displaying add dialog with data currently stored in selected row

    AddDialog aDialog;
    aDialog.setWindowTitle(tr("Edit Wallet information"));

    aDialog.nameText->setText(name);
    aDialog.addressText->setText(address);
    aDialog.publicKeyText->setText(publicKey);
    aDialog.privateKeyText->setText(privateKey);
    aDialog.passPhraseText->setText(passPhrase);
    aDialog.wordCodeText->setText(wordCode);
    aDialog.cryptocurrencyNameText->setText(cryptocurrencyName);

    //If some of the data differs from before - change it
    //If not - leave it as it is

    if (aDialog.exec()) {

        QString newName = aDialog.nameText->text();
        if (newName != name) {
          QModelIndex  index = table->index(row, 0, QModelIndex());
            table->setData(index, newName, Qt::EditRole);
        }

        QString newCryptocurrencyName = aDialog.cryptocurrencyNameText->text();
        if (newCryptocurrencyName != cryptocurrencyName) {
          QModelIndex  index = table->index(row, 1, QModelIndex());
            table->setData(index, newCryptocurrencyName, Qt::EditRole);
        }

        QString newAddress = aDialog.addressText->text();
        if (newAddress != address) {
            QModelIndex index = table->index(row, 2, QModelIndex());
            table->setData(index, newAddress, Qt::EditRole);
        }
        QString newPublicKey = aDialog.publicKeyText->text();
        if (newPublicKey != publicKey) {
          QModelIndex  index = table->index(row, 3, QModelIndex());
            table->setData(index, newPublicKey, Qt::EditRole);
        }
        QString newPrivateKey = aDialog.privateKeyText->text();
        if (newPrivateKey != privateKey) {
           QModelIndex index = table->index(row, 4, QModelIndex());
            table->setData(index, newPrivateKey, Qt::EditRole);
        }
        QString newPassPhrase = aDialog.passPhraseText->text();
        if (newPassPhrase != passPhrase) {
           QModelIndex index = table->index(row, 5, QModelIndex());
            table->setData(index, newPassPhrase, Qt::EditRole);
        }
        QString newWordCode = aDialog.wordCodeText->text();
        if (newWordCode != wordCode) {
           QModelIndex index = table->index(row, 6, QModelIndex());
            table->setData(index, newWordCode, Qt::EditRole);
        }
    }
}

void WalletWidget::removeEntry()
{
    //Getting pointers to our currently highlited data

    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();

    //Deleting row with selected data
    //If there is no wallet information after deleting - display a newWalletTab

    foreach (QModelIndex index, indexes) {
        int row = proxy->mapToSource(index).row();
        table->removeRows(row, 1, QModelIndex());
    }

    if (table->rowCount(QModelIndex()) == 0) {
        insertTab(0, newWalletTab, "Wallet information");
    }
}

void WalletWidget::setupTabs()
{
    //Creating a table view to display all our wallets

    QTableView *allView = new QTableView;

    //Creating and seting our sortfilter model (without it we can't sort our data)

    allModel = new QSortFilterProxyModel(this);
    allModel->setSourceModel(table);

    allView->setModel(allModel);

    //Table behaviour configuration

    allView->setSelectionBehavior(QAbstractItemView::SelectRows);
    allView->horizontalHeader()->setStretchLastSection(true);
    allView->verticalHeader()->hide();
    allView->setEditTriggers(QAbstractItemView::DoubleClicked);
    allView->setSelectionMode(QAbstractItemView::SingleSelection);

    allView->setSortingEnabled(true);

    addTab(allView, "All");

    //Creating list of filtering groups
    QStringList groups;
    groups << "ABC" << "DEF" << "GHI" << "JKL" << "MNO" << "PQR" << "STU" << "VW" << "XYZ";

    //Passing these groups to regexp one by one
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
        tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
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
    //File handling

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());

        return;
    }

    //Creating variables for reading data from file

    QList<Wallet> wallets;

    quint64 key;
    QString encryptedFirstName;
    QString encryptedLastName;
    QString encryptedPassword;
    QString encryptedRecoveryCode;

    //File reading

    QDataStream in(&file);
    in >> key >> encryptedFirstName >> encryptedLastName >> encryptedPassword >> encryptedRecoveryCode >> wallets;

    /*
     * If file doesn't contain any wallet information - warning window
     * if it does - program gets the data
     */

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

        //App restart
        QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
        return;
    }

    QDataStream out(&file);
    out << user.getKey() << user.getFirstName() << user.getLastName() << user.getPassword() << user.getRecoveryCode() << table->getWallets();
}

void WalletWidget::login()
{
    hide();

    //Opening a file

    QString fileName = QFileDialog::getOpenFileName(this);

    QFile file(fileName);

    //On failed open

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());

        //App restart
        QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
        return;
    }

    //Creating variables and reading data to them

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

    /*If there is no wallet information then app sends an pop up with this information
     * else it reads wallet data from file
     */

    if (wallets.isEmpty()) {
        QMessageBox::information(this, tr("No wallet information in file"),
                                 tr("The file you are attempting to open contains no wallet information."));
    } else {
        for (const auto &wallet: qAsConst(wallets))
            addEntry(wallet.name, wallet.address, wallet.publicKey, wallet.privateKey, wallet.passPhrase, wallet.wordCode, wallet.cryptocurrencyName);
    }

    //Setting a key that it's got from a file to get correct data from decryption

    SimpleCrypt simple(key);

    firstName = simple.decryptToString(encryptedFirstName);
    lastName = simple.decryptToString(encryptedLastName);
    password = simple.decryptToString(encryptedPassword);

    //Getting first name and last name together to form full name

    QString name = firstName + " " + lastName;

    /*Creating a login dialog
     * If user information is correct - app shows up the main window
     * If it isn't - app restarts
     */

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

                //App Restart
                QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
                QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
            }
        }

    //Sending a signal with user information for later use
    emit sendUserFileDetails(key, encryptedFirstName, encryptedLastName, encryptedPassword, encryptedRecoveryCode);
}


void WalletWidget::getUserFileDetails(quint64 key ,QString encFirstName, QString encLastName, QString encPassword, QString encRecoveryCode)
{
   //Setting the user information from login signal for later use
   user.setKey(key);
   user.setFirstName(encFirstName);
   user.setLastName(encLastName);
   user.setPassword(encPassword);
   user.setRecoveryCode(encRecoveryCode);

}

void WalletWidget::changePassword()
{
    ChangePasswordDialog changeDialog;
    //Getting user key to decrypt his data
    SimpleCrypt simple(user.getKey());

    /*
     * If recovery code is correct - password can be changed
     * if not - warning window
     */
    if (changeDialog.exec()) {
        QString recoveryCode = changeDialog.recoveryCodeText->text();
        QString newPassword = changeDialog.newPasswordText->text();

        if (recoveryCode == simple.decryptToString(user.getRecoveryCode()))
        {
            QString encryptedNewPassword = simple.encryptToString(newPassword);
            user.setPassword(encryptedNewPassword);
            QMessageBox::information(this, "Change password", "Password changed succesfully");


            //User specifies a file for saving his data with new password

            QString fileName = QFileDialog::getSaveFileName(this);
            QFile file(fileName);

            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::information(this, tr("Unable to open file"), file.errorString());
                return;
            }

            //Writing data to file

            QDataStream out(&file);
            out << user.getKey() << user.getFirstName() << user.getLastName() << user.getPassword() << user.getRecoveryCode() << table->getWallets();

        }
    } else QMessageBox::warning(this, "Change password", "Wrong recovery code, password hasn't changed");
}
