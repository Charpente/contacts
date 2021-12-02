#ifndef CONTACT_H
#define CONTACT_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "../contacts/contacts.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Contact; }
QT_END_NAMESPACE

class Contact : public QMainWindow
{
    Q_OBJECT
    Contacts *       _th1    = nullptr;
    QSqlQueryModel*modal = new QSqlQueryModel();

public:
    Contact(QWidget *parent = nullptr, Contacts *c = nullptr);
    ~Contact();
    void refresh();

signals:
    void onClickedDelete(const QString &key, const QString &value);
    void onClickedUpdate(const QString &key1, const QString &value1, const QString &key2, const QString &value2);

private slots:
    void on_btnDelete_clicked();

    void on_btnUpdate_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::Contact *ui;
};
#endif // CONTACT_H
