#include <QApplication>

#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::UpdateDualMain(int input)
{
    int series = ui->n_seriesSpinBox_1->value();
    int parallel = ui->n_parallelSpinBox_1->value();
    int nTotal = series * parallel;
    int current = input / parallel;

    UpdateDualModule(current);
    UpdateDualChannels(current, series, parallel);
    UpdateDualDriverLumi(current, nTotal);
}

void MainWindow::UpdateDualModule(int current)
{
    if(module_1 != nullptr && module_2 != nullptr)
    {
        double moduleFlux1 = this->module_1->calc_flux(current);
        double moduleVoltage1 = this->module_1->calc_voltage(current);
        double modulePower1 = this->module_1->calc_power(current);

        double moduleFlux2 = this->module_2->calc_flux(current);
        double moduleVoltage2 = this->module_2->calc_voltage(current);
        double modulePower2 = this->module_2->calc_power(current);

        this->ui->moduleCurrentLineEdit->setText(QString("%1 mA").arg(current));
        this->ui->moduleFluxLineEdit->setText(QString("%1 lm / %2 lm").arg(QString::number(moduleFlux1, 'f', 0)).arg(QString::number(moduleFlux2, 'f', 0)));
        this->ui->moduleVoltageLineEdit->setText(QString("%1 V / %2 V").arg(QString::number(moduleVoltage1, 'f', 1)).arg(QString::number(moduleVoltage2, 'f', 1)));
        this->ui->modulePowerLineEdit->setText(QString("%1 W / %2 W").arg(QString::number(modulePower1, 'f', 2)).arg(QString::number(modulePower2, 'f', 2)));
    }
}

void MainWindow::UpdateDualChannels(int current, int series, int parallel)
{
    if(module_1 != nullptr && module_2 != nullptr)
    {
        double totalFlux1 = this->module_1->calc_flux(current) * series * parallel; // is also nominal flux
        double totalVoltage1 = this->module_1->calc_voltage(current) * series;
        double totalPower1 = this->module_1->calc_power(current) * series * parallel; // is also output power

        double totalFlux2 = this->module_2->calc_flux(current) * series * parallel; // is also nominal flux
        double totalVoltage2 = this->module_2->calc_voltage(current) * series;
        double totalPower2 = this->module_2->calc_power(current) * series * parallel; // is also output power

        this->ui->channelLayoutLineEdit->setText(QString("%1 P x %2 S").arg(parallel).arg(series));
        this->ui->numberOfModulesLineEdit->setText(QString("%1").arg(series * parallel));
        this->ui->channelFluxLineEdit->setText(QString("%1 lm / %2 lm").arg(QString::number(totalFlux1, 'f', 0)).arg(QString::number(totalFlux2, 'f', 0)));
        this->ui->channelVoltageLineEdit->setText(QString("%1 V / %2 V").arg(QString::number(totalVoltage1, 'f', 1)).arg(QString::number(totalVoltage2, 'f', 1)));
        this->ui->channelPowerLineEdit->setText(QString("%1 W / %2 W").arg(QString::number(totalPower1, 'f', 2)).arg(QString::number(totalPower2, 'f', 2)));
    }
}

void MainWindow::UpdateDualDriverLumi(int current, int total)
{
    if(module_1 != nullptr && module_2 != nullptr && driver != nullptr)
    {
        double LOR = this->ui->LOR_DoubleSpinBox->value();

        double totalPower1 = this->module_1->calc_power(current) * total;
        double efficiency1 = this->driver->calc_efficiency(totalPower1);
        double pfactor1 = this->driver->calc_powerfactor(totalPower1);
        double inputPower1 = totalPower1 / (efficiency1 / 100); // is also rated power

        double moduleFlux1 = this->module_1->calc_flux(current);
        double totalFlux1 = moduleFlux1 * total;
        double efficacy1 = (moduleFlux1 * LOR) / inputPower1;

        double totalPower2 = this->module_2->calc_power(current) * total;
        double efficiency2 = this->driver->calc_efficiency(totalPower2);
        double pfactor2 = this->driver->calc_powerfactor(totalPower2);
        double inputPower2 = totalPower2 / (efficiency2 / 100); // is also rated power

        double moduleFlux2 = this->module_2->calc_flux(current);
        double totalFlux2 = moduleFlux2 * total;
        double efficacy2 = (moduleFlux2 * LOR) / inputPower2;

        this->ui->nominalPowerLineEdit->setText(QString("%1 W / %2 W").arg(QString::number(totalPower1, 'f', 2)).arg(QString::number(totalPower2, 'f', 2)));
        this->ui->efficiencyLineEdit->setText(QString("%1\% / %2\%").arg(QString::number(efficiency1, 'f', 3)).arg(QString::number(efficiency2, 'f', 3)));
        this->ui->powerFactorLineEdit->setText(QString("%1\% / %2\%").arg(QString::number(pfactor1 * 100, 'f', 3)).arg(QString::number(pfactor2 * 100, 'f', 3)));
        this->ui->inputPowerLineEdit->setText(QString("%1 W / %2 W").arg(QString::number(inputPower1, 'f', 2)).arg(QString::number(inputPower2, 'f', 2)));

        this->ui->nominalFluxLineEdit->setText(QString("%1 lm / %2 lm").arg(totalFlux1).arg(totalFlux2));
        this->ui->effectiveFluxLineEdit->setText(QString("%1 lm / %2 lm").arg(moduleFlux1 * LOR).arg(moduleFlux2 * LOR));
        this->ui->ratedPowerLineEdit->setText(QString("%1 / %2").arg(inputPower1).arg(inputPower2));
        this->ui->overallEfficacyLineEdit->setText(QString("%1 / %2").arg(efficacy1).arg(efficacy2));
    }
}
