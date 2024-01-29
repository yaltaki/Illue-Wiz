#include "led_module.h"
#include "mainwindow.cpp"
#include "ui_mainwindow.h"

LED_Module::LED_Module()
{
    /*QSqlQuery *numList = new QSqlQuery;
    numList->prepare("SELECT COUNT(id) FROM module");
    numList->exec();
    int numOfClasses = numList->value(0).toInt();
    LED_Module *Modu_s[numOfClasses];
    for(int i = 0; i < numOfClasses; i++)
    {
        Modu_s[i] = new LED_Module();
    }*/
}

void LED_Module::Update(int index, MainWindow* Uip)
{
    QAbstractItemModel* model = Uip->ui->moduleComboBox_1->model();
    QModelIndex module_index = model->index(index, 0);
    int module_id = model->data(module_index).toInt();

    QSqlQuery *query = new QSqlQuery;
    query->prepare("SELECT * FROM module WHERE id = (:module_id)");
    query->bindValue(":module_id", module_id);
    query->exec();
    query->first();

    this->Manufacturer = query->value("manufacturer").toString();
    this->If[0] = query->value("If_min").toInt();
    this->If[1] = query->value("If_rated").toInt();
    this->If[2] = query->value("If_max").toInt();
    this->C_LF[0] = query->value("c_LF_I_1").toFloat();
    this->C_LF[1] = query->value("c_LF_I_2").toFloat();
    this->C_LF[2] = query->value("c_LF_I_3").toFloat();
    this->C_VI[0] = query->value("c_V_I_1").toFloat();
    this->C_VI[1] = query->value("c_V_I_2").toFloat();
    this->C_VI[2] = query->value("c_V_I_3").toFloat();
}

void LED_Module::Copy(LED_Module* CopyTo)
{
    CopyTo->Manufacturer = this->Manufacturer;
    CopyTo->If[0] = this->If[0];
    CopyTo->If[1] = this->If[1];
    CopyTo->If[2] = this->If[2];
    CopyTo->C_LF[0] = this->C_LF[0];
    CopyTo->C_LF[1] = this->C_LF[1];
    CopyTo->C_LF[2] = this->C_LF[2];
    CopyTo->C_VI[0] = this->C_VI[0];
    CopyTo->C_VI[1] = this->C_VI[1];
    CopyTo->C_VI[2] = this->C_VI[2];
}

void LED_Module::PrintMake()
{
    qDebug() << "Manufacturer: " << this->Manufacturer;
}

void LED_Module::PrintIf()
{
    qDebug() << "Forward Currents: " << this->If[0] << " / " <<
        this->If[1] << " / " << this->If[2];
}

void LED_Module::PrintCLF()
{
    qDebug() << "Forward Luminal Flux: " << this->C_LF[0] << " / " <<
        this->C_LF[1] << " / " << this->C_LF[2];
}

void LED_Module::PrintCVI()
{
    qDebug() << "Forward Voltages: " << this->C_VI[0] << " / " <<
        this->C_VI[1] << " / " << this->C_VI[2];
}

LED_Module::~LED_Module()
{
    // Decons
}
