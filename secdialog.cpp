#include "user.h"
#include "cryptocompanion.h"
#include <QAction>
#include <QFileDialog>
#include <QMenuBar>


SecDialog::SecDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);
    addressWidget = new AddressWidget;
    setCentralWidget(addressWidget);
    createMenus();
    setWindowTitle(tr("Address Book"));
}

SecDialog::~SecDialog()
{
    delete ui;
}



//SecDialog::SecDialog()
//{
//    addressWidget = new AddressWidget;
//    setCentralWidget(addressWidget);
//    createMenus();
//    setWindowTitle(tr("Address Book"));
//}

void SecDialog::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));

    openAct = new QAction(tr("&Open..."), this);
    fileMenu->addAction(openAct);
    connect(openAct, &QAction::triggered, this, &SecDialog::openFile);

    saveAct = new QAction(tr("&Save As..."), this);
    fileMenu->addAction(saveAct);
    connect(saveAct, &QAction::triggered, this, &SecDialog::saveFile);

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
        this, &SecDialog::updateActions);
}

void SecDialog::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        addressWidget->readFromFile(fileName);
}

void SecDialog::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (!fileName.isEmpty())
        addressWidget->writeToFile(fileName);
}

void SecDialog::updateActions(const QItemSelection &selection)
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

