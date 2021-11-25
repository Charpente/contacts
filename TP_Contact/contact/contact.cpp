#include "contact.h"
#include "ui_contact.h"

Contact::Contact(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Contact)
{
    ui->setupUi(this);
}

Contact::~Contact()
{
    delete ui;
}

