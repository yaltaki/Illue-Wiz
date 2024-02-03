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

#include "core/LED_components/led_module.h"

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
    void onStepChange(int val);
    ~MainWindow();

private slots:
    void on_moduleComboBox_1_currentIndexChanged(int index);

    void on_driverComboBox_currentIndexChanged(int index);

private:
    QSqlDatabase db;
    // LED_Luminaire luminaire;
    LED_Module *module_1;
};
#endif // MAINWINDOW_H
