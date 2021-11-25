#include "contact.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Contact w;
    w.show();
    return a.exec();
}
