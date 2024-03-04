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
#include <QLineEdit>

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

private slots:
    void on_moduleComboBox_1_currentIndexChanged(int index);
    void on_moduleComboBox_2_currentIndexChanged(int index);
    void on_driverComboBox_currentIndexChanged(int index);

    void on_n_seriesSpinBox_1_valueChanged(int arg1);
    void on_n_parallelSpinBox_1_valueChanged(int arg1);
    void on_n_seriesSpinBox_2_valueChanged(int arg1);
    void on_n_parallelSpinBox_2_valueChanged(int arg1);

    void on_horizontalSlider_valueChanged(int value);
    void on_spinBox_valueChanged(int arg1);

    void on_moduleGroupBox_2_clicked(bool checked);
    void on_checkBox_Copy_clicked(bool checked);

private:
    QSqlDatabase db;
    // LED_Luminaire luminaire;
    LED_Module *module_1;
    LED_Module *module_2;
    LED_Driver *driver;

    void connectToDatabase();
    void setComboBoxModel();

    void IndexChangeModule_1(int index);
    void IndexChangeModule_2(int index);
    void IndexChangeDriver(int index);

    void UpdateMain(int input);
    void UpdateModule(int current);
    void UpdateChannels(int current, int series, int parallel);
    void UpdateDriverLumi(int current, int total);

    void UpdateDualMain(int input);
    void UpdateDualModule(int current1, int current2);
    void UpdateDualChannels(int current1, int series1, int parallel1, int current2, int series2, int parallel2);
    void UpdateDualDriverLumi(int current1, int total1, int current2, int total2);

    void updateLimits();
    bool ModuleTwoActive();

    void checkColourI(unsigned value, unsigned threshold_low, unsigned threshold_high, QLineEdit *field);
    void checkColourD(double value, double threshold_low, double threshold_high, QLineEdit *field);
};
#endif // MAINWINDOW_H
