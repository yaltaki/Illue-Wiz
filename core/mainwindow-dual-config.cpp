#include <QApplication>

#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::UpdateDualMain(int input)
{
    int series1 = ui->n_seriesSpinBox_1->value();
    int parallel1 = ui->n_parallelSpinBox_1->value();
    int total1 = series1 * parallel1;
    int current1 = input / parallel1;

    int series2 = ui->n_seriesSpinBox_2->value();
    int parallel2 = ui->n_parallelSpinBox_2->value();
    int total2 = series2 * parallel2;
    int current2 = input / parallel2;

    UpdateDualModule(current1, current2);
    UpdateDualChannels(current1, series1, parallel1, current2, series2, parallel2);
    UpdateDualDriverLumi(current1, total1, current2, total2);
}

void MainWindow::UpdateDualModule(int current1, int current2)
{
    if(module_1 != nullptr && module_2 != nullptr)
    {
        double moduleFlux1 = this->module_1->calc_flux(current1);
        double moduleVoltage1 = this->module_1->calc_voltage(current1);
        double modulePower1 = this->module_1->calc_power(current1);

        double moduleFlux2 = this->module_2->calc_flux(current2);
        double moduleVoltage2 = this->module_2->calc_voltage(current2);
        double modulePower2 = this->module_2->calc_power(current2);

        this->ui->moduleCurrentLineEdit->setText(QString("%1 mA / %2 mA").arg(current1).arg(current2));
        this->ui->moduleFluxLineEdit->setText(QString("%1 lm / %2 lm").arg(QString::number(moduleFlux1, 'f', 0)).arg(QString::number(moduleFlux2, 'f', 0)));
        this->ui->moduleVoltageLineEdit->setText(QString("%1 V / %2 V").arg(QString::number(moduleVoltage1, 'f', 1)).arg(QString::number(moduleVoltage2, 'f', 1)));
        this->ui->modulePowerLineEdit->setText(QString("%1 W / %2 W").arg(QString::number(modulePower1, 'f', 2)).arg(QString::number(modulePower2, 'f', 2)));
    }
}

void MainWindow::UpdateDualChannels(int current1, int series1, int parallel1, int current2, int series2, int parallel2)
{
    if(module_1 != nullptr && module_2 != nullptr)
    {
        double totalFlux1 = this->module_1->calc_flux(current1) * series1 * parallel1; // is also nominal flux
        double totalVoltage1 = this->module_1->calc_voltage(current1) * series1;
        double totalPower1 = this->module_1->calc_power(current1) * series1 * parallel1; // is also output power

        double totalFlux2 = this->module_2->calc_flux(current2) * series2 * parallel2; // is also nominal flux
        double totalVoltage2 = this->module_2->calc_voltage(current2) * series2;
        double totalPower2 = this->module_2->calc_power(current2) * series2 * parallel2; // is also output power

        this->ui->channelLayoutLineEdit->setText(QString("%1 P x %2 S / %3 P x %4 S").arg(parallel1).arg(series1).arg(parallel2).arg(series2));
        this->ui->numberOfModulesLineEdit->setText(QString("%1").arg((series1 * parallel1) + (series2 * parallel2)));
        this->ui->channelFluxLineEdit->setText(QString("%1 lm / %2 lm").arg(QString::number(totalFlux1, 'f', 0)).arg(QString::number(totalFlux2, 'f', 0)));
        this->ui->channelVoltageLineEdit->setText(QString("%1 V / %2 V").arg(QString::number(totalVoltage1, 'f', 1)).arg(QString::number(totalVoltage2, 'f', 1)));
        this->ui->channelPowerLineEdit->setText(QString("%1 W / %2 W").arg(QString::number(totalPower1, 'f', 2)).arg(QString::number(totalPower2, 'f', 2)));
    }
}

void MainWindow::UpdateDualDriverLumi(int current1, int total1, int current2, int total2)
{
    if(module_1 != nullptr && module_2 != nullptr && driver != nullptr)
    {
        double LOR = this->ui->LOR_DoubleSpinBox->value();

        double totalPower1 = this->module_1->calc_power(current1) * total1;
        double efficiency1 = this->driver->calc_efficiency(totalPower1);
        double pfactor1 = this->driver->calc_powerfactor(totalPower1);
        double inputPower1 = totalPower1 / (efficiency1 / 100); // is also rated power

        double moduleFlux1 = this->module_1->calc_flux(current1);
        double totalFlux1 = moduleFlux1 * total1;
        double efficacy1 = (moduleFlux1 * LOR) / inputPower1;

        double totalPower2 = this->module_2->calc_power(current2) * total2;
        double efficiency2 = this->driver->calc_efficiency(totalPower2);
        double pfactor2 = this->driver->calc_powerfactor(totalPower2);
        double inputPower2 = totalPower2 / (efficiency2 / 100); // is also rated power

        double moduleFlux2 = this->module_2->calc_flux(current2);
        double totalFlux2 = moduleFlux2 * total2;
        double efficacy2 = (moduleFlux2 * LOR) / inputPower2;

        double tEfficiency = (efficiency1 < efficiency2) ? efficiency1 : efficiency2;
        double tPFactor = (pfactor1 < pfactor2) ? pfactor1 : pfactor2;
        double tOverallEfficacy = (efficacy1 < efficacy2) ? efficacy1 : efficacy2;

        this->ui->nominalPowerLineEdit->setText(QString("%1 W").arg(QString::number((totalPower1+totalPower2), 'f', 2)));
        this->ui->efficiencyLineEdit->setText(QString("%1\%").arg(QString::number(tEfficiency, 'f', 3))); // TO BE REVIEWED
        this->ui->powerFactorLineEdit->setText(QString("%1\%").arg(QString::number(tPFactor * 100, 'f', 3))); // TO BE REVIEWED
        this->ui->inputPowerLineEdit->setText(QString("%1 W").arg(QString::number((inputPower1+inputPower2), 'f', 2)));

        this->ui->nominalFluxLineEdit->setText(QString("%1 lm").arg(totalFlux1+totalFlux2));
        this->ui->effectiveFluxLineEdit->setText(QString("%1 lm").arg((moduleFlux1 + moduleFlux2) * LOR));
        this->ui->ratedPowerLineEdit->setText(QString("%1 W").arg(QString::number((inputPower1+inputPower2), 'f', 2)));
        this->ui->overallEfficacyLineEdit->setText(QString("%1").arg(tOverallEfficacy)); // TO BE REVIEWED
    }
}
