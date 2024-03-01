#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::IndexChangeModule_1(int index)
{
    qDebug() << "Module 1 Index Changed:" << index;
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

    unsigned If[3];
    If[0] = query->value(rec.indexOf("If_min")).toUInt();
    If[1] = query->value(rec.indexOf("If_rated")).toUInt();
    If[2] = query->value(rec.indexOf("If_max")).toUInt();

    double LF_I[3];
    LF_I[0] = query->value(rec.indexOf("c_LF_I_1")).toDouble();
    LF_I[1] = query->value(rec.indexOf("c_LF_I_2")).toDouble();
    LF_I[2] = query->value(rec.indexOf("c_LF_I_3")).toDouble();

    double V_I[3];
    V_I[0] = query->value(rec.indexOf("c_V_I_1")).toDouble();
    V_I[1] = query->value(rec.indexOf("c_V_I_2")).toDouble();
    V_I[2] = query->value(rec.indexOf("c_V_I_3")).toDouble();

    if (!(this->module_1 == nullptr))
        delete this->module_1;

    this->module_1 = new LED_Module(
        name, code, manu,
        If, LF_I, V_I);

    delete query;
}

void MainWindow::IndexChangeModule_2(int index)
{
    qDebug() << "Module 2 Index Changed:" << index;
    QAbstractItemModel *model = this->ui->moduleComboBox_2->model();
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

    unsigned If[3];
    If[0] = query->value(rec.indexOf("If_min")).toUInt();
    If[1] = query->value(rec.indexOf("If_rated")).toUInt();
    If[2] = query->value(rec.indexOf("If_max")).toUInt();

    double LF_I[3];
    LF_I[0] = query->value(rec.indexOf("c_LF_I_1")).toDouble();
    LF_I[1] = query->value(rec.indexOf("c_LF_I_2")).toDouble();
    LF_I[2] = query->value(rec.indexOf("c_LF_I_3")).toDouble();

    double V_I[3];
    V_I[0] = query->value(rec.indexOf("c_V_I_1")).toDouble();
    V_I[1] = query->value(rec.indexOf("c_V_I_2")).toDouble();
    V_I[2] = query->value(rec.indexOf("c_V_I_3")).toDouble();

    if (!(this->module_2 == nullptr))
        delete this->module_2;

    this->module_2 = new LED_Module(
        name, code, manu,
        If, LF_I, V_I);

    delete query;
}

void MainWindow::IndexChangeDriver(int index)
{
    qDebug() << "currentDriverIndexChanged:" << index;
    QAbstractItemModel *model = this->ui->driverComboBox->model();
    QModelIndex driver_index = model->index(index, 0);
    int driver_id = model->data(driver_index).toInt();

    QSqlQuery *query = new QSqlQuery;
    query->prepare("SELECT * FROM driver WHERE id=(:driver_id)");
    query->bindValue(":driver_id", driver_id);
    query->exec();
    query->first();
    QSqlRecord rec = query->record();

    QString name = query->value(rec.indexOf("name")).toString();
    QString code = query->value(rec.indexOf("code")).toString();
    QString manu = query->value(rec.indexOf("manufacturer")).toString();

    unsigned Vf[2];
    Vf[0] = query->value(rec.indexOf("V_min")).toUInt();
    Vf[1] = query->value(rec.indexOf("V_max")).toUInt();

    unsigned If[3];
    If[0] = query->value(rec.indexOf("If_min")).toUInt();
    If[1] = query->value(rec.indexOf("If_default")).toUInt();
    If[2] = query->value(rec.indexOf("If_max")).toUInt();

    unsigned P_out[2];
    P_out[0] = query->value(rec.indexOf("P_1_max")).toUInt();
    P_out[1] = query->value(rec.indexOf("P_2_max")).toUInt();

    bool bDualChannel = query->value(rec.indexOf("isDualChannel")).toBool();

    double C_N[3];
    C_N[0] = query->value(rec.indexOf("c_n_1")).toDouble();
    C_N[1] = query->value(rec.indexOf("c_n_2")).toDouble();
    C_N[2] = query->value(rec.indexOf("c_n_3")).toDouble();

    double C_PF[3];
    C_PF[0] = query->value(rec.indexOf("c_pf_1")).toDouble();
    C_PF[1] = query->value(rec.indexOf("c_pf_2")).toDouble();
    C_PF[2] = query->value(rec.indexOf("c_pf_3")).toDouble();

    if (!(this->driver == nullptr))
        delete this->driver;

    this->driver = new LED_Driver(
        name, code, manu,
        Vf, If, P_out,
        bDualChannel, C_N, C_PF);

    delete query;
}
