#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlIndex>
#include <QAbstractItemModel>
#include <QPushButton>
#include <QSqlDatabase>

#include "LED_components/led_module.h"
#include "LED_components/led_driver.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void onStepChange(int val) const;
    void updateLimitBoxes() const;

private slots:
    void IndexChangeModule_1(int index);
    void IndexChangeModule_2(int index);
    void IndexChangeDriver(int index);

private:
    QSqlDatabase db;
    // LED_Luminaire luminaire;
    LED_Module *module_1;
    LED_Module *module_2;
    LED_Driver *driver;
};
#endif // MAINWINDOW_H
