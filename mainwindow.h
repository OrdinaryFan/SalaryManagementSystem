#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QtSql>
#include <QTableView>
#include <QSqlQuery>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void show_table_kind();
    void show_table_allowance();
    void show_table_annual();
    void show_table_attendance();
    void show_table_info();
    void show_table_woker();
    void show_table_depart();
    void add_new_item();
    void del_item();
    void submit_all();
    void calc_month_salary(int month);
    void calc_annual_bonus();

private slots:
    void on_tabWidget_currentChanged(int index);

    void on_pushButton_clicked();

    void on_add1_clicked();

    void on_del1_clicked();

    void on_submit1_clicked();

    void on_pushButton_2_clicked();

    void on_add1_2_clicked();

    void on_del1_2_clicked();

    void on_submit1_2_clicked();

    void on_pushButton_3_clicked();

    void on_add1_3_clicked();

    void on_del1_3_clicked();

    void on_submit1_3_clicked();

    void on_pushButton_4_clicked();

    void on_add1_4_clicked();

    void on_del1_4_clicked();

    void on_submit1_4_clicked();

    void on_btnCalcSalary_clicked();

    void on_pushButton_6_clicked();

    void on_salarySearch_clicked();

    void on_sschNum_returnPressed();

    void on_btnSchApart_clicked();

    void on_pschApart_returnPressed();

private:
    QSqlTableModel *model;
    QSqlQueryModel *model2;
    QTableView * current_table;
    Ui::MainWindow *ui;
    int salaryShowMonth;
    QString salaryShowNum;
    QString departShowName;
    int departShowMonth;
};

#endif // MAINWINDOW_H
