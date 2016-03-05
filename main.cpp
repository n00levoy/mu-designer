#include "designer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    designer w;
    w.setMinimumWidth(800);
    w.show();

    return a.exec();
}
