#ifndef CONTACTS_H
#define CONTACTS_H

#include "contacts_global.h"
#include <QThread>
#include <QSqlDatabase>
#include <QObject>

class CONTACTS_EXPORT Contacts : public QThread
{
    QSqlDatabase db;
    bool m_exitAsked = false;
public:
    Contacts();
    void run() override;

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
