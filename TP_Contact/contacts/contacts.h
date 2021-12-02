#ifndef CONTACTS_H
#define CONTACTS_H

#include "contacts_global.h"
#include <QSqlDatabase>
#include <QObject>
#include "./mythread.h"

class CONTACTS_EXPORT Contacts : public QObject
{
    bool m_exitAsked = false;
    int m_method = 0;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString m_param;
    QString m_key;
public:
    Contacts();
    //Mythread * thread;
    void insert(const QString &dir_path);

    void deleteByParam(const QString &param);

    void update(const QString &key, const QString &value);

    void exportByParam(const QString &param);

    void clean();

public slots:
    void onInsert(const QString &dir_path);
    void onDelete(const QString &param);
    void onUpdate(const QString &key, const QString &value);
    void onExport(const QString &param);
    void onClose();
};

#endif // CONTACTS_H
