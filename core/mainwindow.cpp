#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
    module_1{nullptr}, module_2{nullptr}, driver{nullptr}
{
    ui->setupUi(this);
    this->connectToDatabase();
    this->setComboBoxModel();

    this->updateLimits();
    this->UpdateMain(100);
}

MainWindow::~MainWindow()
{
    delete ui;
    // delete luminaire;
    delete module_1;
    delete module_2;
    delete driver;
}

bool MainWindow::ModuleTwoActive()
{
    return (!(module_2 == nullptr) && (ui->moduleGroupBox_2->isChecked()) && !(ui->checkBox_Copy->isChecked()));
}

// void MainWindow::onStepChange(int val) const { this->ui->stepsSpinBox->setValue(val); }

