#ifndef CRYPTOCOMPANION_H
#define CRYPTOCOMPANION_H

#include <QMainWindow>
#include <QDialog>
#include "user.h"
#include "walletwidget.h"

namespace Ui {
class Cryptocompanion;
}

class Cryptocompanion : public QMainWindow
{
    Q_OBJECT

public:
    explicit Cryptocompanion(QWidget *parent = 0);
    ~Cryptocompanion();
        void login();


private slots:
    void updateActions(const QItemSelection &selection);
    void openFile();
    void saveFile();


private:
    Ui::Cryptocompanion *ui;
    void createMenus();
    void changePass();

    WalletWidget *walletWidget;
    QMenu *fileMenu;
    QMenu *toolMenu;
    QAction *openAct;
    QAction *saveAct;
    QAction *changeAct;
    QAction *exitAct;
    QAction *addAct;
    QAction *editAct;
    QAction *removeAct;
};

#endif // CRYPTOCOMPANION_H
