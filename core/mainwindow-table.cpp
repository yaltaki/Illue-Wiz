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

    for(int i = MinCurrent; i < MaxCurrent; i += StepCurrent)
    {
        qDebug() << "The current step is" << i;
        if(StepCurrent >= (MaxCurrent - i))
        {
            qDebug() << "This final step is" << MaxCurrent;
        }
    }
}
