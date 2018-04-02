#include "cryptocompanion.h"
#include <QApplication>
#include "secdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Cryptocompanion w;
    w.show();

    return a.exec();
}
