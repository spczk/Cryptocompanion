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
    walletWidget = new WalletWidget;
    setCentralWidget(walletWidget);
    createMenus();
    setWindowTitle("Cryptocompanion");
}

Cryptocompanion::~Cryptocompanion()
{
    delete ui;
}

void Cryptocompanion::createMenus()
{
    //Creating the dropdown menus and connecting them with their actions
    fileMenu = menuBar()->addMenu(tr("&File"));

    openAct = new QAction(tr("&Open..."), this);
    fileMenu->addAction(openAct);
    connect(openAct, &QAction::triggered, this, &Cryptocompanion::openFile);

    saveAct = new QAction(tr("&Save As..."), this);
    fileMenu->addAction(saveAct);
    connect(saveAct, &QAction::triggered, this, &Cryptocompanion::saveFile);

    changeAct = new QAction(tr("&Change Password..."), this);
    fileMenu->addAction(changeAct);
    connect(changeAct, &QAction::triggered, this, &Cryptocompanion::changePass);

    fileMenu->addSeparator(); //Adds a solid line to separate text

    exitAct = new QAction(tr("E&xit"), this);
    fileMenu->addAction(exitAct);
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    toolMenu = menuBar()->addMenu(tr("&Tools"));

    addAct = new QAction(tr("&Add Entry..."), this);
    toolMenu->addAction(addAct);
    connect(addAct, &QAction::triggered, walletWidget, &WalletWidget::showAddEntryDialog);

    editAct = new QAction(tr("&Edit Entry..."), this);
    editAct->setEnabled(false);
    toolMenu->addAction(editAct);
    connect(editAct, &QAction::triggered, walletWidget, &WalletWidget::editEntry);

    toolMenu->addSeparator();

    removeAct = new QAction(tr("&Remove Entry"), this);
    removeAct->setEnabled(false);
    toolMenu->addAction(removeAct);
    connect(removeAct, &QAction::triggered, walletWidget, &WalletWidget::removeEntry);

    connect(walletWidget, &WalletWidget::selectionChanged, this, &Cryptocompanion::updateActions);
}

void Cryptocompanion::openFile()
{
    walletWidget->login();
}

void Cryptocompanion::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (!fileName.isEmpty())
        walletWidget->writeToFile(fileName);
}

void Cryptocompanion::updateActions(const QItemSelection &selection)
{
    QModelIndexList indexes = selection.indexes();

    //Setting up Remove and Edit Entry clickable or not
    //depending on model data - if it exists then they are clickable

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
    walletWidget->login();
}

void Cryptocompanion::changePass()
{
  walletWidget->changePassword();
}
