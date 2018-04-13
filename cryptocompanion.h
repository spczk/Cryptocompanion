#ifndef CRYPTOCOMPANION_H
#define CRYPTOCOMPANION_H

#include <QMainWindow>
#include <QDialog>
#include "user.h"
#include "addresswidget.h"

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

    AddressWidget *addressWidget;
    QMenu *fileMenu;
    QMenu *toolMenu;
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *addAct;
    QAction *editAct;
    QAction *removeAct;
};

#endif // CRYPTOCOMPANION_H
