#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_stepsSpinBox_valueChanged(int arg1)
{
    this->TableUpdate(arg1);
}

void MainWindow::TableUpdate(int current)
{
    int MinCurrent = module_1->get_If_min();
    int MaxCurrent = module_1->get_If_max();
    int StepCurrent = current;
    int StepCount = ((MaxCurrent - MinCurrent) / StepCurrent) + 1;

    // for(int i = MinCurrent; i < MaxCurrent; i += StepCurrent)
    // {
    //     qDebug() << "The current step is" << i;
    //     if(StepCurrent >= (MaxCurrent - i))
    //     {
    //         qDebug() << "This final step is" << MaxCurrent;
    //     }
    // }

    if(ui->tableWidget != nullptr)
    {
        ui->tableWidget->setColumnCount(7);
        ui->tableWidget->setRowCount(StepCount+1);

        for(int i = 0; i < StepCount; i++)
        {
            int CurrentStep = MinCurrent + (StepCurrent * i);
            UpdateValuesForRow(i, CurrentStep);
            if(i == StepCount-1)
            {
                UpdateValuesForRow(StepCount, MaxCurrent);
                break;
            }
        }
    }
}

void MainWindow::UpdateValuesForRow(int Step, int Value)
{
    if(ui->tableWidget != nullptr)
    {
        double ModFlux = module_1->calc_flux(Value);
        double Voltage = module_1->calc_voltage(Value);
        double NomPower = module_1->calc_power(Value);
        double NomFlux = ModFlux * ui->n_seriesSpinBox_1->value() * ui->n_parallelSpinBox_1->value();
        double Efficiency = driver->calc_efficiency(NomPower);
        double EffPower = NomPower / Efficiency * 100;
        double EffFlux = NomFlux * ui->LOR_DoubleSpinBox->value();
        double SysEff = (ModFlux * ui->LOR_DoubleSpinBox->value()) / EffPower;

        QTableWidgetItem *item0 = new QTableWidgetItem(tr("%1 lm").arg(QString::number(ModFlux, 'f', 2)));
        QTableWidgetItem *item1 = new QTableWidgetItem(tr("%1 V").arg(QString::number(Voltage, 'f', 2)));
        QTableWidgetItem *item2 = new QTableWidgetItem(tr("%1 W").arg(QString::number(NomPower, 'f', 2)));
        QTableWidgetItem *item3 = new QTableWidgetItem(tr("%1 lm").arg(QString::number(NomFlux, 'f', 2)));
        QTableWidgetItem *item4 = new QTableWidgetItem(tr("%1 W").arg(QString::number(EffPower, 'f', 2)));
        QTableWidgetItem *item5 = new QTableWidgetItem(tr("%1 lm").arg(QString::number(EffFlux, 'f', 2)));
        QTableWidgetItem *item6 = new QTableWidgetItem(tr("%1 lm/W").arg(QString::number(SysEff, 'f', 2)));

        QTableWidgetItem *row = new QTableWidgetItem(tr("%1 mA").arg(Value));
        ui->tableWidget->setVerticalHeaderItem(Step, row);

        ui->tableWidget->setItem(Step, 0, item0);
        ui->tableWidget->setItem(Step, 1, item1);
        ui->tableWidget->setItem(Step, 2, item2);
        ui->tableWidget->setItem(Step, 3, item3);
        ui->tableWidget->setItem(Step, 4, item4);
        ui->tableWidget->setItem(Step, 5, item5);
        ui->tableWidget->setItem(Step, 6, item6);

        qDebug() << Efficiency;
    }
}
