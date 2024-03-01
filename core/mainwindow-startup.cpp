#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::connectToDatabase()
{
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setDatabaseName("main.db");
    if (this->db.open())
        qDebug() << "Database: connection ok";
    else
        qDebug() << "Error: connection with database failed";
}

void MainWindow::setComboBoxModel()
{
    QSqlQueryModel *module_model_1 = new QSqlQueryModel;
    module_model_1->setQuery("SELECT id, name FROM module ORDER BY id");
    module_model_1->setHeaderData(0, Qt::Horizontal, tr("id"));
    module_model_1->setHeaderData(1, Qt::Horizontal, tr("Name"));
    this->ui->moduleComboBox_1->setModel(module_model_1);
    this->ui->moduleComboBox_1->setModelColumn(1);

    QSqlQueryModel *module_model_2 = new QSqlQueryModel;
    module_model_2->setQuery("SELECT id, name FROM module ORDER BY id");
    module_model_2->setHeaderData(0, Qt::Horizontal, tr("id"));
    module_model_2->setHeaderData(1, Qt::Horizontal, tr("Name"));
    this->ui->moduleComboBox_2->setModel(module_model_2);
    this->ui->moduleComboBox_2->setModelColumn(1);

    QSqlQueryModel *module_model_3 = new QSqlQueryModel;
    module_model_3->setQuery("SELECT id, name FROM driver ORDER BY id");
    module_model_3->setHeaderData(0, Qt::Horizontal, tr("id"));
    module_model_3->setHeaderData(1, Qt::Horizontal, tr("Name"));
    this->ui->driverComboBox->setModel(module_model_3);
    this->ui->driverComboBox->setModelColumn(1);
}
