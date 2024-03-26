#include <QApplication>
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::UpdateSingle(int current, LED_Module *mod)
{
    if(mod != nullptr)
    {
        mod->modCurrent = current;
        mod->modFlux = mod->calc_flux(current);
        mod->modVoltage = mod->calc_voltage(current);
        mod->modPower = mod->calc_power(current);

        mod->totalFlux = mod->calc_flux(current) * mod->series * mod->parallel; // is also nominal flux
        mod->totalVoltage = mod->calc_voltage(current) * mod->series;
        mod->totalPower = mod->calc_power(current) * mod->series * mod->parallel; // is also output power

        mod->totalPower = mod->calc_power(current) * mod->series * mod->parallel;
        mod->modFlux = mod->calc_flux(current);
        mod->totalFlux = mod->modFlux * mod->series * mod->parallel;

        if(driver != nullptr)
        {
            driver->efficiency = this->driver->calc_efficiency(mod->totalPower);
            driver->powerFactor = this->driver->calc_powerfactor(mod->totalPower);
            driver->LOR = this->ui->LOR_DoubleSpinBox->value();
            driver->efficacy = (mod->modFlux * driver->LOR) / mod->inputPower;
            mod->inputPower = mod->totalPower / (driver->efficiency / 100); // is also rated power
        }
    }
}

void MainWindow::UpdatePage()
{
    if(ModuleTwoActive())
    {
        if((module_1 != nullptr) && (module_2 != nullptr))
        {
            this->UpdateSingle(this->ui->spinBox->value(), module_1);
            this->UpdateSingle(this->ui->spinBox->value(), module_2);

            this->ui->moduleCurrentLineEdit->setText(QString("%1 mA / %2 mA").arg(module_1->modCurrent).arg(module_2->modCurrent));
            this->ui->moduleFluxLineEdit->setText(QString("%1 lm / %2 lm").arg(QString::number(module_1->modFlux, 'f', 2)).arg(QString::number(module_2->modFlux, 'f', 2)));
            this->ui->moduleVoltageLineEdit->setText(QString("%1 V / %2 V").arg(QString::number(module_1->modVoltage, 'f', 1)).arg(QString::number(module_2->modVoltage, 'f', 1)));
            this->ui->modulePowerLineEdit->setText(QString("%1 W / %2 W").arg(QString::number(module_1->modPower, 'f', 2)).arg(QString::number(module_2->modPower, 'f', 2)));

            this->ui->channelLayoutLineEdit->setText(QString("%1 P x %2 S / %3 P x %4 S").arg(module_1->parallel).arg(module_1->series).arg(module_2->parallel).arg(module_2->series));
            this->ui->numberOfModulesLineEdit->setText(QString("%1").arg((module_1->series * module_1->parallel) + (module_2->series * module_2->parallel)));
            this->ui->channelFluxLineEdit->setText(QString("%1 lm / %2 lm").arg(QString::number(module_1->totalFlux, 'f', 0)).arg(QString::number(module_2->totalFlux, 'f', 0)));
            this->ui->channelVoltageLineEdit->setText(QString("%1 V / %2 V").arg(QString::number(module_1->totalVoltage, 'f', 1)).arg(QString::number(module_2->totalVoltage, 'f', 1)));
            this->ui->channelPowerLineEdit->setText(QString("%1 W / %2 W").arg(QString::number(module_1->totalPower, 'f', 2)).arg(QString::number(module_2->totalPower, 'f', 2)));

            this->ui->nominalPowerLineEdit->setText(QString("%1 W").arg(QString::number((module_1->totalPower + module_2->totalPower), 'f', 2)));
            this->ui->inputPowerLineEdit->setText(QString("%1 W").arg(QString::number((module_1->inputPower + module_2->inputPower), 'f', 2)));
            this->ui->nominalFluxLineEdit->setText(QString("%1 lm").arg(QString::number((module_1->totalFlux + module_2->totalFlux), 'f', 2)));
            this->ui->ratedPowerLineEdit->setText(QString("%1 W").arg(QString::number((module_1->inputPower + module_2->inputPower), 'f', 2)));


            if(driver != nullptr)
            {
                this->ui->efficiencyLineEdit->setText(QString("%1\%").arg(QString::number(driver->efficiency, 'f', 3))); // TO BE REVIEWED
                this->ui->powerFactorLineEdit->setText(QString("%1\%").arg(QString::number(driver->powerFactor * 100, 'f', 3))); // TO BE REVIEWED
                this->ui->overallEfficacyLineEdit->setText(QString("%1 lm/W").arg(driver->efficacy)); // TO BE REVIEWED
                this->ui->effectiveFluxLineEdit->setText(QString("%1 lm").arg(QString::number((module_1->modFlux + module_2->modFlux) * driver->LOR, 'f', 2)));
            }
        }
    } else
    {
        if(module_1 != nullptr)
        {
            this->UpdateSingle(this->ui->spinBox->value(), module_1);

            this->ui->moduleCurrentLineEdit->setText(QString("%1 mA").arg(module_1->modCurrent));
            this->ui->moduleFluxLineEdit->setText(QString("%1 lm").arg(QString::number(module_1->modFlux, 'f', 2)));
            this->ui->moduleVoltageLineEdit->setText(QString("%1 V").arg(QString::number(module_1->modVoltage, 'f', 1)));
            this->ui->modulePowerLineEdit->setText(QString("%1 W").arg(QString::number(module_1->modPower, 'f', 2)));

            this->ui->channelLayoutLineEdit->setText(QString("%1 P x %2 S").arg(module_1->parallel).arg(module_1->series));
            this->ui->numberOfModulesLineEdit->setText(QString("%1").arg(module_1->series * module_1->parallel));
            this->ui->channelFluxLineEdit->setText(QString("%1 lm").arg(QString::number(module_1->totalFlux, 'f', 0)));
            this->ui->channelVoltageLineEdit->setText(QString("%1 V").arg(QString::number(module_1->totalVoltage, 'f', 1)));
            this->ui->channelPowerLineEdit->setText(QString("%1 W").arg(QString::number(module_1->totalPower, 'f', 2)));

            this->ui->nominalPowerLineEdit->setText(QString("%1 W").arg(QString::number(module_1->totalPower, 'f', 2)));
            this->ui->inputPowerLineEdit->setText(QString("%1 W").arg(QString::number(module_1->inputPower, 'f', 2)));
            this->ui->nominalFluxLineEdit->setText(QString("%1 lm").arg(QString::number(module_1->totalFlux, 'f', 2)));
            this->ui->ratedPowerLineEdit->setText(QString("%1 W").arg(QString::number(module_1->inputPower, 'f', 2)));

            if(driver != nullptr)
            {
                this->ui->efficiencyLineEdit->setText(QString("%1\%").arg(QString::number(driver->efficiency, 'f', 3)));
                this->ui->powerFactorLineEdit->setText(QString("%1\%").arg(QString::number(driver->powerFactor * 100, 'f', 3)));
                this->ui->overallEfficacyLineEdit->setText(QString("%1 lm/W").arg(driver->efficacy));
                this->ui->effectiveFluxLineEdit->setText(QString("%1 lm").arg(QString::number((module_1->modFlux * driver->LOR), 'f', 2)));
            }
        }
    }
}
