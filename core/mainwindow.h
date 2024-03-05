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

    void checkColourI(unsigned value, QLineEdit *field, bool ModOrDriver); // ModOrDriver: true = mod / false = driver
    void checkColourV(double value, QLineEdit *field, bool ModOrDriver);
    void checkColourP(double value, QLineEdit *field, bool ModOrDriver);
    void checkColourE(double value, QLineEdit *field);

    void checkColourI_D(unsigned value1, unsigned value2, QLineEdit *field, bool ModOrDriver); // ModOrDriver: true = mod / false = driver
    void checkColourV_D(double value1, double value2, QLineEdit *field, bool ModOrDriver);
    void checkColourP_D(double value1, double value2, QLineEdit *field, bool ModOrDriver);
    void checkColourE_D(double value1, double value2, QLineEdit *field);

    void ModuleColour(unsigned current, double moduleVoltage, double modulePower);
    void ChannelsColour(double totalVoltage, double totalPower);
    void DriverLumiColour(double totalPower, double efficiency, double inputPower);
};
#endif // MAINWINDOW_H
