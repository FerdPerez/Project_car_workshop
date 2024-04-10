#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    //Database
    Car_DB = QSqlDatabase::addDatabase("QSQLITE");
    Car_DB.setDatabaseName(QCoreApplication::applicationDirPath() + "/Car_workshop.db");
    if(Car_DB.open())
    {
        qDebug() << "Database connected";
    }
    else
    {
        qDebug() << "Database not connected";
        qDebug() << "Error : " << Car_DB.lastError();
    }

    //PageMainWindow
    connect(ui->TicketManagementButton, &QPushButton::clicked, this, &MainWindow::on_TicketManagementButton_clicked);
    connect(ui->DocumentHandlingButton, &QPushButton::clicked, this, &MainWindow::on_DocumentHandlingButton_clicked);
    connect(ui->EmployeeManagementButton, &QPushButton::clicked, this, &MainWindow::on_EmployeeManagementButton_clicked);

    //PageTicketManagement
    connect(ui->CancelTicketManagementButton, &QPushButton::clicked, this, &MainWindow::on_CancelTicketManagementButton_clicked);
        //CreateTicket
        connect(ui->CreateTicketButton, &QPushButton::clicked, this, &MainWindow::on_CreateTicketButton_clicked);
        connect(ui->CancelCreateTicketButton, &QPushButton::clicked, this, &MainWindow::on_CancelCreateTicketButton_clicked);
        //MaintainTicket
        connect(ui->lineEdit_8, &QLineEdit::textChanged, this, &MainWindow::checkInputs2);
        connect(ui->textEdit_2, &QTextEdit::textChanged, this, &MainWindow::checkInputs2);
        connect(ui->lineEdit_5, &QLineEdit::textChanged, this, &MainWindow::checkInputs2);
        connect(ui->lineEdit_11, &QLineEdit::textChanged, this, &MainWindow::checkInputs2);
        connect(ui->lineEdit_9, &QLineEdit::textChanged, this, &MainWindow::checkInputs2);
        connect(ui->lineEdit_10, &QLineEdit::textChanged, this, &MainWindow::checkInputs2);
        connect(ui->radioButton, &QRadioButton::toggled, this, &MainWindow::checkInputs2);
        connect(ui->radioButton_2, &QRadioButton::toggled, this, &MainWindow::checkInputs2);




    //PageDocumentHandling
    connect(ui->CancelDocumentHandlingButton, &QPushButton::clicked, this, &MainWindow::on_CancelDocumentHandlingButton_clicked);
    connect(ui->lineEdit_15, &QLineEdit::textChanged, this, &MainWindow::checkTicketSelected);

    ui->CalendarsButton->setEnabled(false);
    ui->FinalCostButton->setEnabled(false);
    ui->EstimateButton->setEnabled(false);


    //PageEmployeeManagement
    connect(ui->CancelPageEmployeeManagementButton, &QPushButton::clicked, this, &MainWindow::on_CancelPageEmployeeManagementButton_clicked);
    connect(ui->lineEdit_18, &QLineEdit::textChanged, this, &MainWindow::checkRemoveButton);
    connect(ui->lineEdit_18, &QLineEdit::textChanged, this, &MainWindow::checkAddButton);
    connect(ui->lineEdit_16, &QLineEdit::textChanged, this, &MainWindow::checkAddButton);
    connect(ui->lineEdit_17, &QLineEdit::textChanged, this, &MainWindow::checkAddButton);
    connect(ui->calendarWidget_2, &QCalendarWidget::selectionChanged, this, &MainWindow::checkAddButton);
    connect(ui->timeEdit_2, &QTimeEdit::timeChanged, this, &MainWindow::checkAddButton);



    //CreatingTicket
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::checkFieldsFilled);
    connect(ui->lineEdit_2, &QLineEdit::textChanged, this, &MainWindow::checkFieldsFilled);
    connect(ui->lineEdit_3, &QLineEdit::textChanged, this, &MainWindow::checkFieldsFilled);
    connect(ui->lineEdit_4, &QLineEdit::textChanged, this, &MainWindow::checkFieldsFilled);
    connect(ui->textEdit, &QTextEdit::textChanged, this, &MainWindow::checkFieldsFilled);

    connect(ui->calendarWidget, &QCalendarWidget::selectionChanged, this, &MainWindow::on_calendarWidget_selectionChanged);
    connect(ui->timeEdit_3, &QTimeEdit::timeChanged, this, &MainWindow::on_timeEdit_timeChanged);


}

