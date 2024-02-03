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

    connect(ui->btn_steps_25, &QPushButton::clicked, this, [this]
            { onStepChange(25); });
    connect(ui->btn_steps_50, &QPushButton::clicked, this, [this]
            { onStepChange(50); });
    connect(ui->btn_steps_100, &QPushButton::clicked, this, [this]
            { onStepChange(100); });
    connect(ui->btn_steps_200, &QPushButton::clicked, this, [this]
            { onStepChange(200); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_moduleComboBox_1_currentIndexChanged(int index)
{
    QAbstractItemModel *model = this->ui->moduleComboBox_1->model();
    QModelIndex module_index = model->index(index, 0);
    int module_id = model->data(module_index).toInt();

    QSqlQuery *query = new QSqlQuery;

    query->prepare("SELECT * FROM module WHERE id=(:module_id)");
    query->bindValue(":module_id", module_id);
    query->exec();
    query->first();

    QSqlRecord rec = query->record();
    QString name = query->value(rec.indexOf("name")).toString();
    QString code = query->value(rec.indexOf("code")).toString();
    QString manu = query->value(rec.indexOf("manufacturer")).toString();
    // If
    unsigned If[3];
    If[0] = query->value(rec.indexOf("If_min")).toUInt();
    If[1] = query->value(rec.indexOf("If_rated")).toUInt();
    If[2] = query->value(rec.indexOf("If_max")).toUInt();
    // LF_I
    double LF_I[3];
    LF_I[0] = query->value(rec.indexOf("c_LF_I_1")).toDouble();
    LF_I[1] = query->value(rec.indexOf("c_LF_I_2")).toDouble();
    LF_I[2] = query->value(rec.indexOf("c_LF_I_3")).toDouble();
    // V_I
    double V_I[3];
    V_I[0] = query->value(rec.indexOf("c_V_I_1")).toDouble();
    V_I[1] = query->value(rec.indexOf("c_V_I_2")).toDouble();
    V_I[2] = query->value(rec.indexOf("c_V_I_3")).toDouble();

    //delete this->module_1;
    this->module_1 = new LED_Module(
        name, code, manu,
        If, LF_I, V_I);

    this->ui->module_If_maxLineEdit_1->setText(this->module_1->get_current_limits());
    this->ui->module_V_maxLineEdit_1->setText(this->module_1->get_voltage_limits());
}

void MainWindow::onStepChange(int val)
{
    this->ui->stepsSpinBox->setValue(val);
}

// void MainWindow::on_driverComboBox_currentIndexChanged(int index)
// {
//     QAbstractItemModel *model = this->ui->driverComboBox->model();
//     QModelIndex driver_index = model->index(index, 0);
//     int driver_id = model->data(driver_index).toInt();

//     QSqlQuery *query = new QSqlQuery;

//     query->prepare("SELECT * FROM driver WHERE id=(:driver_id)");
//     query->bindValue(":driver_id", driver_id);
//     query->exec();
//     query->first();

//     QSqlRecord rec = query->record();
//     QString name = query->value(rec.indexOf("name")).toString();
//     QString code = query->value(rec.indexOf("code")).toString();
//     QString manu = query->value(rec.indexOf("manufacturer")).toString();

//     // Vf
//     unsigned Vf[2];
//     Vf[0] = query->value(rec.indexOf("V_min")).toUInt();
//     Vf[1] = query->value(rec.indexOf("V_max")).toUInt();

//     // If
//     unsigned If[3];
//     If[0] = query->value(rec.indexOf("If_min")).toUInt();
//     If[1] = query->value(rec.indexOf("If_default")).toUInt();
//     If[2] = query->value(rec.indexOf("If_max")).toUInt();

//     // P_out
//     unsigned P_out[2];
//     P_out[0] = query->value(rec.indexOf("P_1_max")).toUInt();
//     P_out[1] = query->value(rec.indexOf("P_2_max")).toUInt();

//     bool bDualChannel = query->value(rec.indexOf("isDualChannel")).toBool();

//     // C_N
//     double C_N[3];
//     C_N[0] = query->value(rec.indexOf("c_n_1")).toDouble();
//     C_N[1] = query->value(rec.indexOf("c_n_2")).toDouble();
//     C_N[2] = query->value(rec.indexOf("c_n_3")).toDouble();

//     // C_PF
//     double C_PF[3];
//     C_PF[0] = query->value(rec.indexOf("c_pf_1")).toDouble();
//     C_PF[1] = query->value(rec.indexOf("c_pf_2")).toDouble();
//     C_PF[2] = query->value(rec.indexOf("c_pf_3")).toDouble();

//     delete this->driver;
//     this->driver = new LED_Driver(
//         name,code,manu,
//         Vf,If,P_out,
//         bDualChannel, C_N, C_PF
//     );

//     this->ui->driver_If_maxLineEdit->setText(this->driver->get_current_limits());
//     this->ui->driver_V_maxLineEdit->setText(this->driver->get_voltage_limits());
//     this->ui->driver_P_maxLineEdit->setText(this->driver->get_power_limits());
// }
