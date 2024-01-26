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

    connect(ui->btn_steps_25,&QPushButton::clicked, this, [this]{ onStepChange(25); });
    connect(ui->btn_steps_50,&QPushButton::clicked, this, [this]{ onStepChange(50); });
    connect(ui->btn_steps_100,&QPushButton::clicked, this, [this]{ onStepChange(100); });
    connect(ui->btn_steps_200,&QPushButton::clicked, this, [this]{ onStepChange(200); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_moduleComboBox_1_currentIndexChanged(int index)
{
    QSqlQueryModel *If_MinMax = new QSqlQueryModel;
    If_MinMax->setQuery("SELECT id, If_min, If_max FROM module ORDER BY id");
    If_MinMax->setHeaderData(0, Qt::Horizontal, tr("id"));
    If_MinMax->setHeaderData(1, Qt::Horizontal, tr("If_min"));
    If_MinMax->setHeaderData(2, Qt::Horizontal, tr("If_max"));
    QString concac = "";
    concac = If_MinMax->data(If_MinMax->index(index, 1)).toString();
    concac += " / ";
    concac += If_MinMax->data(If_MinMax->index(index, 2)).toString();
    this->ui->module_If_maxLineEdit_1->setText(concac);
}

void MainWindow::onStepChange(int val)
{
    this->ui->stepsSpinBox->setValue(val);
}

void MainWindow::on_driverComboBox_currentIndexChanged(int index)
{
    QSqlQueryModel *DR_MinMax = new QSqlQueryModel;
    DR_MinMax->setQuery("SELECT id, If_min, If_max, V_min, V_max, P_1_max, P_2_max, isDualChannel FROM driver ORDER BY id");
    DR_MinMax->setHeaderData(0, Qt::Horizontal, tr("id"));
    DR_MinMax->setHeaderData(1, Qt::Horizontal, tr("If_min"));
    DR_MinMax->setHeaderData(2, Qt::Horizontal, tr("If_max"));
    DR_MinMax->setHeaderData(3, Qt::Horizontal, tr("V_min"));
    DR_MinMax->setHeaderData(4, Qt::Horizontal, tr("V_max"));
    DR_MinMax->setHeaderData(5, Qt::Horizontal, tr("P_1_max"));
    DR_MinMax->setHeaderData(6, Qt::Horizontal, tr("P_2_max"));
    DR_MinMax->setHeaderData(7, Qt::Horizontal, tr("isDualChannel"));

    QString concac1 = "";
    concac1 = DR_MinMax->data(DR_MinMax->index(index, 1)).toString();
    concac1 += " / ";
    concac1 += DR_MinMax->data(DR_MinMax->index(index, 2)).toString();

    QString concac2 = "";
    concac2 = DR_MinMax->data(DR_MinMax->index(index, 3)).toString();
    concac2 += " / ";
    concac2 += DR_MinMax->data(DR_MinMax->index(index, 4)).toString();

    QString concac3 = "";
    if(DR_MinMax->data(DR_MinMax->index(index,7)).toBool())
    {
        concac3 = DR_MinMax->data(DR_MinMax->index(index, 5)).toString();
        concac3 += " / ";
        concac3 += DR_MinMax->data(DR_MinMax->index(index, 6)).toString();
    } else {
        concac3 = DR_MinMax->data(DR_MinMax->index(index, 5)).toString();
    }

    this->ui->driver_If_maxLineEdit->setText(concac1);
    this->ui->driver_V_maxLineEdit->setText(concac2);
    this->ui->driver_P_maxLineEdit->setText(concac3);
}

