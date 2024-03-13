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
    int StepCount = ceil((MaxCurrent - MinCurrent) / StepCurrent);

    // for(int i = MinCurrent; i < MaxCurrent; i += StepCurrent)
    // {
    //     qDebug() << "The current step is" << i;
    //     if(StepCurrent >= (MaxCurrent - i))
    //     {
    //         qDebug() << "This final step is" << MaxCurrent;
    //     }
    // }

    if(table != nullptr)
    {
        table->setColumnCount(7);
        table->setRowCount(StepCount);


        for(int i = 0; i < StepCount; i++)
        {
            int CurrentStep = MinCurrent + (StepCurrent * i);
            UpdateValuesForRow(i, CurrentStep);
            if(++i == StepCount)
            {
                UpdateValuesForRow(StepCount, MaxCurrent);
                break;
            }
        }
    }
}

void MainWindow::UpdateValuesForRow(int Step, int Value)
{
    if(table != nullptr)
    {
        double ModFlux = module_1->calc_flux(Value);
        double Voltage = module_1->calc_voltage(Value);
        double NomPower = module_1->calc_power(Value);
        double NomFlux = ModFlux * ui->n_seriesSpinBox_1->value() * ui->n_parallelSpinBox_1->value();
        double Efficiency = module_1->calc_efficiency(Value);
        double EffPower = NomPower / Efficiency;
        double EffFlux = NomFlux / Efficiency;
        double SysEff = (ModFlux * ui->LOR_DoubleSpinBox->value()) / EffPower;

        table->item(Step, 0)->setData(Qt::DisplayRole, ModFlux);
        table->item(Step, 1)->setData(Qt::DisplayRole, Voltage);
        table->item(Step, 2)->setData(Qt::DisplayRole, NomPower);
        table->item(Step, 3)->setData(Qt::DisplayRole, NomFlux);
        table->item(Step, 4)->setData(Qt::DisplayRole, EffPower);
        table->item(Step, 5)->setData(Qt::DisplayRole, EffFlux);
        table->item(Step, 6)->setData(Qt::DisplayRole, SysEff);
    }
}
