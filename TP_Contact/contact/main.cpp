#include "contact.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Contacts c;
    Contact w(nullptr,&c);

    QObject::connect(&w, &Contact::onClickedDelete, &c, &Contacts::onDelete);
    QObject::connect(&w, &Contact::onClickedUpdate, &c, &Contacts::onUpdate);
    w.show();
    return a.exec();
}
