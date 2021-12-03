#include "contact.h"
#include "ui_contact.h"
#include <QElapsedTimer>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <iomanip>
#include <iostream>
#include <QDebug>

Contact::Contact(QWidget *parent, Contacts *c)
    : QMainWindow(parent)
    , ui(new Ui::Contact)
{   
    ui->setupUi(this);
    _th1 = c;
    QStringList allColumns ={"firstname", "lastname", "email", "tel", "category", "city", "birth_day","country", "list", "company"};
    QStringList allColumnsWithID ={"GUID", "firstname", "lastname", "email", "tel", "category", "city", "birth_day","country", "list", "company"};
    ui->cbxDelete->addItems(allColumnsWithID);
    ui->cbxUpdate1->addItems(allColumns);
    ui->cbxUpdate2->addItems(allColumns);
    ui->cbxSearch->addItems(allColumnsWithID);
    ui->cbxExport->addItems(allColumnsWithID);



    _th1->db.open();
    QString requete = "SELECT * FROM contacts";
    QSqlQuery query;
    query.exec(requete);

    _th1->modal->setQuery(query);
    ui->tableView->setModel(_th1->modal);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(100);
    ui->progressBar->hide();
}

Contact::~Contact()
{
    _th1->db.close();
    _th1->clean();
    delete ui;
}

void Contact::onRefresh(const bool val)
{
    if (val){
        _th1->modal->setQuery(_th1->modal->query());
        ui->tableView->setModel(_th1->modal);
        ui->tableView->repaint();
        ui->progressBar->hide();
    }
}


void Contact::on_btnDelete_clicked()
{
    if(!(ui->tbxDelete->text().isEmpty())){
        ui->progressBar->show();
        QApplication::processEvents();
        emit onClickedDelete(ui->cbxDelete->currentText(), ui->tbxDelete->text());
    }
}


void Contact::on_btnUpdate_clicked()
{
    if(!(ui->tbxUpdate1->text().isEmpty()) && !(ui->tbxUpdate2->text().isEmpty())){
        ui->progressBar->show();
        QApplication::processEvents();
        emit onClickedUpdate(ui->cbxUpdate1->currentText(), ui->tbxUpdate1->text(), ui->cbxUpdate2->currentText(), ui->tbxUpdate2->text());
    }
}


void Contact::on_tableView_clicked(const QModelIndex &index)
{
    QVariant guid=index.sibling(index.row(),1).data();
    QVariant firstname=index.sibling(index.row(),2).data();
    QVariant lastname=index.sibling(index.row(),3).data();
    QVariant email=index.sibling(index.row(),4).data();
    QVariant tel=index.sibling(index.row(),5).data();
    QVariant category=index.sibling(index.row(),6).data();
    QVariant city=index.sibling(index.row(),7).data();
    QVariant birth_day=index.sibling(index.row(),8).data();
    QVariant country=index.sibling(index.row(),9).data();
    QVariant list=index.sibling(index.row(),10).data();
    QVariant company=index.sibling(index.row(),11).data();

    ui->lineEdit_GUID->setText(guid.toString());
    ui->lineEdit_firstname->setText(firstname.toString());
    ui->lineEdit_lastname->setText(lastname.toString());
    ui->lineEdit_email->setText(email.toString());
    ui->lineEdit_tel->setText(tel.toString());
    ui->lineEdit_category->setText(category.toString());
    ui->lineEdit_city->setText(city.toString());
    ui->lineEdit_birthday->setText(birth_day.toString());
    ui->lineEdit_country->setText(country.toString());
    ui->lineEdit_list->setText(list.toString());
    ui->lineEdit_company->setText(company.toString());
}


void Contact::on_btnImport_clicked()
{
    if(!ui->lbFolderPath->text().isNull()){
        ui->progressBar->show();
        QApplication::processEvents();
        emit onClikedImport(ui->lbFolderPath->text());
    }
}


void Contact::on_btn_Export_clicked()
{
    if(!ui->tbxExport->text().isEmpty()){
        ui->progressBar->show();
        QApplication::processEvents();
        emit onClickedExport(ui->cbxExport->currentText(), ui->tbxExport->text());
    }
}


void Contact::on_btnSearch_clicked()
{
    if(!ui->tbxSearch->text().isEmpty()){
        ui->progressBar->show();
        QApplication::processEvents();
        emit onClickedSearch(ui->cbxSearch->currentText(), ui->tbxSearch->text());
    }
}

