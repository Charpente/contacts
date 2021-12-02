#include "contact.h"
#include "ui_contact.h"
#include <QElapsedTimer>
#include <iomanip>
#include <iostream>

Contact::Contact(QWidget *parent)
    : QMainWindow(parent),
      _th1(new Contacts)
    , ui(new Ui::Contact)
{   
    ui->setupUi(this);
}

Contact::~Contact()
{
    delete ui;
}

