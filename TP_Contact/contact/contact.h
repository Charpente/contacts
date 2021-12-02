#ifndef CONTACT_H
#define CONTACT_H

#include <QMainWindow>
#include "../contacts/contacts.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Contact; }
QT_END_NAMESPACE

class Contact : public QMainWindow
{
    Q_OBJECT
    Contacts *       _th1    = nullptr;

public:
    Contact(QWidget *parent = nullptr);
    ~Contact();

private:
    Ui::Contact *ui;
};
#endif // CONTACT_H
