#include "mainmodel.h"

MainModel::MainModel(QObject *parent, const QString &db_path)
    : QObject{parent}
{
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setDatabaseName(db_path);
    this->openDB();
}

bool MainModel::openDB()
{
    this->db.open();
    if (this->db.isOpenError())
    {
        qDebug() << "Database  : " << db.lastError().databaseText();
        qDebug() << "Driver    : " << db.lastError().driverText();
        qDebug() << "Error code: " << db.lastError().nativeErrorCode();
        return false;
    }
    return true;
}

MainModel::~MainModel()
{
    if (this->db.isOpen())
    {
        this->db.close();
    }
}