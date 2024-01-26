#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QPushButton>
#include <QSqlDatabase>

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
    void onStepChange(int val);
    ~MainWindow();

private slots:
    void on_moduleComboBox_1_currentIndexChanged(int index);

    void on_driverComboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    // MainModel mm;
    QSqlDatabase db;
};
#endif // MAINWINDOW_H
