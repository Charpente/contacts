#include "contacts.h"
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QElapsedTimer>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <iomanip>
#include <iostream>
#include <fstream>


Contacts::Contacts()
{
    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(appDataLocation);
    if (!dir.exists()) {
        dir.mkdir(appDataLocation);
        qDebug() << __FUNCTION__ << __LINE__ << "mkdir" << appDataLocation;
    }
    QString dbPath = appDataLocation + "/contacts.db";
    qDebug() << "dbPath" << dbPath;
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qCritical() << "Unable to open db" << dbPath;
    }
    else{
        qDebug() << __FUNCTION__ << __LINE__ << "creating table 'contacts'";
        QString tblFileCreate = "CREATE TABLE IF NOT EXISTS contacts ("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "GUID VARCHAR,"
                                "firstname VARCHAR,"
                                "lastname VARCHAR,"
                                "email VARCHAR,"
                                "tel VARCHAR,"
                                "category VARCHAR,"
                                "city VARCHAR,"
                                "birth_day VARCHAR,"
                                "country VARCHAR,"
                                "list VARCHAR,"
                                "company VARCHAR"
                                ");";

        QSqlQuery query;
        query.exec(tblFileCreate);
        if (query.lastError().isValid()) {
            qWarning() << query.lastError().text();
        }
    }
}

void Contacts::search(const QString &key, const QString &value)
{
    QString requete = QString("SELECT * FROM contacts where %1 like '%2%'").arg(key,value);
    QSqlQuery query;
    query.exec(requete);
    modal->setQuery(query);
}

void Contacts::insert(const QString &dir_path)
{
    QElapsedTimer elapsed;
    elapsed.start();

    QString dir = dir_path;
    QSqlQuery query;
    query.exec("pragma temp_store = memory");
    query.exec("PRAGMA synchronous = normal");
    query.exec("pragma mmap_size = 30000000000");
    query.exec("PRAGMA journal_mode = wal");

    db.transaction();

    query.prepare("INSERT INTO contacts (GUID, firstname, lastname, email, tel, category, city, birth_day, country, list, company)"
                  "VALUES (:GUID, :firstname, :lastname, :email, :tel, :category, :city, :birth_day, :country, :list, :company)");


    QDirIterator it(dir, QStringList() << "*.csv", QDir::Files, QDirIterator::Subdirectories);
    QStringList lines;
    while (it.hasNext())
    {
        QString filePath = it.next();
        qDebug() << filePath;
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << file.errorString();
        }
        while (!file.atEnd()) {
            lines.append(file.readLine());
        }

    }
    for (int i = 0; i < lines.size(); ++i) {
        QStringList splitLine= lines.at(i).split(',');
        query.bindValue(":GUID", splitLine[1]);
        query.bindValue(":firstname", splitLine[2]);
        query.bindValue(":lastname", splitLine[3]);
        query.bindValue(":email", splitLine[4]);
        query.bindValue(":tel", splitLine[5]);
        query.bindValue(":category", splitLine[6]);
        query.bindValue(":city", splitLine[7]);
        query.bindValue(":birth_day", splitLine[8]);
        query.bindValue(":country", splitLine[9]);
        query.bindValue(":list", splitLine[10]);
        query.bindValue(":company", splitLine[11]);
        query.exec();
    }
    db.commit();
    double rate     = 0;
    double iElapsed = double(elapsed.elapsed()) / 1000;
    if (iElapsed)
        rate = 1000000 / iElapsed;
    elapsed.restart();
    std::cout << std::fixed << std::setprecision(2) << std::setfill(' ');
    std::cout << "  "
              << " done in " << std::setw(6) << iElapsed << " s - " << std::setw(10) << rate << " inserts/s"
              << std::endl;
}

void Contacts::deleteByParam(const QString &key, const QString &value)
{
    QSqlQuery query;
    qDebug() << QString("DELETE FROM contacts where %1 like '%2%'").arg(key,value);
    query.exec(QString("DELETE FROM contacts where %1 like '%2%'").arg(key,value));
    db.commit();
}

void Contacts::update(const QString &key1, const QString &value1, const QString &key2, const QString &value2)
{
    QSqlQuery query;
    query.exec(QString("Update contacts set %1='%2' where %3 like '%4%'").arg(key1,value1,key2,value2));
    db.commit();
}

void Contacts::exportByParam(const QString &key, const QString &value)
{
    qDebug() << QString("Exporting contacts where %1 like '%2%' to .csv, wait ...").arg(key,value);

    QString currentLocation = QString("%1/%2_%3.csv").arg(QDir::currentPath(), key, value) ;

    qDebug() << currentLocation;

    //path du fichier csv cree
    std::ofstream exportedContacts(currentLocation.toStdString());


    QString requete = QString("SELECT * FROM contacts where %1 like '%2%'").arg(key,value);
    QSqlQuery query;
    query.exec(requete);
    if (query.lastError().isValid()) {
        qWarning() << query.lastError().text();
    }

    while (query.next()) {
        QString id = query.value(0).toString();
        QString GUID = query.value(1).toString();
        QString firstname = query.value(2).toString();
        QString lastname = query.value(3).toString();
        QString email = query.value(4).toString();
        QString tel = query.value(5).toString();
        QString category = query.value(6).toString();
        QString city = query.value(7).toString();
        QString birth_day = query.value(8).toString();
        QString country = query.value(9).toString();
        QString list = query.value(10).toString();
        QString company = query.value(11).toString();

        QString line = id+ "," +GUID+ "," +firstname+ "," +lastname+ "," +email+ "," +tel+ "," +category+ "," +city+ "," +birth_day+ "," +country+ "," +list+ "," +company.simplified()+"\n";

        exportedContacts << line.toStdString();
    }
    exportedContacts.close();
    qDebug() << QString("Done!");
}

void Contacts::clean()
{
    db.open();
    QSqlQuery query;
    query.exec("DROP TABLE contacts");
    if (query.lastError().isValid()) {
        qWarning() << "DROP TABLE" << query.lastError().text();
    }
    db.commit();
    db.close();
}

void Contacts::onInsert(const QString &dir_path)
{
    insert(dir_path);
    modal->query().exec();
    emit onRefresh(true);
}

void Contacts::onDelete(const QString &key, const QString &value)
{
    deleteByParam(key,value);
    modal->query().exec();
    emit onRefresh(true);
}

void Contacts::onUpdate(const QString &key1, const QString &value1, const QString &key2, const QString &value2)
{
    update(key1,value1,key2,value2);
    modal->query().exec();
    emit onRefresh(true);
}

void Contacts::onExport(const QString &key, const QString &value)
{
    exportByParam(key,value);
    modal->query().exec();
    emit onRefresh(true);
}

void Contacts::onSearch(const QString &key, const QString &value)
{
    search(key,value);
    modal->query().exec();
    emit onRefresh(true);
}

void Contacts::onClose()
{
    m_exitAsked = true;
}
