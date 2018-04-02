#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>
#include <QMainWindow>
#include "addresswidget.h"

namespace Ui {
class SecDialog;
}

class SecDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = 0);
    ~SecDialog();

private:
    Ui::SecDialog *ui;
    void createMenus();

    AddressWidget *addressWidget;
    QMenu *fileMenu;
    QMenu *toolMenu;
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *addAct;
    QAction *editAct;
    QAction *removeAct;

private slots:
    void updateActions(const QItemSelection &selection);
    void openFile();
    void saveFile();
};


#endif // SECDIALOG_H
