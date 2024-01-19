#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ledmodule.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), dbm(DbManager("people.db"))
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    LedModule currentModule = LedModule();
    double voltage = currentModule.calculate_voltage(ui->spinBox->value());
    QString volts = QString::number(voltage);
    ui->label->setText(volts);
}

void MainWindow::on_pushButton_2_clicked()
{
    if (this->dbm.isOpen())
    {
        QString result = dbm.retrieveAllPersons();
        ui->label_2->setText(result);
    }
}
