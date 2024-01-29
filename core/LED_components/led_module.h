#ifndef LED_MODULE_H
#define LED_MODULE_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlIndex>
#include <QAbstractItemModel>
#include <QPushButton>
#include <QSqlDatabase>
#include <QString>
#include "mainwindow.h"

class LED_Module
{
public:
    LED_Module();

    QString Manufacturer;
    int If[3];
    float C_LF[3];
    float C_VI[3];

    void Update(int index, MainWindow* Uip);
    void Copy(LED_Module* CopyTo);
    void PrintMake();
    void PrintIf();
    void PrintCLF();
    void PrintCVI();
    float CalcLF(int index);
    float CalcVI(int index);
    float CalcPower(int index);

    ~LED_Module();
};

#endif // LED_MODULE_H

// If
// LF_I
// V_I
