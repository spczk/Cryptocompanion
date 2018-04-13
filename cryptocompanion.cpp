#include "cryptocompanion.h"
#include "ui_cryptocompanion.h"
#include "registerdialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QPixmap>
#include <QAction>
#include <QFileDialog>
#include <QMenuBar>


Cryptocompanion::Cryptocompanion(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Cryptocompanion)
{
    ui->setupUi(this);
    addressWidget = new AddressWidget;
    setCentralWidget(addressWidget);
    createMenus();
    setWindowTitle("Cryptocompanion");
}

Cryptocompanion::~Cryptocompanion()
{
    delete ui;
}

void Cryptocompanion::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));

    openAct = new QAction(tr("&Open..."), this);
    fileMenu->addAction(openAct);
    connect(openAct, &QAction::triggered, this, &Cryptocompanion::openFile);

    saveAct = new QAction(tr("&Save As..."), this);
    fileMenu->addAction(saveAct);
    connect(saveAct, &QAction::triggered, this, &Cryptocompanion::saveFile);

    fileMenu->addSeparator();

    exitAct = new QAction(tr("E&xit"), this);
    fileMenu->addAction(exitAct);
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    toolMenu = menuBar()->addMenu(tr("&Tools"));

    addAct = new QAction(tr("&Add Entry..."), this);
    toolMenu->addAction(addAct);
    connect(addAct, &QAction::triggered, addressWidget, &AddressWidget::showAddEntryDialog);

    editAct = new QAction(tr("&Edit Entry..."), this);
    editAct->setEnabled(false);
    toolMenu->addAction(editAct);
    connect(editAct, &QAction::triggered, addressWidget, &AddressWidget::editEntry);

    toolMenu->addSeparator();

    removeAct = new QAction(tr("&Remove Entry"), this);
    removeAct->setEnabled(false);
    toolMenu->addAction(removeAct);
    connect(removeAct, &QAction::triggered, addressWidget, &AddressWidget::removeEntry);

    connect(addressWidget, &AddressWidget::selectionChanged,
        this, &Cryptocompanion::updateActions);
}

void Cryptocompanion::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        addressWidget->readFromFile(fileName);
}

void Cryptocompanion::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (!fileName.isEmpty())
        addressWidget->writeToFile(fileName);
}

void Cryptocompanion::updateActions(const QItemSelection &selection)
{
    QModelIndexList indexes = selection.indexes();

    if (!indexes.isEmpty()) {
        removeAct->setEnabled(true);
        editAct->setEnabled(true);
    } else {
        removeAct->setEnabled(false);
        editAct->setEnabled(false);
    }
}

void Cryptocompanion::login()
{
    addressWidget->login();
}

/*
void Cryptocompanion::loadTextFile()
  {
      QFile inputFile(":/input.txt");
      inputFile.open(QIODevice::ReadOnly);

      QTextStream in(&inputFile);
      QString line = in.readAll();
      inputFile.close();

      ui->textEdit->setPlainText(line);
      QTextCursor cursor = ui->textEdit->textCursor();
      cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);
  }

void Cryptocompanion::on_loginButton_clicked()
{
    QString Name = ui->Name_lineEdit->text();
    QString password = ui->login_password_lineEdit->text();

    if(Name ==  "Jan Kowalski" && password == "test") {
        QMessageBox::information(this, "Login", "Succesful Login!");
        hide();
        secDialog = new SecDialog(this);
        secDialog->show();
    }
    else {
        QMessageBox::warning(this,"Login", "Name and password is not correct");
    }
}

void Cryptocompanion::on_registerButton_clicked()
{


    QMessageBox::information(this, "Register", "Succesful Register!");
    hide();
    secDialog = new SecDialog(this);
    secDialog->show();
    User user;
    user.setFirstName(ui->firstName_lineEdit->text());
    user.setLastName(ui->lastName_lineEdit->text());
    user.setPassword(ui->register_password_lineEdit->text());
}
*/
