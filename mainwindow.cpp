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
    module_model_1->setQuery("SELECT id, name FROM module ORDER BY id DESC");
    module_model_1->setHeaderData(0, Qt::Horizontal, tr("id"));
    module_model_1->setHeaderData(1, Qt::Horizontal, tr("Name"));
    this->ui->moduleComboBox_1->setModel(module_model_1);
    this->ui->moduleComboBox_1->setModelColumn(1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 void MainWindow::on_pushButton_clicked()
{
     LedModule currentModule = LedModule();
     double voltage = currentModule.calculate_voltage(ui->spinBox->value());
     QString volts = QString::number(voltage);
     ui->label->setText(volts);
 }
*/

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
