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
    std::vector<Tenant> tenants;//These metrics are currently (this month) consumptions.
    std::vector<Tenant> archive_tenants;//These metrics are absolute values
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
    void store_tenants_table_info();
    QSqlDatabase mydb;
    void create_month_table(); //Setup database table
    void create_tenant_table(); //Setup db table
    void archive_month(); //Save state to database
    void archive_tenant(int id, int water_cold_metric, int water_hot_metric, int electric_metric);//Save this (1) tenant to the tenants db table. (this function gets called foreach tenant).
    float getLastMonthMetric(const QString &metricType); // Fetch last month's water/gas/electric metric from the database
    int getLastMonthTenantMetric(int tenantId, const QString &metricType);
};
#endif // MAINWINDOW_H
