#include "adddialog.h"

#include <QtWidgets>

AddDialog::AddDialog(QWidget *parent)
    : QDialog(parent)
{
    //Creating our UI objects

    nameLabel = new QLabel("Name");
    addressLabel = new QLabel("Address");
    publicKeyLabel = new QLabel("Public Key");
    privateKeyLabel = new QLabel("Private Key");
    passPhraseLabel = new QLabel("Pass Phrase");
    wordCodeLabel = new QLabel("Word Code");
    cryptocurrencyNameLabel = new QLabel("Cryptocurrency name");

    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    nameText = new QLineEdit;
    addressText = new QLineEdit;
    publicKeyText = new QLineEdit;
    privateKeyText = new QLineEdit;
    passPhraseText = new QLineEdit;
    wordCodeText = new QLineEdit;
    cryptocurrencyNameText = new QLineEdit;

    QGridLayout *gLayout = new QGridLayout;

    //Placing our UI objects on our grid layout

    gLayout->setColumnStretch(1, 7);
    gLayout->addWidget(nameLabel, 0, 0);
    gLayout->addWidget(nameText, 0, 1, Qt::AlignLeft);

    gLayout->addWidget(cryptocurrencyNameLabel, 1, 0, Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(cryptocurrencyNameText, 1, 1, Qt::AlignLeft);

    gLayout->addWidget(addressLabel, 2, 0, Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(addressText, 2, 1, Qt::AlignLeft);

    gLayout->addWidget(publicKeyLabel, 3, 0, Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(publicKeyText, 3, 1, Qt::AlignLeft);

    gLayout->addWidget(privateKeyLabel, 4, 0, Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(privateKeyText, 4, 1, Qt::AlignLeft);

    gLayout->addWidget(passPhraseLabel, 5, 0, Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(passPhraseText, 5, 1, Qt::AlignLeft);

    gLayout->addWidget(wordCodeLabel, 6, 0, Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(wordCodeText, 6, 1, Qt::AlignLeft);



    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 7, 1, Qt::AlignRight);

    //Creating main layout to put our previously created grid layout in a window box

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    /*
     * Connecting buttons with actions
     * ok - sets the dialog code to accepted
     * cancel - sets the dialog code to rejected
     */

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle(tr("Add a Wallet"));
}
