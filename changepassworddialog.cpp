#include "changepassworddialog.h"

#include <QtWidgets>

ChangePasswordDialog::ChangePasswordDialog(QWidget *parent)
    : QDialog(parent)
{
  //Setting up the UI of the dialog
    recoveryCodeLabel = new QLabel("Recovery Code");
    newPasswordLabel = new QLabel("New Password");
    changeButton = new QPushButton("Change");
    cancelButton = new QPushButton("Cancel");

    recoveryCodeText = new QLineEdit;
    newPasswordText = new QLineEdit;

    QGridLayout *gLayout = new QGridLayout;
    gLayout->setColumnStretch(1, 2);
    gLayout->addWidget(recoveryCodeLabel, 0, 0);
    gLayout->addWidget(recoveryCodeText, 0, 1);

    gLayout->addWidget(newPasswordLabel, 1, 0, Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(newPasswordText, 1, 1, Qt::AlignLeft);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(changeButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 2, 1, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    /*
     * Connecting buttons with actions
     * ok - sets the dialog code to accepted
     * cancel - sets the dialog code to rejected
     */

    connect(changeButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle(tr("Change Password"));
}