void MainWindow::on_calendarWidget_selectionChanged()
{
    QString dateString = ui->calendarWidget->selectedDate().toString("yyyy-MM-dd");
}

void MainWindow::on_timeEdit_timeChanged(const QTime &time)
{
    QString timeString = time.toString("HH:mm");
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_TicketManagementButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_DocumentHandlingButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_EmployeeManagementButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->AddEmployeeButton->setEnabled(false);
    ui->RemoveEmployeeButton->setEnabled(false);
}


void MainWindow::on_CancelTicketManagementButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_MaintainTicketButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->MaintainMaintainButton->setEnabled(false);
}


void MainWindow::on_CreateTicketButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->CreateCreateTicketButton->setEnabled(false);
}


void MainWindow::on_CancelDocumentHandlingButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_CancelPageEmployeeManagementButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_CancelCreateTicketButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}



void MainWindow::on_CreateCreateTicketButton_clicked()
{
    QString dateString = ui->calendarWidget->selectedDate().toString("yyyy-MM-dd");
    QString timeString = ui->timeEdit_3->time().toString("HH:mm");
    QString dateTimeString = dateString + " " + timeString;

    Car_DB.open();
    QSqlDatabase::database().transaction();
    QSqlQuery QueryInsertData(Car_DB);
    QueryInsertData.prepare("INSERT INTO Ticket(Ticket_ID,Vehicule_brand,Vehicule_model,Description,Employee_assigned,Time_slot,State,Price_paid) VALUES(:Ticket_ID,:Vehicule_brand,:Vehicule_model,:Description,:Employee_assigned,:Time_slot,:State,:Price_paid)");
    QueryInsertData.bindValue(":Ticket_ID",ui->lineEdit_3->text());
    QueryInsertData.bindValue(":Vehicule_brand",ui->lineEdit->text());
    QueryInsertData.bindValue(":Vehicule_model",ui->lineEdit_2->text());
    QueryInsertData.bindValue(":Employee_assigned",ui->lineEdit_4->text());
    QueryInsertData.bindValue(":Description",ui->textEdit->toPlainText());
    QueryInsertData.bindValue(":Time_slot", dateTimeString);
    QueryInsertData.bindValue(":State","Created");
    QueryInsertData.bindValue(":Price_paid",0.0);

    if (!QueryInsertData.exec())
    {
        qDebug() << "Error executing query:" << QueryInsertData.lastError().text();
    }

    if (!QSqlDatabase::database().commit())
    {
        qDebug() << "Error committing transaction:" << QSqlDatabase::database().lastError().text();
    }

    Car_DB.close();

    ui->stackedWidget->setCurrentIndex(0);
}



void MainWindow::checkFieldsFilled()
{
    bool fieldsNotEmpty = !ui->lineEdit->text().isEmpty() &&
                          !ui->lineEdit_2->text().isEmpty() &&
                          !ui->lineEdit_3->text().isEmpty() &&
                          !ui->lineEdit_4->text().isEmpty() &&
                          !ui->textEdit->toPlainText().isEmpty();

    ui->CreateCreateTicketButton->setEnabled(fieldsNotEmpty);
}

void MainWindow::on_CancelMaintainButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_MaintainMaintainButton_clicked()
{
    QString ticketID = ui->lineEdit_8->text();
    QString description = ui->textEdit_2->toPlainText();
    QString expectedCost = ui->lineEdit_5->text();
    QString partName = ui->lineEdit_11->text();
    QString amount = ui->lineEdit_9->text();
    QString unitPrice = ui->lineEdit_10->text();
    QString selectedValue;
    if (ui->radioButton->isChecked()) {
        selectedValue = ui->radioButton->text();
    } else if (ui->radioButton_2->isChecked()) {
        selectedValue = ui->radioButton_2->text();
    }

    QSqlQuery estimationQuery;
    estimationQuery.prepare("INSERT INTO RepairEstimation (ticket_id, description, accepted_by_client, expected_cost) "
                            "VALUES (:ticketID, :description, :accepted_by_client, :expected_cost)");
    estimationQuery.bindValue(":ticketID", ticketID);
    estimationQuery.bindValue(":description", description);
    estimationQuery.bindValue(":accepted_by_client", selectedValue);
    estimationQuery.bindValue(":expected_cost", expectedCost);

    QSqlQuery partsQuery;
    partsQuery.prepare("INSERT INTO BoughtParts (ticket_id, name, amount, unit_price) "
                       "VALUES (:ticketID, :name, :amount, :unitPrice)");
    partsQuery.bindValue(":ticketID", ticketID);
    partsQuery.bindValue(":name", partName);
    partsQuery.bindValue(":amount", amount);
    partsQuery.bindValue(":unitPrice", unitPrice);

    ui->stackedWidget->setCurrentIndex(0);
}



