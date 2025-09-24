//TODO:
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tenant.h"
//Check if any of the cells for a "checked" tenant has a value of NULL.
bool MainWindow::validate_row(int row){
    for(int column = 0; column < 4; ++column){
        if(ui->ui_room_table->item(row, column) == NULL){
            qDebug() << "NULL cell at row " << row + 1 << "column" << column;
            return false;
        }
    }
    return true;
}
//Return the total consumption on the floor (sum of all tenants' consumptions).
int MainWindow::hallway_water_metric(){
    float sum = 0;
    for ( auto &curr : MainWindow::tenants) {
        sum += curr.get_tenant_water_metric();
    }
    return sum;
}
int MainWindow::hallway_electric_metric(){
    float sum = 0;
    for ( auto &curr : MainWindow::tenants) {
        sum += curr.electric_metric;
    }
    return sum;
}

//Fetch input information from the Qt Table Widget (tenants 1 - 10 info.) so that we can store it into program memory and later process it.
void MainWindow::fetch_tenants_table_info(){
    for(int row = 0; row < 10; ++row){
        if((MainWindow::ui->ui_room_table->item(row, 0)->checkState() == Qt::Checked) && MainWindow::validate_row(row)){
            int cold_water = MainWindow::ui->ui_room_table->item(row, 1)->text().toInt();
            int hot_water = MainWindow::ui->ui_room_table->item(row, 2)->text().toInt();
            int electric = MainWindow::ui->ui_room_table->item(row, 3)->text().toInt();
            MainWindow::tenants.push_back(Tenant(row+1, cold_water, hot_water, electric));
        }
    }
}
//Compute the sum of costs across all tenants.
//The "floor water/elec metric" is > "hallway water/elec metric", because "floor water/elec metric" = "hallway water/elec metric" + kitchen water/elec metric usage.
float MainWindow::tenants_shared_costs(){
    float water_shared_cost = (MainWindow::floor_water_metric - MainWindow::hallway_water_metric()) * MainWindow::water_rate;
    float electric_shared_cost = (MainWindow::floor_electric_metric - MainWindow::hallway_electric_metric()) * MainWindow::electric_rate;
    float gas_shared_cost = MainWindow::floor_gas_metric * MainWindow::gas_rate; //Rooms do not have any gas pipelines, hence no "hallway_gas_metric" (tenants only have access to gas in the kitches, which is a "floor cost")
    return water_shared_cost + electric_shared_cost + gas_shared_cost;
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ui_room_table->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
    ui->ui_room_table->resizeColumnsToContents();
    ui->ui_room_table->resizeRowsToContents();

    //--------inputs-----
    //Add checkbox in first column
    for (int row = 0; row < 10; ++row) {
        QTableWidgetItem *checkItem = new QTableWidgetItem();
        checkItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled); // must set flags
        checkItem->setCheckState(Qt::Unchecked); // default unchecked
        ui->ui_room_table->setItem(row, 0, checkItem);
    }
    //On "calculate" button click -> fetch room/tenant information from the QtTableWidget ("ui_room_table") and sotre it in program memory.
    connect(ui->ui_calculate, &QPushButton::clicked, this, [this](){
        MainWindow::tenants.clear();
        MainWindow::fetch_tenants_table_info();
    });
    //-----------

    //------outputs--------
    ui->ui_output_display->setReadOnly(true);
    connect(ui->ui_calculate, &QPushButton::clicked, this, [this](){
        ui->ui_output_display->clear();

        QString report;

        // ===== Floor Costs =====
        report += "<h4>FLOOR COSTS:</h4>";
        report += QString("Floor water cost: %1 RON<br>").arg(MainWindow::floor_water_metric * MainWindow::water_rate, 0, 'f', 2);
        report += QString("Floor electric cost: %1 RON<br>").arg(MainWindow::floor_electric_metric * MainWindow::electric_rate, 0, 'f', 2);
        report += QString("Floor gas cost: %1 RON<br><br>").arg(MainWindow::floor_gas_metric * MainWindow::gas_rate, 0, 'f', 2);

        // ===== Total FLoor Consumption =====
        report += "<h4>FLOOR CONSUMPTION:</h4>";
        report += QString("Hallway water consumption: %1 m³<br>").arg(MainWindow::hallway_water_metric());
        report += QString("Hallway electric consumption: %1 m³<br>").arg(MainWindow::hallway_electric_metric());

        // ===== Shared Costs =====
        report += "<h4>SHARED COSTS:</h4>";
        float shared_cost = MainWindow::tenants_shared_costs();
        float individual_cost = shared_cost / MainWindow::tenants.size();
        qDebug() << "ICG Total:" << MainWindow::total_icg;
        float individual_icg = MainWindow::total_icg / MainWindow::tenants.size();
        individual_cost += individual_icg;   //Include the shared icg cost.
        qDebug() << "ICG Individual:" << individual_icg;
        report += QString("Shared costs for tenants: %1 RON<br>").arg(shared_cost, 0 , 'f', 2);
        report += QString("Individual tenant share: %1 RON<br><br>").arg(individual_cost, 0, 'f', 2);

        // ===== Individual Tenant Costs =====
        report += "<h3>INDIVIDUAL TENANT COSTS:</h3>";
        for (auto& tenant : MainWindow::tenants) {
            report += QString("Tenant %1: %2 RON<br>")
            .arg(tenant.id)
                .arg(tenant.get_my_cost(ui->ui_water_rate->text().toFloat(), ui->ui_electric_rate->text().toFloat()) + individual_cost, 0, 'f', 2);
        }

        // Display with HTML formatting
        ui->ui_output_display->setHtml(report);

    });


    //Store icg input
    connect(ui->ui_icg, &QLineEdit::editingFinished, this, [this]() {
        bool ok;
        float value = ui->ui_icg->text().toInt(&ok);
        if (ok) {
            MainWindow::total_icg = value;
            qDebug() << "icg updated to:" << MainWindow::total_icg;
        } else {
            qDebug() << "Invalid number entered!";
        }
    });
    //Store water rate input
    connect(ui->ui_water_rate, &QLineEdit::editingFinished, this, [this]() {
        bool ok;
        float value = ui->ui_water_rate->text().toFloat(&ok);
        if (ok) {
            MainWindow::water_rate = value;
            qDebug() << "Water rate updated to:" << MainWindow::water_rate;
        } else {
            qDebug() << "Invalid number entered!";
        }
    });
    //Store electric rate input
    connect(ui->ui_electric_rate, &QLineEdit::editingFinished, this, [this]() {
        bool ok;
        float value = ui->ui_electric_rate->text().toFloat(&ok);
        if (ok) {
            MainWindow::electric_rate = value;
        } else {
            qDebug() << "Invalid number entered!";
        }
    });
    //Store gas rate input
    connect(ui->ui_gas_rate, &QLineEdit::editingFinished, this, [this]() {
        bool ok;
        float value = ui->ui_gas_rate->text().toFloat(&ok);
        if (ok) {
            MainWindow::gas_rate = value;
        } else {
            qDebug() << "Invalid number entered!";
        }
    });

    //Store water metric input
    connect(ui->ui_floor_water_metric, &QLineEdit::editingFinished, this, [this]() {
        bool ok;
        float value = ui->ui_floor_water_metric->text().toFloat(&ok);
        if (ok) {
            MainWindow::floor_water_metric = value;
            qDebug() << "Water metric updated to:" << MainWindow::floor_water_metric;
        } else {
            qDebug() << "Invalid number entered!";
        }
    });
    //Store electric metric input
    connect(ui->ui_floor_electric_metric, &QLineEdit::editingFinished, this, [this]() {
        bool ok;
        float value = ui->ui_floor_electric_metric->text().toFloat(&ok);
        if (ok) {
            MainWindow::floor_electric_metric = value;
        } else {
            qDebug() << "Invalid number entered!";
        }
    });
    //Store gas metric input
    connect(ui->ui_floor_gas_metric, &QLineEdit::editingFinished, this, [this]() {
        bool ok;
        float value = ui->ui_floor_gas_metric->text().toFloat(&ok);
        if (ok) {
            MainWindow::floor_gas_metric= value;
        } else {
            qDebug() << "Invalid number entered!";
        }
    });

    //--------------------------------------------Database Implementation----------------------
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Users/ferna/OneDrive/Desktop/Browser/myBrowser/database.db");
    if(mydb.open()){
        qDebug() << "Database is OPEN!";
    }else{
        qDebug() << "Failed to open Database";
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
