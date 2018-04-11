#include "cryptocompanion.h"
#include <QApplication>
#include "registerdialog.h"

int main(int argc, char *argv[])
{
    QApplication Cryptocompan(argc, argv);
    //Cryptocompan.setQuitOnLastWindowClosed(false);
    Cryptocompanion w;
    LoginDialog logDialog;
    logDialog.show();
    if(logDialog.exec())
    w.show();

    return Cryptocompan.exec();
}
