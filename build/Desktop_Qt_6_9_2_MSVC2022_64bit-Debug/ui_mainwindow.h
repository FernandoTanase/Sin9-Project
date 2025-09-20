/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QLineEdit *ui_water_rate;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *ui_electric_rate;
    QLineEdit *ui_gas_rate;
    QGroupBox *groupBox_2;
    QLineEdit *ui_floor_water_metric;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *ui_floor_electric_metric;
    QLineEdit *ui_floor_gas_metric;
    QGroupBox *groupBox_3;
    QTableWidget *ui_room_table;
    QPushButton *ui_calculate;
    QGroupBox *groupBox_4;
    QTextEdit *ui_output_display;
    QGroupBox *groupBox_5;
    QLineEdit *ui_icg;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1312, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 0, 401, 111));
        ui_water_rate = new QLineEdit(groupBox);
        ui_water_rate->setObjectName("ui_water_rate");
        ui_water_rate->setEnabled(true);
        ui_water_rate->setGeometry(QRect(0, 50, 113, 28));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 30, 81, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 30, 81, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(260, 30, 81, 20));
        ui_electric_rate = new QLineEdit(groupBox);
        ui_electric_rate->setObjectName("ui_electric_rate");
        ui_electric_rate->setGeometry(QRect(130, 50, 113, 28));
        ui_gas_rate = new QLineEdit(groupBox);
        ui_gas_rate->setObjectName("ui_gas_rate");
        ui_gas_rate->setGeometry(QRect(260, 50, 113, 28));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(420, 0, 441, 111));
        ui_floor_water_metric = new QLineEdit(groupBox_2);
        ui_floor_water_metric->setObjectName("ui_floor_water_metric");
        ui_floor_water_metric->setEnabled(true);
        ui_floor_water_metric->setGeometry(QRect(0, 50, 113, 28));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 30, 91, 20));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(150, 30, 101, 20));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(290, 30, 81, 20));
        ui_floor_electric_metric = new QLineEdit(groupBox_2);
        ui_floor_electric_metric->setObjectName("ui_floor_electric_metric");
        ui_floor_electric_metric->setGeometry(QRect(150, 50, 113, 28));
        ui_floor_gas_metric = new QLineEdit(groupBox_2);
        ui_floor_gas_metric->setObjectName("ui_floor_gas_metric");
        ui_floor_gas_metric->setGeometry(QRect(290, 50, 113, 28));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(0, 120, 551, 371));
        ui_room_table = new QTableWidget(groupBox_3);
        if (ui_room_table->columnCount() < 4)
            ui_room_table->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        ui_room_table->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        ui_room_table->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        ui_room_table->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        ui_room_table->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        if (ui_room_table->rowCount() < 10)
            ui_room_table->setRowCount(10);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        ui_room_table->setVerticalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        ui_room_table->setVerticalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        ui_room_table->setVerticalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        ui_room_table->setVerticalHeaderItem(3, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        ui_room_table->setVerticalHeaderItem(4, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        ui_room_table->setVerticalHeaderItem(5, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        ui_room_table->setVerticalHeaderItem(6, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        ui_room_table->setVerticalHeaderItem(7, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        ui_room_table->setVerticalHeaderItem(8, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        ui_room_table->setVerticalHeaderItem(9, __qtablewidgetitem13);
        ui_room_table->setObjectName("ui_room_table");
        ui_room_table->setGeometry(QRect(20, 30, 521, 291));
        ui_room_table->setSortingEnabled(false);
        ui_room_table->horizontalHeader()->setVisible(true);
        ui_room_table->horizontalHeader()->setCascadingSectionResizes(false);
        ui_calculate = new QPushButton(groupBox_3);
        ui_calculate->setObjectName("ui_calculate");
        ui_calculate->setGeometry(QRect(0, 330, 90, 29));
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(580, 120, 611, 421));
        ui_output_display = new QTextEdit(groupBox_4);
        ui_output_display->setObjectName("ui_output_display");
        ui_output_display->setGeometry(QRect(20, 40, 571, 341));
        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(880, 0, 131, 111));
        ui_icg = new QLineEdit(groupBox_5);
        ui_icg->setObjectName("ui_icg");
        ui_icg->setGeometry(QRect(10, 50, 113, 28));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1312, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Floor Rates", nullptr));
        ui_water_rate->setText(QCoreApplication::translate("MainWindow", "0.0", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Water Rate", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Electric Rate", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Gas Rate", nullptr));
        ui_electric_rate->setText(QCoreApplication::translate("MainWindow", "0.0", nullptr));
        ui_gas_rate->setText(QCoreApplication::translate("MainWindow", "0.0", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Floor Metrics", nullptr));
        ui_floor_water_metric->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Water Metric", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Electric Metric", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Gas Metric", nullptr));
        ui_floor_electric_metric->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        ui_floor_gas_metric->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Rooms", nullptr));
        QTableWidgetItem *___qtablewidgetitem = ui_room_table->horizontalHeaderItem(1);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Cold Water Consumption", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = ui_room_table->horizontalHeaderItem(2);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Hot Water Consumption", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = ui_room_table->horizontalHeaderItem(3);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Electric Consumption", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = ui_room_table->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Room 1:", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = ui_room_table->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Room 2:", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = ui_room_table->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Room 3:", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = ui_room_table->verticalHeaderItem(3);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Room 4:", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = ui_room_table->verticalHeaderItem(4);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Room 5:", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = ui_room_table->verticalHeaderItem(5);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Room 6:", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = ui_room_table->verticalHeaderItem(6);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Room 7:", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = ui_room_table->verticalHeaderItem(7);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "Room 8:", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = ui_room_table->verticalHeaderItem(8);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "Room 9:", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = ui_room_table->verticalHeaderItem(9);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "Room 10:", nullptr));
        ui_calculate->setText(QCoreApplication::translate("MainWindow", "Calculate", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Results", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "ICG", nullptr));
        ui_icg->setText(QCoreApplication::translate("MainWindow", "400", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
