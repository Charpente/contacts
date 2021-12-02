#include "contact.h"
#include "ui_contact.h"
#include <QElapsedTimer>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <iomanip>
#include <iostream>

Contact::Contact(QWidget *parent)
    : QMainWindow(parent),
      _th1(new Contacts)
    , ui(new Ui::Contact)
{   
    ui->setupUi(this);
    QStringList allColumns ={"firstname", "lastname", "email", "tel", "category", "city", "birth_day","country", "list", "company"};
    ui->cbxDelete->addItems(allColumns);
    ui->cbxUpdate1->addItems(allColumns);
    ui->cbxUpdate2->addItems(allColumns);


    QSqlQueryModel*modal = new QSqlQueryModel();

    _th1->db.open();
    QString requete = "SELECT * FROM contacts";
    QSqlQuery query;
    query.exec(requete);

    modal->setQuery(query);
    ui->tableView->setModel(modal);
}

Contact::~Contact()
{
    _th1->clean();
    delete ui;
}

