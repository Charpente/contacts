#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QSqlDatabase>

class Mythread : public QThread
{

public:
    explicit Mythread(QObject *parent = nullptr);
    bool m_exitAsked = false;
    int m_method = 0;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString m_param;
    QString m_key;

    void run() override;

    void insert(const QString &dir_path);

    void deleteByParam(const QString &param);

    void update(const QString &key, const QString &value);

    void exportByParam(const QString &param);

    void clean();

    int method() const;
    void setMethod(int newMethod);

    void setDb(const QSqlDatabase &newDb);

    const QString &param() const;
    void setParam(const QString &newParam);

    const QString &key() const;
    void setKey(const QString &newKey);

    bool exitAsked() const;
    void setExitAsked(bool newExitAsked);
};

#endif // MYTHREAD_H
