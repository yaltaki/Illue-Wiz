#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>

#include "mainmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // void testFunction();

    void on_btn_steps_25_clicked();

    void on_btn_steps_50_clicked();

    void on_btn_steps_100_clicked();

    void on_btn_steps_200_clicked();

    // void on_moduleComboBox_1_currentIndexChanged(int index);

    // void on_calc_clicked();

private:
    Ui::MainWindow *ui;
    MainModel mm;
};
#endif // MAINWINDOW_H
