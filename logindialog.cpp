#include "logindialog.h"

#include <QtWidgets>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
{
    nameLabel = new QLabel("Name");
    passwordLabel = new QLabel("Password");
    loginButton = new QPushButton("Login");
    cancelButton = new QPushButton("Cancel");

    nameText = new QLineEdit;
    passwordText = new QLineEdit;

    QGridLayout *gLayout = new QGridLayout;
    gLayout->setColumnStretch(1, 2);
    gLayout->addWidget(nameLabel, 0, 0);
    gLayout->addWidget(nameText, 0, 1);

    gLayout->addWidget(passwordLabel, 1, 0, Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(passwordText, 1, 1, Qt::AlignLeft);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 2, 1, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(loginButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle(tr("Login"));
}
