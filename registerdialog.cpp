#include "registerdialog.h"

#include <QtWidgets>

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
{
    firstNameLabel = new QLabel("First Name");
    lastNameLabel = new QLabel("Last Name");
    passwordLabel = new QLabel("Password");
    registerButton = new QPushButton("Register");
    cancelButton = new QPushButton("Cancel");

    firstNameText = new QLineEdit;
    lastNameText = new QLineEdit;
    passwordText = new QLineEdit;

    QGridLayout *gLayout = new QGridLayout;
    gLayout->setColumnStretch(1, 3);
    gLayout->addWidget(firstNameLabel, 0, 0);
    gLayout->addWidget(firstNameText, 0, 1);

    gLayout->addWidget(lastNameLabel, 1, 0);
    gLayout->addWidget(lastNameText, 1, 1);

    gLayout->addWidget(passwordLabel, 2, 0, Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(passwordText, 2, 1, Qt::AlignLeft);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(registerButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    /*
     * Connecting buttons with actions
     * register - sets the dialog code to accepted
     * cancel - sets the dialog code to rejected
     */

    connect(registerButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle(tr("Register"));
}
