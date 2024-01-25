#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      dbm(DbManager("people.db"))
{
    ui->setupUi(this);
    //connect(ui->btn_steps_25, SIGNAL(clicked()), this, SLOT(testFunction()));

    //QWidget mycb = new QWidget;

    ui->moduleComboBox_1->addItem("1");
    ui->moduleComboBox_1->addItem("2");
    ui->moduleComboBox_1->addItem("3");
    ui->moduleComboBox_1->addItem("4");
    ui->moduleComboBox_1->addItem("5");
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::testFunction()
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
}*/

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

    ui->moduleComboBox_1->addItem("1");
    ui->moduleComboBox_1->addItem("2");
    ui->moduleComboBox_1->addItem("3");
    ui->moduleComboBox_1->addItem("4");
    ui->moduleComboBox_1->addItem("5");
}


void MainWindow::on_moduleComboBox_1_activated(int index)
{
    ui->moduleComboBox_1->show();
}


void MainWindow::on_moduleComboBox_1_currentIndexChanged(int index)
{
    ui->module_If_maxLineEdit_1->setText(ui->tableWidget->item(index-1,0)->text());
}


void MainWindow::on_calc_clicked()
{
    int index = ui->moduleComboBox_1->currentIndex();
    //index--;
    ui->module_If_maxLineEdit_1->setText(ui->tableWidget->item(index,0)->text());
}

