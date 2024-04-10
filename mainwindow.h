#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSqlQuery>
#include <QtSql>
#include <QPdfWriter>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui {
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
    void on_TicketManagementButton_clicked();

    void on_DocumentHandlingButton_clicked();

    void on_EmployeeManagementButton_clicked();

    void on_CancelTicketManagementButton_clicked();

    void on_MaintainTicketButton_clicked();

    void on_CreateTicketButton_clicked();

    void on_CancelDocumentHandlingButton_clicked();

    void on_CancelPageEmployeeManagementButton_clicked();

    void on_CancelCreateTicketButton_clicked();

    void on_CreateCreateTicketButton_clicked();

    void checkTicketSelected();

    void checkFieldsFilled();

    void checkInputs2();

    void checkRemoveButton();

    void checkAddButton();

    void on_calendarWidget_selectionChanged();

    void on_timeEdit_timeChanged(const QTime &time);

    void on_CancelMaintainButton_clicked();

    void on_MaintainMaintainButton_clicked();

    void on_CalendarsButton_clicked();

    void on_EstimateButton_clicked();

    void on_FinalCostButton_clicked();

    void on_AddEmployeeButton_clicked();

    void on_RemoveEmployeeButton_clicked();

    void on_label_13_linkActivated(const QString &link);

    void on_label_14_linkActivated(const QString &link);

    void on_label_26_linkActivated(const QString &link);

private:
    Ui::MainWindow *ui;
    QSqlDatabase Car_DB;

};
#endif // MAINWINDOW_H
