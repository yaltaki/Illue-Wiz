#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QDebug>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>

class MainModel : public QObject
{
    Q_OBJECT
public:
    explicit MainModel(QObject *parent = nullptr, const QString &db_path = QString("main.db"));
    ~MainModel();
signals:

private:
    QSqlDatabase db;
};

#endif // MAINMODEL_H
