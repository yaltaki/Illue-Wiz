#include "mainwindow.h"
#include "QColor"
#include "ui_mainwindow.h"

void MainWindow::checkColourI(unsigned value, QLineEdit *field, bool ModOrDriver)
{
    if(ModOrDriver && (module_1 != nullptr))
    {
        unsigned th_low1 = module_1->get_If_min();
        unsigned th_high1 = module_1->get_If_max();
        if(value < th_low1)
        {
            field->setStyleSheet("color: orange");
        } else if(value > th_high1)
        {
            field->setStyleSheet("color: red");
        } else
        {
            field->setStyleSheet("color: black");
        }
    } else if(driver != nullptr)
    {
        unsigned th_lowd = driver->get_If_min();
        unsigned th_highd = driver->get_If_max();
        if(value < th_lowd)
        {
            field->setStyleSheet("color: orange");
        } else if(value > th_highd)
        {
            field->setStyleSheet("color: red");
        } else
        {
            field->setStyleSheet("color: black");
        }
    }
}

void MainWindow::checkColourI_D(unsigned value1, unsigned value2, QLineEdit *field, bool ModOrDriver)
{
    if(ModOrDriver && (module_1 != nullptr))
    {
        unsigned th_low1 = module_1->get_If_min();
        unsigned th_high1 = module_1->get_If_max();
        if(ModuleTwoActive() && (module_2 != nullptr))
        {
            unsigned th_low2 = module_2->get_If_min();
            unsigned th_high2 = module_2->get_If_max();
            if((value1 < th_low1) || (value2 < th_low2))
            {
                field->setStyleSheet("color: orange");
            } else if((value1 > th_high1) || (value2 > th_high2))
            {
                field->setStyleSheet("color: red");
            } else
            {
                field->setStyleSheet("color: black");
            }
        } else
        {
            if(value1 < th_low1)
            {
                field->setStyleSheet("color: orange");
            } else if(value1 > th_high1)
            {
                field->setStyleSheet("color: red");
            } else
            {
                field->setStyleSheet("color: black");
            }
        }
    } else if(driver != nullptr)
    {
        unsigned th_lowd = driver->get_If_min();
        unsigned th_highd = driver->get_If_max();
        if(value1 < th_lowd)
        {
            field->setStyleSheet("color: orange");
        } else if(value1 > th_highd)
        {
            field->setStyleSheet("color: red");
        } else
        {
            field->setStyleSheet("color: black");
        }
    }
}

void MainWindow::checkColourV(double value, QLineEdit *field, bool ModOrDriver)
{
    if(ModOrDriver && (module_1 != nullptr))
    {
        double th_low1 = module_1->get_V_min();
        double th_high1 = module_1->get_V_max();
        if(ModuleTwoActive() && (module_2 != nullptr))
        {
            double th_low2 = module_2->get_V_min();
            double th_high2 = module_2->get_V_max();
            if((value < th_low1) || (value < th_low2))
            {
                field->setStyleSheet("color: orange");
            } else if((value > th_high1) || (value > th_high2))
            {
                field->setStyleSheet("color: red");
            } else
            {
                field->setStyleSheet("color: black");
            }
        } else
        {
            if(value < th_low1)
            {
                field->setStyleSheet("color: orange");
            } else if (value > th_high1)
            {
                field->setStyleSheet("color: red");
            } else
            {
                field->setStyleSheet("color: black");
            }
        }
    } else if(driver != nullptr)
    {
        double th_lowd = driver->get_V_min();
        double th_highd = driver->get_V_max();
        if(value < th_lowd)
        {
            field->setStyleSheet("color: orange");
        } else if(value > th_highd)
        {
            field->setStyleSheet("color: red");
        } else
        {
            field->setStyleSheet("color: black");
        }
    }
}

void MainWindow::checkColourP(double value, QLineEdit *field, bool ModOrDriver)
{
    if(ModOrDriver && (module_1 != nullptr))
    {
        double th_low1 = module_1->get_V_min() * module_1->get_If_min() / 1000;
        double th_high1 = module_1->get_V_max() * module_1->get_If_max() / 1000;
        if(ModuleTwoActive() && (module_2 != nullptr))
        {
            double th_low2 = module_2->get_V_min() * module_2->get_If_min() / 1000;
            double th_high2 = module_2->get_V_max() * module_2->get_If_max() / 1000;
            if((value < th_low1) || (value < th_low2))
            {
                field->setStyleSheet("color: orange");
            } else if((value > th_high1) || (value > th_high2))
            {
                field->setStyleSheet("color: red");
            } else
            {
                field->setStyleSheet("color: black");
            }
        } else
        {
            if(value < th_low1)
            {
                field->setStyleSheet("color: orange");
            } else if(value > th_high1)
            {
                field->setStyleSheet("color: red");
            } else
            {
                field->setStyleSheet("color: black");
            }
        }
    } else if(driver != nullptr)
    {
        double th_lowd = driver->get_V_min() * driver->get_If_min() / 1000;
        double th_highd = driver->get_P_1();
        if(driver->get_Dual())
        {
            // double th_lowd2 = driver->get_V_min() * driver->get_If_min() / 1000; seemingly unneeded for now
            double th_highd2 = driver->get_P_2();
            if(value < th_lowd)
            {
                field->setStyleSheet("color: orange");
            } else if ((value > th_highd) || (value > th_highd2))
            {
                field->setStyleSheet("color: red");
            } else
            {
                field->setStyleSheet("color: black");
            }
        } else
        {
            if(value < th_lowd)
            {
                field->setStyleSheet("color: orange");
            } else if(value > th_highd)
            {
                field->setStyleSheet("color: red");
            } else
            {
                field->setStyleSheet("color: black");
            }
        }
    }
}

void MainWindow::checkColourE(double value, QLineEdit *field)
{
    double th_lowe = 50;
    double th_highe = 100;
    if(value < th_lowe)
    {
        field->setStyleSheet("color: orange");
    } else if(value > th_highe)
    {
        field->setStyleSheet("color: red");
    } else
    {
        field->setStyleSheet("color: black");
    }
}

void MainWindow::ModuleColour(unsigned current, double moduleVoltage, double modulePower)
{
    checkColourI(current, ui->moduleCurrentLineEdit, true);
    checkColourV(moduleVoltage, ui->moduleVoltageLineEdit, true);
    checkColourP(modulePower, ui->modulePowerLineEdit, true);
}

void MainWindow::ChannelsColour(double totalVoltage, double totalPower)
{
    checkColourV(totalVoltage, ui->channelVoltageLineEdit, false);
    checkColourP(totalPower, ui->channelPowerLineEdit, false);
}

void MainWindow::DriverLumiColour(double totalPower, double efficiency, double inputPower)
{
    checkColourP(totalPower, ui->nominalPowerLineEdit, false);
    checkColourE(efficiency, ui->efficiencyLineEdit);
    checkColourP(inputPower, ui->inputPowerLineEdit, false);
    checkColourP(inputPower, ui->ratedPowerLineEdit, false);
}
