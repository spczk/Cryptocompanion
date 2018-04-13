#include "cryptocompanion.h"
#include <QApplication>
#include "registerdialog.h"
#include "startdialog.h"

int main(int argc, char *argv[])
{
    QApplication Cryptocompan(argc, argv);
    //Cryptocompan.setQuitOnLastWindowClosed(false);
    StartDialog start;
    start.show();
    Cryptocompanion w;
    if (start.exec()==1)
    {
    w.login();
    w.show();
    }
//    else if (start.exec()==0)
//    {
//        return Cryptocompan.exec();
//    }
    return Cryptocompan.exec();
}
