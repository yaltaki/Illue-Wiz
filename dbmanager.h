#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

class DbManager
{
private:
    QSqlDatabase m_db;

public:
    DbManager(const QString &path);
    ~DbManager();
    bool isOpen() const;
    bool createTable();
    bool addPerson(const QString &name);
    bool removePerson(const QString &name);
    bool personExists(const QString &name);
    QString retrieveAllPersons() const;
    bool removeAllPersons();
};

#endif // DBMANAGER_H
