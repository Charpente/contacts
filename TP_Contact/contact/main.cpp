#include "contact.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Contacts c;
    Contact w(nullptr,&c);

    QObject::connect(&w, &Contact::onClickedDelete, &c, &Contacts::onDelete);
    QObject::connect(&w, &Contact::onClickedUpdate, &c, &Contacts::onUpdate);
    QObject::connect(&w, &Contact::onClikedImport, &c, &Contacts::onInsert);
    QObject::connect(&w, &Contact::onClickedExport, &c, &Contacts::onExport);
    QObject::connect(&w, &Contact::onClickedSearch, &c, &Contacts::onSearch);
    QObject::connect(&c, &Contacts::onRefresh, &w, &Contact::onRefresh);
    w.show();
    return a.exec();
}
