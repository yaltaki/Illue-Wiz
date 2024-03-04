#include "mainwindow.h"
#include "QColor"
#include "ui_mainwindow.h"

void MainWindow::checkColourI(unsigned value, unsigned threshold_low, unsigned threshold_high, QLineEdit *field)
{
    if(value < threshold_low)
    {
        field->setStyleSheet("color: orange");
    } else if (value > threshold_high)
    {
        field->setStyleSheet("color: red");
    } else
    {
        field->setStyleSheet("color: black");
    }
}

void MainWindow::checkColourD(double value, double threshold_low, double threshold_high, QLineEdit *field)
{
    if(value < threshold_low)
    {
        field->setStyleSheet("color: orange");
    } else if (value > threshold_high)
    {
        field->setStyleSheet("color: red");
    } else
    {
        field->setStyleSheet("color: black");
    }
}