void MainWindow::on_CalendarsButton_clicked()
{
    QString ticketID = ui->lineEdit_15->text();
    QString timeSlot = ui->calendarWidget->selectedDate().toString("yyyy-MM-dd");

    QSqlQuery query;
    query.prepare("UPDATE Ticket SET Time_slot = :timeSlot WHERE Ticket_ID = :ticketID");
    query.bindValue(":timeSlot", timeSlot);
    query.bindValue(":ticketID", ticketID);

    if (query.exec()) {
        QString filePath = "time_slot_ticket_" + ticketID + ".pdf";
        QPdfWriter pdfWriter(filePath);
        QPainter painter(&pdfWriter);

        painter.drawText(100, 100, "Ticket ID: " + ticketID);
        painter.drawText(100, 120, "Time Slot: " + timeSlot);
        painter.end();

        qDebug() << "File PDF saved to :" << filePath;
    } else {
        qDebug() << "Error on the ticket :" << ticketID << "Error :" << query.lastError().text();
    }

    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::checkTicketSelected()
{
    bool lineEditFilled = !ui->lineEdit_15->text().isEmpty();
    ui->CalendarsButton->setEnabled(lineEditFilled);
    ui->FinalCostButton->setEnabled(lineEditFilled);
    ui->EstimateButton->setEnabled(lineEditFilled);
}

void MainWindow::on_EstimateButton_clicked()
{
    QString ticketID = ui->lineEdit->text();

    QSqlQuery query;
    query.prepare("SELECT expected_cost FROM repairEstimation WHERE ticket_id = :ticketID");
    query.bindValue(":ticketID", ticketID);

    if (query.exec() && query.next()) {
        QString estimateInfo = "Estimation of the ticket " + ticketID + " : " + query.value(0).toString();

        QString filePath = "estimate_ticket_" + ticketID + ".pdf";
        QPdfWriter pdfWriter(filePath);
        QPainter painter(&pdfWriter);

        painter.drawText(100, 100, estimateInfo);

        painter.end();
    } else {
        qDebug() << "Error :" << query.lastError().text();
    }

    ui->stackedWidget->setCurrentIndex(0);
}



void MainWindow::on_FinalCostButton_clicked()
{
    QString ticketID = ui->lineEdit->text();

    QSqlQuery query;
    query.prepare("SELECT Price_paid, Time_slot FROM Ticket WHERE Ticket_ID = :ticketID");
    query.bindValue(":ticketID", ticketID);

    if (query.exec() && query.next()) {
        QString pricePaid = query.value(0).toString();
        QString timeSlot = query.value(1).toString();

        QSqlQuery partsQuery;
        partsQuery.prepare("SELECT * FROM BoughtsParts WHERE ticket_id = :ticketID");
        partsQuery.bindValue(":ticketID", ticketID);
        if (partsQuery.exec()) {
            QString partsList;
            while (partsQuery.next()) {
                partsList += partsQuery.value(0).toString() + ": " + partsQuery.value(1).toString() + ", ";
            }

            QString filePath = "final_cost_ticket_" + ticketID + ".pdf";
            QPdfWriter pdfWriter(filePath);
            QPainter painter(&pdfWriter);

            painter.drawText(100, 100, "Ticket ID: " + ticketID);
            painter.drawText(100, 120, "Price Paid: " + pricePaid);
            painter.drawText(100, 140, "Time Slot: " + timeSlot);
            painter.drawText(100, 160, "Parts Bought: " + partsList);

            painter.end();

        }
    } else {
        qDebug() << "Error :" << query.lastError().text();
    }

    ui->stackedWidget->setCurrentIndex(0);
}



void MainWindow::on_AddEmployeeButton_clicked()
{
    QString employeeID = ui->lineEdit_18->text();
    QString employeeName = ui->lineEdit_16->text();
    QString pricePerHour = ui->lineEdit_17->text();
    QString dateTime = ui->calendarWidget_2->selectedDate().toString("yyyy-MM-dd") + " " + ui->timeEdit_2->time().toString("HH:mm");

    QSqlQuery employeeQuery;
    employeeQuery.prepare("INSERT INTO Employee (Employee_ID, Name, Price_Per_Hour) "
                          "VALUES (:employeeID, :employeeName, :pricePerHour)");
    employeeQuery.bindValue(":employeeID", employeeID);
    employeeQuery.bindValue(":employeeName", employeeName);
    employeeQuery.bindValue(":pricePerHour", pricePerHour);

    if (employeeQuery.exec()) {
        qDebug() << "Data added to the table Employee";
    } else {
        qDebug() << "Error while adding to the table Employee :" << employeeQuery.lastError().text();
    }

    QSqlQuery availabilityQuery;
    availabilityQuery.prepare("INSERT INTO EmployeeAvailability (Employee_ID, Date_Time, Available) "
                              "VALUES (:employeeID, :dateTime, :available)");
    availabilityQuery.bindValue(":employeeID", employeeID);
    availabilityQuery.bindValue(":dateTime", dateTime);
    availabilityQuery.bindValue(":available", "available");

    if (availabilityQuery.exec()) {
        qDebug() << "Data added in the table EmployeeAvailability";
    } else {
        qDebug() << "Error while adding data in the table EmployeeAvailability :" << availabilityQuery.lastError().text();
    }

    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_RemoveEmployeeButton_clicked()
{
    QString employeeID = ui->lineEdit_18->text();


    QSqlQuery query;
    query.prepare("DELETE FROM Employee WHERE Employee_ID = :employeeID");
    query.bindValue(":employeeID", employeeID);

    if (query.exec()) {
        qDebug() << "Suppression succed in the table Employee";
    } else {
        qDebug() << "Error in suppression in the table Employee :" << query.lastError().text();
    }

    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_label_13_linkActivated(const QString &link)
{
    QSqlQuery query("SELECT Available FROM Employee_ID WHERE ID = " + ui->lineEdit_15->text() + ";");
    if (query.exec()) {
        if (query.next()) {
            QString valeur = query.value(0).toString();

            QLabel label(valeur);
            label.show();
        } else {
            qDebug() << "No result found";
        }
    } else {
        qDebug() << "Error while executing the request :" << query.lastError().text();
    }

}


void MainWindow::on_label_14_linkActivated(const QString &link)
{
    QSqlQuery query("SELECT State FROM Ticket WHERE Employee = " + ui->lineEdit_4->text() + ";");
    if (query.exec()) {
        if (query.next()) {
            QString valeur = query.value(0).toString();

            QLabel label(valeur);
            label.show();
        } else {
            qDebug() << "No result found";
        }
    } else {
        qDebug() << "Error while executing the request :" << query.lastError().text();
    }
}


void MainWindow::on_label_26_linkActivated(const QString &link)
{
    QSqlQuery query("SELECT Price_paid FROM Ticket WHERE Ticket_ID = " + ui->lineEdit_8->text() + ";");
    if (query.exec()) {
        if (query.next()) {
            QString valeur = query.value(0).toString();

            QLabel label(valeur);
            label.show();
        } else {
            qDebug() << "No result found";
        }
    } else {
        qDebug() << "Error while executing the request :" << query.lastError().text();
    }
}

void MainWindow::checkInputs2() {
    bool allFilled = !ui->lineEdit_8->text().isEmpty() &&
                     !ui->textEdit_2->toPlainText().isEmpty() &&
                     !ui->lineEdit_5->text().isEmpty() &&
                     !ui->lineEdit_11->text().isEmpty() &&
                     !ui->lineEdit_9->text().isEmpty() &&
                     !ui->lineEdit_10->text().isEmpty() &&
                     (ui->radioButton->isChecked() || ui->radioButton_2->isChecked());

    ui->MaintainMaintainButton->setEnabled(allFilled);
}

void MainWindow::checkRemoveButton() {
    bool filled = !ui->lineEdit_18->text().isEmpty();
    ui->RemoveEmployeeButton->setEnabled(filled);
}

void MainWindow::checkAddButton() {
    bool allFilled = !ui->lineEdit_18->text().isEmpty() &&
                     !ui->lineEdit_16->text().isEmpty() &&
                     !ui->lineEdit_17->text().isEmpty() &&
                     !ui->calendarWidget_2->selectedDate().isNull() &&
                     !ui->timeEdit_2->time().isNull();

    ui->AddEmployeeButton->setEnabled(allFilled);
}
