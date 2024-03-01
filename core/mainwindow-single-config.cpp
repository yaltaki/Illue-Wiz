#include <QApplication>

#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::UpdateMain(int input)
{
    int series = ui->n_seriesSpinBox_1->value();
    int parallel = ui->n_parallelSpinBox_1->value();
    int nTotal = series * parallel;
    int current = input / parallel;

    UpdateModule(current);
    UpdateChannels(current, series, parallel);
    UpdateDriverLumi(current, nTotal);
}

void MainWindow::UpdateModule(int current)
{
    if(module_1 != nullptr)
    {
        double moduleFlux = this->module_1->calc_flux(current);
        double moduleVoltage = this->module_1->calc_voltage(current);
        double modulePower = this->module_1->calc_power(current);

        this->ui->moduleCurrentLineEdit->setText(QString("%1 mA").arg(current));
        this->ui->moduleFluxLineEdit->setText(QString("%1 lm").arg(QString::number(moduleFlux, 'f', 0)));
        this->ui->moduleVoltageLineEdit->setText(QString("%1 V").arg(QString::number(moduleVoltage, 'f', 1)));
        this->ui->modulePowerLineEdit->setText(QString("%1 W").arg(QString::number(modulePower, 'f', 2)));
    }
}

void MainWindow::UpdateChannels(int current, int series, int parallel)
{
    if(module_1 != nullptr)
    {
        double totalFlux = this->module_1->calc_flux(current) * series * parallel; // is also nominal flux
        double totalVoltage = this->module_1->calc_voltage(current) * series;
        double totalPower = this->module_1->calc_power(current) * series * parallel; // is also output power

        this->ui->channelLayoutLineEdit->setText(QString("%1 P x %2 S").arg(parallel).arg(series));
        this->ui->numberOfModulesLineEdit->setText(QString("%1").arg(series * parallel));
        this->ui->channelFluxLineEdit->setText(QString("%1 lm").arg(QString::number(totalFlux, 'f', 0)));
        this->ui->channelVoltageLineEdit->setText(QString("%1 V").arg(QString::number(totalVoltage, 'f', 1)));
        this->ui->channelPowerLineEdit->setText(QString("%1 W").arg(QString::number(totalPower, 'f', 2)));
    }
}

void MainWindow::UpdateDriverLumi(int current, int total)
{
    if(module_1 != nullptr && driver != nullptr)
    {
        double totalPower = this->module_1->calc_power(current) * total;
        double efficiency = this->driver->calc_efficiency(totalPower);
        double pfactor = this->driver->calc_powerfactor(totalPower);
        double inputPower = totalPower / (efficiency / 100); // is also rated power

        double moduleFlux = this->module_1->calc_flux(current);
        double totalFlux = moduleFlux * total;
        double LOR = this->ui->LOR_DoubleSpinBox->value();
        double efficacy = (moduleFlux * LOR) / inputPower;

        this->ui->nominalPowerLineEdit->setText(QString("%1 W").arg(QString::number(totalPower, 'f', 2)));
        this->ui->efficiencyLineEdit->setText(QString("%1\%").arg(QString::number(efficiency, 'f', 3)));
        this->ui->powerFactorLineEdit->setText(QString("%1\%").arg(QString::number(pfactor * 100, 'f', 3)));
        this->ui->inputPowerLineEdit->setText(QString("%1 W").arg(QString::number(inputPower, 'f', 2)));

        this->ui->nominalFluxLineEdit->setText(QString("%1 lm").arg(totalFlux));
        this->ui->effectiveFluxLineEdit->setText(QString("%1 lm").arg(moduleFlux * LOR));
        this->ui->ratedPowerLineEdit->setText(QString("%1").arg(inputPower));
        this->ui->overallEfficacyLineEdit->setText(QString("%1").arg(efficacy));
    }
}
