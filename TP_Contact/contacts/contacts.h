#ifndef CONTACTS_H
#define CONTACTS_H

#include "contacts_global.h"
#include <QSqlDatabase>
#include <QObject>
#include <QSqlQueryModel>

class CONTACTS_EXPORT Contacts : public QObject
{
    Q_OBJECT
public:
    Contacts();
    bool m_exitAsked = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QSqlQueryModel*modal = new QSqlQueryModel();

    void search(const QString &key, const QString &value);

    void insert(const QString &dir_path);

    void deleteByParam(const QString &key, const QString &value);

    void update(const QString &key1, const QString &value1, const QString &key2, const QString &value2);

    void exportByParam(const QString &key, const QString &value);

    void clean();

signals:
    void onRefresh(const bool val);

public slots:
    void onInsert(const QString &dir_path);
    void onDelete(const QString &key, const QString &value);
    void onUpdate(const QString &key1, const QString &value1, const QString &key2, const QString &value2);
    void onExport(const QString &key, const QString &value);
    void onSearch(const QString &key, const QString &value);
    void onClose();
};

#endif // CONTACTS_H
