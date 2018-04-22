#include "cryptocompanion.h"
#include "startdialog.h"

#include <QApplication>
#include <QMetaObject>


int main(int argc, char *argv[])
{
    QApplication Cryptocompan(argc, argv);
    StartDialog start;
    Cryptocompanion w;
    if (start.exec())
    {
        w.login();
        w.show();
    }
    return Cryptocompan.exec();
}
