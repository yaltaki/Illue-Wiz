#include "dbmanager.h"

DbManager::DbManager(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database failed";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

DbManager::~DbManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool DbManager::isOpen() const
{
    return m_db.isOpen();
}

bool DbManager::createTable()
{
    bool success = true;

    QSqlQuery query;
    query.prepare("CREATE TABLE people(id INTEGER PRIMARY KEY, name TEXT);");
    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'people': one might already exist.";
        success = false;
    }

    return success;
}

bool DbManager::addPerson(const QString& name)
{
    bool success = false;

    if (name.isEmpty()) {
        qDebug() << "Adding person failed: name cannot be empty";
        return success;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO people (name) VALUES (:name)");
    query.bindValue(":name", name);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "addPerson error:" << query.lastError();
    }

    return success;
}

bool DbManager::removePerson(const QString& name)
{

    if(name.isEmpty()) {
        qDebug() << "removePerson failed: name cannot be empty";
        return false;
    }

    if (!personExists(name)) {
        qDebug() << "removePerson failed: " << name << " does not exist";
        return false;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM people WHERE name = (:name) ");
    query.bindValue(":name", name);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "removePerson failed: " << query.lastError();
        return false;
    }
}

bool DbManager::personExists(const QString& name)
{
    if(name.isEmpty()) {
        qDebug() << "removePerson failed: name cannot be empty";
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM people WHERE name = (:name)");
    query.bindValue(":name", name);
    query.exec();
    query.first();
    int count = query.value(0).toInt();
    if (count < 1)
    {
        qDebug() << "No person with that name exists";
        return false;
    }
    if (count > 1)
    {
        qDebug() << "Too many people with the same name";
        return false;
    }

    return true;
}

QString DbManager::retrieveAllPersons() const
{
    QSqlQuery query;
    query.prepare("SELECT * FROM people");
    query.exec();
    QString result;
    unsigned i{0};
    while(query.next())
    {
        if (i == 0)
        {
            result += query.value(1).toString();
        } else
        {
            result += ", " + query.value(1).toString();
        }
        i++;
    }
    return result;
}
