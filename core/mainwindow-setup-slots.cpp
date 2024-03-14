#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_moduleComboBox_1_currentIndexChanged(int index)
{
    this->IndexChangeModule_1(index);
    this->updateLimits();
    if(ModuleTwoActive())
        this->UpdateDualMain(ui->horizontalSlider->value());
    else
        this->UpdateMain(ui->horizontalSlider->value());
}

void MainWindow::on_moduleComboBox_2_currentIndexChanged(int index)
{
    this->IndexChangeModule_2(index);
    this->updateLimits();
    if(ModuleTwoActive())
        this->UpdateDualMain(ui->horizontalSlider->value());
    else
        this->UpdateMain(ui->horizontalSlider->value());
}

void MainWindow::on_driverComboBox_currentIndexChanged(int index)
{
    this->IndexChangeDriver(index);
    this->updateLimits();
    if(ModuleTwoActive())
        this->UpdateDualMain(ui->horizontalSlider->value());
    else
        this->UpdateMain(ui->horizontalSlider->value());
}

void MainWindow::on_n_seriesSpinBox_1_valueChanged(int arg1)
{
    this->IndexChangeModule_1(ui->moduleComboBox_1->currentIndex());
    this->updateLimits();
    if(ModuleTwoActive())
        this->UpdateDualMain(ui->horizontalSlider->value());
    else
        this->UpdateMain(ui->horizontalSlider->value());
}

void MainWindow::on_n_parallelSpinBox_1_valueChanged(int arg1)
{
    this->IndexChangeModule_1(ui->moduleComboBox_1->currentIndex());
    this->updateLimits();
    if(ModuleTwoActive())
        this->UpdateDualMain(ui->horizontalSlider->value());
    else
        this->UpdateMain(ui->horizontalSlider->value());
}

void MainWindow::on_n_seriesSpinBox_2_valueChanged(int arg1)
{
    this->IndexChangeModule_2(ui->moduleComboBox_2->currentIndex());
    this->updateLimits();
    if(ModuleTwoActive())
        this->UpdateDualMain(ui->horizontalSlider->value());
    else
        this->UpdateMain(ui->horizontalSlider->value());
}

void MainWindow::on_n_parallelSpinBox_2_valueChanged(int arg1)
{
    this->IndexChangeModule_2(ui->moduleComboBox_2->currentIndex());
    this->updateLimits();
    if(ModuleTwoActive())
        this->UpdateDualMain(ui->horizontalSlider->value());
    else
        this->UpdateMain(ui->horizontalSlider->value());
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->spinBox->setValue(value);
    if(ModuleTwoActive())
        this->UpdateDualMain(value);
    else
        this->UpdateMain(value);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->horizontalSlider->setValue(arg1);
    if(ModuleTwoActive())
        this->UpdateDualMain(arg1);
    else
        this->UpdateMain(arg1);
}

void MainWindow::on_moduleGroupBox_2_clicked(bool checked)
{
    this->updateLimits();
    if(ModuleTwoActive())
        this->UpdateDualMain(ui->horizontalSlider->value());
    else
        this->UpdateMain(ui->horizontalSlider->value());
}

void MainWindow::on_checkBox_Copy_clicked(bool checked)
{
    this->updateLimits();
    if(ModuleTwoActive())
        this->UpdateDualMain(ui->horizontalSlider->value());
    else
        this->UpdateMain(ui->horizontalSlider->value());
}

void MainWindow::on_btn_steps_25_clicked()
{
    this->ui->stepsSpinBox->setValue(this->ui->stepsSpinBox->value()+25);
}

void MainWindow::on_btn_steps_50_clicked()
{
    this->ui->stepsSpinBox->setValue(this->ui->stepsSpinBox->value()+50);
}

void MainWindow::on_btn_steps_100_clicked()
{
    this->ui->stepsSpinBox->setValue(this->ui->stepsSpinBox->value()+100);
}

void MainWindow::on_btn_steps_200_clicked()
{
    this->ui->stepsSpinBox->setValue(this->ui->stepsSpinBox->value()+200);
}
