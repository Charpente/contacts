#include "mythread.h"

#include <QFile>
#include <QDebug>
#include <QDir>
#include <QElapsedTimer>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QDirIterator>
#include <iomanip>
#include <iostream>

Mythread::Mythread(QObject *parent) : QThread(parent)
{

}

int Mythread::method() const
{
    return m_method;
}

void Mythread::setMethod(int newMethod)
{
    m_method = newMethod;
}

void Mythread::setDb(const QSqlDatabase &newDb)
{
    db = newDb;
}

const QString &Mythread::param() const
{
    return m_param;
}

void Mythread::setParam(const QString &newParam)
{
    m_param = newParam;
}

const QString &Mythread::key() const
{
    return m_key;
}

void Mythread::setKey(const QString &newKey)
{
    m_key = newKey;
}

bool Mythread::exitAsked() const
{
    return m_exitAsked;
}

void Mythread::setExitAsked(bool newExitAsked)
{
    m_exitAsked = newExitAsked;
}

void Mythread::run()
{

    QElapsedTimer elapsed;
    elapsed.start();

    if(m_exitAsked){
        clean();
    }
    else{
        switch (m_method) {
        case (0):
            this->insert(m_param);
            break;
        case (1):
            deleteByParam(m_param);
            break;
        case (2):
            update(m_key, m_param);
            break;
        case (3):
            exportByParam(m_param);
            break;
        default:
            break;
        }
    }
    double rate     = 0;
    double iElapsed = double(elapsed.elapsed()) / 1000;
    if (iElapsed)
        rate = 100000 / iElapsed;
    elapsed.restart();
    std::cout << std::fixed << std::setprecision(2) << std::setfill(' ');
    std::cout << "  "
              << " done in " << std::setw(6) << iElapsed << " s - " << std::setw(10) << rate << " inserts/s"
              << std::endl;
}

void Mythread::insert(const QString &dir_path)
{



}

void Mythread::deleteByParam(const QString &param)
{

}

void Mythread::update(const QString &key, const QString &value)
{

}

void Mythread::exportByParam(const QString &param)
{

}

void Mythread::clean()
{
    QSqlQuery query;
    query.exec("DROP TABLE contacts");
    if (query.lastError().isValid()) {
        qWarning() << "DROP TABLE" << query.lastError().text();
    }
    db.commit();
    db.close();
}
