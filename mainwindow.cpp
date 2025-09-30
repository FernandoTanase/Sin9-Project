//TODO: - Add the functionality of selecting a FLOOR 1/2. (In the very beginning of the program!; disable all functionalaity until floor # is selected).
//      - Use different DB or different tables?
// RESUME: line 223 & 213

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
void MainWindow::store_tenants_table_info(){
    for(int row = 0; row < 10; ++row){
        if((MainWindow::ui->ui_room_table->item(row, 0)->checkState() == Qt::Checked) && MainWindow::validate_row(row)){
            int last_month_water_cold_metric = MainWindow::getLastMonthTenantMetric(row+1,"water_cold_metric");
            int last_month_water_hot_metric = MainWindow::getLastMonthTenantMetric(row+1,"water_hot_metric");
            int last_month_electric_metric = MainWindow::getLastMonthTenantMetric(row+1,"electric_metric");

            int curr_water_cold_metric = MainWindow::ui->ui_room_table->item(row, 1)->text().toInt();
            int curr_water_hot_metric = MainWindow::ui->ui_room_table->item(row, 2)->text().toInt();
            int curr_electric_metric = MainWindow::ui->ui_room_table->item(row, 3)->text().toInt();
            MainWindow::archive_tenants.push_back(Tenant(row+1, curr_water_cold_metric, curr_water_hot_metric, curr_electric_metric));

            int used_cold_water = curr_water_cold_metric - last_month_water_cold_metric;
            int used_hot_water = curr_water_hot_metric - last_month_water_hot_metric;
            int used_electric = curr_electric_metric - last_month_electric_metric;
            MainWindow::tenants.push_back(Tenant(row+1, used_cold_water, used_hot_water, used_electric));
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


//Create a predefined sql table, so that one does not have to be configure/shipped on new devices.
//The create_month_table and create_tenant_table ensures the existence of tables needed for the application and its database to function properly.
void MainWindow::create_month_table(){
    QSqlQuery query;
    query.exec(
        "CREATE TABLE IF NOT EXISTS months ("
        "month TEXT PRIMARY KEY,"
        "water_rate REAL,"
        "gas_rate REAL,"
        "electric_rate REAL,"
        "floor_water_metric REAL,"
        "floor_gas_metric REAL,"
        "floor_electric_metric REAL,"
        "icg INTEGER"
        ")");
}
void MainWindow::create_tenant_table(){
    QSqlQuery query;
    query.exec(
        "CREATE TABLE IF NOT EXISTS tenants ("
        "month_id TEXT,"
        "tenant_id INTEGER,"
        "water_cold_metric REAL,"
        "water_hot_metric REAL,"
        "electric_metric REAL,"
        "FOREIGN KEY(month_id) REFERENCES months(month)"
        ")");
}
//Save all the monthly information (rates & metrics) to the database
void MainWindow::archive_month(){
    QSqlQuery query;
    query.prepare(
        "INSERT INTO months (month, water_rate, gas_rate, electric_rate, "
        "floor_water_metric, floor_gas_metric, floor_electric_metric, icg) "
        "VALUES (:month, :water_r, :gas_r, :electric_r, :water_metric, :gas_metric, :electric_metric, :icg)");
    // Get the selected date from widget
    QDate selectedDate = ui->ui_dateEdit->date();
    // Assign program variables to the query(insert)
    QString monthName= selectedDate.toString("yyyy-MM-dd");
    float waterRate = ui->ui_water_rate->text().toFloat();
    float gasRate = ui->ui_gas_rate->text().toFloat();
    float electricRate = ui->ui_electric_rate->text().toFloat();
    float floorWater= ui->ui_floor_water_metric->text().toFloat();
    float floorGas = ui->ui_floor_gas_metric->text().toFloat();
    float floorElectric = ui->ui_floor_electric_metric->text().toFloat();
    int icg = ui->ui_icg->text().toInt();
    query.bindValue(":month", monthName);
    query.bindValue(":water_r", waterRate);
    query.bindValue(":gas_r", gasRate);
    query.bindValue(":electric_r", electricRate);
    query.bindValue(":water_metric", floorWater);
    query.bindValue(":gas_metric", floorGas);
    query.bindValue(":electric_metric", floorElectric);
    query.bindValue(":icg", icg);

    if (!query.exec()) {
        qDebug() << "Failed to archive month, Error: " << query.lastError().text();
    } else {
        qDebug() << "Month archived successfully:" << monthName;
    }
}
//Save all the monthly tenant info (metrics) to the database's tenants table.
void MainWindow::archive_tenant(int id, int water_cold_metric, int water_hot_metric, int electric_metric){
    QSqlQuery query;
    query.prepare(
        "INSERT INTO tenants (month_id, tenant_id, water_cold_metric, water_hot_metric, electric_metric) "
        "VALUES (:month_id, :tenant_id, :water_cold, :water_hot, :electric)"
        );

    // Get tenant info from UI
    // Get the selected date from widget
    QDate selectedDate = ui->ui_dateEdit->date();
    // Assign program variables to the query(insert)
    QString monthId= selectedDate.toString("yyyy-MM-dd");
    int tenantId = id;
    int waterCold = water_cold_metric;
    int waterHot = water_hot_metric;
    int electric = electric_metric;

    // Bind values to the query
    query.bindValue(":month_id", monthId);
    query.bindValue(":tenant_id", tenantId);
    query.bindValue(":water_cold", waterCold);
    query.bindValue(":water_hot", waterHot);
    query.bindValue(":electric", electric);

    // Execute the query and check for errors
    if (!query.exec()) {
        qDebug() << "Failed to archive tenant, Error: " << query.lastError().text();
    } else {
        qDebug() << "Tenant archived successfully: ID=" << tenantId << ", Month=" << monthId;
    }
}

//Fetch last month's water/gas/electirc metric from the database.
float MainWindow::getLastMonthMetric(const QString &metricType) {
    QString queryStr = QString(
                           "SELECT floor_%1_metric FROM months ORDER BY month DESC LIMIT 1"
                           ).arg(metricType);

    QSqlQuery query;
    if (!query.exec(queryStr)) {
        qDebug() << "Query failed:" << query.lastError().text();
        return -1.0f;
    }

    if (query.next()) {
        return query.value(0).toFloat(); // only 1 column in SELECT
    }

    qDebug() << "No months found in database!";
    return -1.0f;
}

int MainWindow::getLastMonthTenantMetric(int tenantId, const QString &metricType) {
    QSqlQuery query;
    query.prepare(
        "SELECT " + metricType + " FROM tenants "
                                 "WHERE tenant_id = :tenant_id AND " + metricType + " IS NOT NULL "
                       "ORDER BY month_id DESC LIMIT 1"
        );

    query.bindValue(":tenant_id", tenantId);

    if (!query.exec() || !query.next()) {
        return 0; // Return 0 if no previous data
    }

    return query.value(0).toInt();
}
void MainWindow::database_setup(){
    //Setup relative path for the database
    QDir projectDir(QCoreApplication::applicationDirPath());
    projectDir.cdUp();
    projectDir.cdUp();
    projectDir.cdUp(); // Go up the directory path 3 levels.
    QString projectPath = projectDir.absolutePath();

    //Setup the database within the project folder.
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(projectPath + MainWindow::database_path); //PATH: set the relative path -to> the database.
    if(mydb.open()){
        qDebug() << "Database " + MainWindow::database_path + " is OPEN!"; //Open program <-to-> database connection.
    }else{
        qDebug() << "Failed to open Database. Error: " << mydb.lastError();
    }
    ui->ui_dateEdit->setDate(QDate::currentDate()); //Set system date as the default date displayed within the "ui_dateEdit" widget.
    //Setup the database's tables.
    MainWindow::create_month_table();
    MainWindow::create_tenant_table();
}









MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ui_room_table->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
    ui->ui_room_table->resizeColumnsToContents();
    ui->ui_room_table->resizeRowsToContents();
    ui->ui_calculate->setDisabled(1); //Only give the user 1 option when program starts...to select the Floor.
    ui->ui_save_state_pushButton->setDisabled(1); //Don't allow user to press Archive before the program gets to Calculate - i.e. press "Save State" before "Calculate" is NOT allowed.

    //--------inputs-----
    //Select floor 1 or 2 so that database connection can be setup. (each floor has a separate database).
    connect(ui->ui_floor1_select, &QPushButton::clicked, this, [this](){
        ui->ui_floor1_select->setDisabled(1);
        ui->ui_floor2_select->setDisabled(1);
        ui->ui_calculate->setEnabled(1);
        MainWindow::database_path = "/database1.db";
        MainWindow::database_setup();
    });
    connect(ui->ui_floor2_select, &QPushButton::clicked, this, [this](){
        ui->ui_floor1_select->setDisabled(1);
        ui->ui_floor2_select->setDisabled(1);
        ui->ui_calculate->setEnabled(1);
        MainWindow::database_path = "/database2.db";
        MainWindow::database_setup();
    });

    //Add checkboxes in first column of all 10 tenants rows
    for (int row = 0; row < 10; ++row) {
        QTableWidgetItem *checkItem = new QTableWidgetItem();
        checkItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled); // must set flags
        checkItem->setCheckState(Qt::Unchecked); // default unchecked
        ui->ui_room_table->setItem(row, 0, checkItem);
    }
    //On "calculate" button click -> fetch room/tenant information from the QtTableWidget ("ui_room_table") and store it in program memory.
    connect(ui->ui_calculate, &QPushButton::clicked, this, [this](){
        MainWindow::tenants.clear();
        MainWindow::archive_tenants.clear();
        MainWindow::store_tenants_table_info();
        ui->ui_save_state_pushButton->setEnabled(1);
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
        float last_month_floor_water_metric = MainWindow::getLastMonthMetric("water"); //Fetch last month's floor water metric from the database.
        float current_month_floor_water_metric = ui->ui_floor_water_metric->text().toFloat(&ok); //Fetch this month's floor water metric from the ui input.
        float water_metric = current_month_floor_water_metric - last_month_floor_water_metric; //This value is the actual water consumption for this month.
        if (ok) {
            MainWindow::floor_water_metric = water_metric;
            qDebug() << "Water metric updated to:" << MainWindow::floor_water_metric;
        } else {
            qDebug() << "Invalid number entered!";
        }
    });
    //Store electric metric input
    connect(ui->ui_floor_electric_metric, &QLineEdit::editingFinished, this, [this]() {
        bool ok;
        float last_month_floor_electric_metric = MainWindow::getLastMonthMetric("electric"); //Fetch last month's floor electric metric from the database.
        float current_month_floor_electric_metric = ui->ui_floor_electric_metric->text().toFloat(&ok); //Fetch this month's floor electric metric from the ui input.
        float electric_metric = current_month_floor_electric_metric - last_month_floor_electric_metric; //This value is the actual electric consumption for this month.
        if (ok) {
            MainWindow::floor_electric_metric = electric_metric;
        } else {
            qDebug() << "Invalid number entered!";
        }
    });
    //Store gas metric input
    connect(ui->ui_floor_gas_metric, &QLineEdit::editingFinished, this, [this]() {
        bool ok;
        float last_month_floor_gas_metric = MainWindow::getLastMonthMetric("gas"); //Fetch last month's floor gas metric from the database.
        float current_month_floor_gas_metric = ui->ui_floor_gas_metric->text().toFloat(&ok); //Fetch this month's floor gas metric from the ui input.
        float gas_metric = current_month_floor_gas_metric - last_month_floor_gas_metric; //This value is the actual gas consumption for this month.
        if (ok) {
            MainWindow::floor_gas_metric = gas_metric;
        } else {
            qDebug() << "Invalid number entered!";
        }
    });

    //--------------------------------------------Database Implementation----------------------

    //On "Save State" push button, archive the current month's state (rates, metrics, and tenants) into the local database.
    connect(ui->ui_save_state_pushButton, &QPushButton::clicked, this, [this]() {
        MainWindow::archive_month(); //Archive the month's water/gas/electric rates & metric.
        //Archive (for)each tenant's information into the database. (for the current  month).
        for (auto &curr_tenant : MainWindow::archive_tenants) {
            MainWindow::archive_tenant(curr_tenant.id,curr_tenant.water_cold_metric,curr_tenant.water_hot_metric,curr_tenant.electric_metric);
        }
        ui->ui_save_state_pushButton->setDisabled(1);
        ui->ui_calculate->setDisabled(1);
    });

}

MainWindow::~MainWindow()
{
    mydb.close(); //Close database connection when program finished.
    delete ui;
}
