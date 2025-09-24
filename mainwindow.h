#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tenant.h"
#include "ui_mainwindow.h"
//SQLite implementation.
#include <QtSql>
#include <QDebug>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //Rates & metrics are initialized in this header file in order to keep track of them for the whole instance of the program.
    float total_icg = 400;
    float water_rate =0.0;
    float gas_rate = 0.0;
    float electric_rate = 0.0;
    int floor_water_metric =0;
    int floor_electric_metric = 0;
    int floor_gas_metric = 0;
    //Keep track of tenants
    std::vector<Tenant> tenants;
    //Getters for each of the utility types(water, gas, and electric) on the whole floor.
    float water_floor_cost(){
        return this->floor_water_metric * this->water_rate;
    }
    float gas_floor_cost (){
        return this->floor_gas_metric * this->gas_rate;
    }
    float electric_floor_cost (){
        return this->floor_electric_metric * electric_rate;
    }


private:
    Ui::MainWindow *ui;
    //validate user input for the tenant cells
    bool validate_row(int);
    int hallway_water_metric();
    int hallway_electric_metric();
    float tenants_shared_costs();
    void fetch_tenants_table_info();

};
#endif // MAINWINDOW_H
