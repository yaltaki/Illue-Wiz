#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ledmodule.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), dbm(DbManager("people.db"))
{
    ui->setupUi(this);
    connect(ui->pushButton_Test, SIGNAL(clicked()), this, SLOT(testFunction()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::testFunction()
{
    this->ui->label_2->setText("Test");
}

void MainWindow::on_pushButton_clicked()
{
    LedModule currentModule = LedModule();
    double voltage = currentModule.calculate_voltage(ui->spinBox->value());
    QString volts = QString::number(voltage);
    ui->label->setText(volts);
}

void MainWindow::on_pushButtonAdd_clicked()
{
    if (this->dbm.isOpen())
    {
        this->dbm.addPerson(ui->textEdit->toPlainText());
    }
    this->on_pushButtonRetrieveAll_clicked();
}


void MainWindow::on_pushButtonRemove_clicked()
{
    if (this->dbm.isOpen())
    {
        dbm.removePerson(ui->textEdit->toPlainText());
    }
    this->on_pushButtonRetrieveAll_clicked();
}


void MainWindow::on_pushButtonRetrieveAll_clicked()
{
    if (this->dbm.isOpen())
    {
        QString result = dbm.retrieveAllPersons();
        ui->label_2->setText(result);
    }
}

