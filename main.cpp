#include "cryptocompanion.h"
#include <QApplication>
#include "secdialog.h"

int main(int argc, char *argv[])
{
    QApplication Cryptocompan(argc, argv);
    Cryptocompan.setQuitOnLastWindowClosed(false);
    Cryptocompanion w;
    w.show();

    return Cryptocompan.exec();
}
