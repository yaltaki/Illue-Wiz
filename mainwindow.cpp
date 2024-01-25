#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setDatabaseName("main.db");
    if (this->db.open())
    {
        qDebug() << "Database: connection ok";
    }
    else
    {
        qDebug() << "Error: connection with database failed";
    }

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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_steps_25_clicked()
{
    ui->stepsSpinBox->setValue(25);
}

void MainWindow::on_btn_steps_50_clicked()
{
    ui->stepsSpinBox->setValue(50);
}

void MainWindow::on_btn_steps_100_clicked()
{
    ui->stepsSpinBox->setValue(100);
}

void MainWindow::on_btn_steps_200_clicked()
{
    ui->stepsSpinBox->setValue(200);
}

// void MainWindow::on_moduleComboBox_1_currentIndexChanged(int index)
// {
//     ui->module_If_maxLineEdit_1->setText(ui->tableWidget->item(index - 1, 0)->text());
// }

// void MainWindow::on_calc_clicked()
// {
//     int index = ui->moduleComboBox_1->currentIndex();
//     // index--;
//     ui->module_If_maxLineEdit_1->setText(ui->tableWidget->item(index, 0)->text());
// }

void MainWindow::on_moduleComboBox_1_activated(int index)
{
    //
}

void MainWindow::on_moduleComboBox_1_currentIndexChanged(int index)
{
    QSqlQueryModel *If_MinMax = new QSqlQueryModel;
    If_MinMax->setQuery("SELECT id, If_min, If_max FROM driver ORDER BY id");
    If_MinMax->setHeaderData(0, Qt::Horizontal, tr("id"));
    If_MinMax->setHeaderData(1, Qt::Horizontal, tr("If_min"));
    If_MinMax->setHeaderData(2, Qt::Horizontal, tr("If_max"));
    QString concac = "";
    concac = If_MinMax->data(If_MinMax->index(index-1, 1)).toString();
    concac += " / ";
    concac += If_MinMax->data(If_MinMax->index(index-1, 2)).toString();
    this->ui->module_If_maxLineEdit_1->setText(concac);
}

