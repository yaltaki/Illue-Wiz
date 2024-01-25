#include "mainmodel.h"

MainModel::MainModel(QObject *parent, const QString &db_path)
    : QObject{parent}
{
    qDebug() << "Starting MainModel";
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setDatabaseName(db_path);
    if (this->db.open())
    {
        qDebug() << "Database: connection ok";
    }
    else
    {
        qDebug() << "Error: connection with database failed";
    }
}

MainModel::~MainModel()
{
    if (this->db.isOpen())
    {
        this->db.close();
    }
}
