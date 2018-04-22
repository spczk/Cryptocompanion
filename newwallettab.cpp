#include "adddialog.h"
#include "newwallettab.h"

#include <QtWidgets>

NewWalletTab::NewWalletTab(QWidget *parent)
{
    Q_UNUSED(parent);

    //String to display on our newWalletTab
    descriptionLabel = new QLabel(tr("There aren't currently any wallet information in your account. "
                                      "\nClick Add to add wallet information."));

    //Setting up the UI
    addButton = new QPushButton(tr("Add"));

    connect(addButton, &QAbstractButton::clicked, this, &NewWalletTab::addEntry);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(descriptionLabel);
    mainLayout->addWidget(addButton, 0, Qt::AlignCenter);

    setLayout(mainLayout);
}

void NewWalletTab::addEntry()
{
    //Opening add dialog, getting data out of text fields and sending a signal with it
    AddDialog aDialog;

    if (aDialog.exec()) {
        QString name = aDialog.nameText->text();
        QString cryptocurrencyName = aDialog.cryptocurrencyNameText->text();
        QString address = aDialog.addressText->text();
        QString publicKey = aDialog.publicKeyText->text();
        QString passPhrase = aDialog.passPhraseText->text();
        QString privateKey = aDialog.privateKeyText->text();
        QString wordCode = aDialog.wordCodeText->text();
        emit sendDetails(name, cryptocurrencyName, address, publicKey, privateKey, passPhrase, wordCode);
    }
}
