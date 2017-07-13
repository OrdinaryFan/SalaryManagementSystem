#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), model(NULL), model2(NULL)
{
    ui->setupUi(this);
    salaryShowMonth = 0;
    salaryShowNum.clear();
    departShowMonth = 0;
    departShowName.clear();
    ui->tabWidget->setCurrentIndex(0);
    on_tabWidget_currentChanged(ui->tabWidget->currentIndex());
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(on_pushButton_clicked()));
    connect(ui->lineEdit_2, SIGNAL(returnPressed()), this, SLOT(on_pushButton_2_clicked()));
    connect(ui->lineEdit_3, SIGNAL(returnPressed()), this, SLOT(on_pushButton_3_clicked()));
    connect(ui->lineEdit_4, SIGNAL(returnPressed()), this, SLOT(on_pushButton_4_clicked()));
    connect(ui->sclcMonth, SIGNAL(returnPressed()), this, SLOT(on_btnCalcSalary_clicked()));
    connect(ui->sschMonth, SIGNAL(returnPressed()), this, SLOT(on_salarySearch_clicked()));
    connect(ui->pschMonth, SIGNAL(returnPressed()), this, SLOT(on_btnSchApart_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch(index)
    {
    case 0:
        show_table_kind();//工种信息表
        break;
    case 1:
        show_table_attendance();//考勤表
        break;
    case 2:
        show_table_allowance();//加班津贴表
        break;
    case 3:
        show_table_info();//职工基本信息表
        break;
    case 4:
        show_table_woker();//员工工资表
        break;
    case 5:
        show_table_depart();
        break;
    case 6:
        show_table_annual();//员工年终奖
        break;
    }
}

void MainWindow::show_table_kind()
{
    current_table = ui->tableView_kind;
    delete model;
    model = new QSqlTableModel;

    model->setTable("kind");
    model->setHeaderData(0,Qt::Horizontal,"工种");
    model->setHeaderData(1,Qt::Horizontal,"等级");
    model->setHeaderData(2,Qt::Horizontal,"薪水");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0,Qt::AscendingOrder);
    model->select();
    current_table->setModel(model);
    current_table->setSortingEnabled(true);
    current_table->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::show_table_attendance()
{
    current_table = ui->tableView_attendance;
    delete model;
    model = new QSqlTableModel;

    model->setTable("attendance");
    model->setHeaderData(0,Qt::Horizontal,"员工号");
    model->setHeaderData(1,Qt::Horizontal,"月份");
    model->setHeaderData(2,Qt::Horizontal,"缺勤天数");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0,Qt::AscendingOrder);
    model->select();    //Populates the model with data from the table that was set via setTable()
    current_table->setModel(model);
    current_table->setSortingEnabled(true);
    current_table->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::show_table_allowance()
{
    current_table = ui->tableView_allowance;
    delete model;
    model = new QSqlTableModel;

    model->setTable("allowance");
    model->setHeaderData(0, Qt::Horizontal,"员工号");
    model->setHeaderData(1, Qt::Horizontal,"类型");
    model->setHeaderData(2, Qt::Horizontal,"时间");
    model->setHeaderData(3, Qt::Horizontal,"天数");
    model->setHeaderData(4, Qt::Horizontal,"津贴");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0,Qt::AscendingOrder);
    model->select();    //Populates the model with data from the table that was set via setTable()
    current_table->setModel(model);
    current_table->setSortingEnabled(true);
    current_table->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::show_table_info()
{
    current_table = ui->tableView_info;
    delete model;
    model = new QSqlTableModel;

    model->setTable("info");
    model->setHeaderData(0,Qt::Horizontal,"员工号");
    model->setHeaderData(1,Qt::Horizontal,"姓名");
    model->setHeaderData(2,Qt::Horizontal,"年龄");
    model->setHeaderData(3,Qt::Horizontal,"部门");
    model->setHeaderData(4,Qt::Horizontal,"工种");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0,Qt::AscendingOrder);
    model->select();    //Populates the model with data from the table that was set via setTable()
    current_table->setModel(model);
    current_table->setSortingEnabled(true);
    current_table->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::show_table_woker()
{
    current_table = ui->tableView_woker;
    delete model2;
    QString queryCommand("select * from salary");
    model2 = new QSqlQueryModel;

    if(!salaryShowNum.isEmpty() && salaryShowMonth > 0)
        queryCommand += QString(" where snum=%1 and smonth=%2").arg(salaryShowNum).arg(salaryShowMonth);
    else if (!salaryShowNum.isEmpty())
        queryCommand += QString(" where snum=%1").arg(salaryShowNum);
    else if (salaryShowMonth > 0)
        queryCommand += QString(" where smonth=%2").arg(salaryShowMonth);

    model2->setQuery(queryCommand);
    model2->setHeaderData(0, Qt::Horizontal, "员工号");
    model2->setHeaderData(1, Qt::Horizontal, "月份");
    model2->setHeaderData(2, Qt::Horizontal, "工资");
    current_table->setModel(model2);
    //current_table->setSortingEnabled(true);
    current_table->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::show_table_depart()
{
    current_table = ui->tableView_depart;
    delete model2;
    QString queryCommand("select inum, iname, idep, smonth, smoney from info, salary where inum=snum");
    model2 = new QSqlQueryModel;

    if (!departShowName.isEmpty())
        queryCommand += QString(" and idep='%1'").arg(departShowName);
    if (departShowMonth > 0)
        queryCommand += QString(" and smonth=%1").arg(departShowMonth);

    model2->setQuery(queryCommand);
    model2->setHeaderData(0, Qt::Horizontal, "员工号");
    model2->setHeaderData(1, Qt::Horizontal, "员工姓名");
    model2->setHeaderData(2, Qt::Horizontal, "部门");
    model2->setHeaderData(3, Qt::Horizontal, "月份");
    model2->setHeaderData(4, Qt::Horizontal, "工资");
    current_table->setModel(model2);
    //current_table->setSortingEnabled(true);
    current_table->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::show_table_annual()
{
    current_table = ui->tableView_annual;
    delete model2;
    model2 = new QSqlQueryModel;

    model2->setQuery("select * from yaward");
    model2->setHeaderData(0, Qt::Horizontal, "员工号");
    model2->setHeaderData(1, Qt::Horizontal, "月份");
    model2->setHeaderData(2, Qt::Horizontal, "奖金");
    current_table->setModel(model2);
    //current_table->setSortingEnabled(true);
    current_table->horizontalHeader()->setStretchLastSection(true);
}

/*******************查询********************/
void MainWindow::on_pushButton_clicked()
{
    QString gnum;
    gnum = ui->lineEdit->text().trimmed();
    if (gnum.isEmpty())
        model->setFilter(gnum);
    else
        model->setFilter(QString("ktype=\'%1\'").arg(gnum));
}

void MainWindow::on_pushButton_2_clicked()
{
    QString gnum;
    gnum = ui->lineEdit_2->text().trimmed();
    if (gnum.isEmpty())
        model->setFilter(gnum);
    else
        model->setFilter(QString("adnum=\'%1\'").arg(gnum));
}

void MainWindow::on_pushButton_3_clicked()
{
    QString gnum;
    gnum = ui->lineEdit_3->text().trimmed();
    if (gnum.isEmpty())
        model->setFilter(gnum);
    else
        model->setFilter(QString("anum=\'%1\'").arg(gnum));
}

void MainWindow::on_pushButton_4_clicked()
{
    QString gnum;
    gnum = ui->lineEdit_4->text().trimmed();
    if (gnum.isEmpty())
        model->setFilter(gnum);
    else
        model->setFilter(QString("inum=\'%1\'").arg(gnum));
}

void MainWindow::submit_all()
{
    if(model)
    {
        model->database().transaction(); //开始事务操作
        if(model->submitAll())//提交修改到数据库中
           model->database().commit(); //提交成功，事务操作将保存数据到数据库中
        else
        {
            model->database().rollback(); //回滚
            QMessageBox::warning(this,"提示","提交失败","确定");
        }
    }
}

/****************增加*****************/
void MainWindow::add_new_item()
{
    if(model)
    {
        model->insertRow(model->rowCount());
    }
}
void MainWindow::on_add1_clicked()
{
    add_new_item();
}

void MainWindow::on_add1_2_clicked()
{
    add_new_item();
}

void MainWindow::on_add1_3_clicked()
{
    add_new_item();
}

void MainWindow::on_add1_4_clicked()
{
    add_new_item();
}

/****************删除*****************/
void MainWindow::del_item()
{
    if(model)
    {
        int curRow=current_table->currentIndex().row();
        //获取选中的行
        if(curRow!=-1)
        {
            int ok = QMessageBox::warning(this,"提示","删除选中行",QMessageBox::Yes,QMessageBox::No);
            if(ok == QMessageBox::Yes)
            {
                model->removeRow(curRow);
                model->submitAll();
            }
        }
    }
}

void MainWindow::on_del1_clicked()
{
    del_item();
}

void MainWindow::on_del1_2_clicked()
{
    del_item();
}

void MainWindow::on_del1_3_clicked()
{
    del_item();
}

void MainWindow::on_del1_4_clicked()
{
    del_item();
}


void MainWindow::on_submit1_clicked()
{
    submit_all();
    show_table_kind();
}

void MainWindow::on_submit1_2_clicked()
{
    submit_all();
    show_table_attendance();
}

void MainWindow::on_submit1_3_clicked()
{
    submit_all();
    show_table_allowance();
}

void MainWindow::on_submit1_4_clicked()
{
    submit_all();
    show_table_info();
}

//计算工资
void MainWindow::calc_month_salary(int month)
{
    QSqlQuery employee;

    employee.setForwardOnly(true);
    employee.exec(QStringLiteral("select inum, ksalary from info, kind where ktype=itype"));
    QList<QString> employeeNums;
    QList<float> baseSalaries;
    while (employee.next()) {
        employeeNums.append(employee.value(0).toString());
        baseSalaries.append(employee.value(1).toFloat());
    }
    for (int i = 0; i < employeeNums.size(); i++) {
        QSqlQuery allowance, attendance;

        allowance.exec(QString("select atime, aallow from allowance where anum=%1").arg(employeeNums[i]));
        while (allowance.next()) {
            QDateTime date = allowance.value(0).toDateTime();
            if (date.date().month() != month)
                continue;
            baseSalaries[i] += allowance.value(1).toFloat();
        }

        attendance.setForwardOnly(true);
        attendance.exec(QString("select addays from attendance where adnum=%1 and admonth=%2")
                        .arg(employeeNums[i]).arg(month));
        while (attendance.next())
            baseSalaries[i] -= 100 * attendance.value(0).toInt();

        QSqlQuery existence, modify;
        existence.setForwardOnly(true);
        existence.exec(QString("select * from salary where snum=%1 and smonth=%2").arg(employeeNums[i]).arg(month));
        bool isExist = false;
        while (existence.next())
            isExist = true;

        if (isExist) {
            modify.exec(QString("update salary set smoney=%1 where snum=%2 and smonth=%3")
                        .arg(baseSalaries[i]).arg(employeeNums[i]).arg(month));   //修改
        } else {
            modify.prepare("INSERT INTO salary  (snum, smonth, smoney)"
                           " VALUES (?, ?, ?)");
            modify.bindValue(0, employeeNums[i]);
            modify.bindValue(1, month);
            modify.bindValue(2, QString::number(baseSalaries[i]));
            modify.exec();
        }
    }
}

//计算年终奖
void MainWindow::calc_annual_bonus()
{
    QSqlQuery employee;

    employee.setForwardOnly(true);
    employee.exec("select inum from info");

    QList<QString> employeeNums;

    while (employee.next())
        employeeNums.append(employee.value(0).toString());

    for (int i = 0; i < employeeNums.size(); i++) {
        QSqlQuery salary;
        float total = 0;

        salary.setForwardOnly(true);
        salary.exec(QString("select smoney from salary where snum=%1").arg(employeeNums[i]));
        while (salary.next())
            total += salary.value(0).toFloat();

        QSqlQuery allowance;

        allowance.setForwardOnly(true);
        allowance.exec(QString("select aallow from allowance where anum=%1").arg(employeeNums[i]));
        while (allowance.next())
            total += allowance.value(0).toFloat();

        total /= 12;

        QSqlQuery existence, modify;
        existence.exec(QString("select * from yaward where ynum=%1").arg(employeeNums[i]));
        bool isExist = false;
        while (existence.next())
            isExist = true;
        if (isExist) {
            modify.prepare("update yaward set ymoney=? where ynum=?");
            modify.bindValue(0, QString::number(total));
            modify.bindValue(1, employeeNums[i]);
            modify.exec();
        } else {
            modify.prepare("insert into yaward(ynum, yyear, ymoney)"
                           "values (?, ?, ?)");
            modify.bindValue(0, employeeNums[i]);
            modify.bindValue(1, QDate::currentDate().year());
            modify.bindValue(2, QString::number(total));
            modify.exec();
        }
    }
}

void MainWindow::on_btnCalcSalary_clicked()
{
    if (ui->sclcMonth->text().trimmed().isEmpty()) {
        for (int i = 1; i <= 12; i++)
            calc_month_salary(i);
        salaryShowNum.clear();
        salaryShowMonth = 0;
        show_table_woker();
    } else {
        bool isNumber;
        int month = ui->sclcMonth->text().toInt(&isNumber);

        if (!isNumber || month < 1 || month > 12) {
            QMessageBox::critical(this, QStringLiteral("错误"), QStringLiteral("请输入1~12的数字"), QMessageBox::Ok);
            return;
        }
        calc_month_salary(month);
        salaryShowMonth = month;
        salaryShowNum.clear();
        show_table_woker();
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    calc_annual_bonus();
    show_table_annual();
}

void MainWindow::on_salarySearch_clicked()
{
    QString strMonth = ui->sschMonth->text().trimmed();
    bool isInt;
    int intMonth = strMonth.toInt(&isInt);

    if (strMonth.isEmpty())
        salaryShowMonth = 0;
    else if (isInt && intMonth > 0 && intMonth < 13)
        salaryShowMonth = intMonth;
    else {
        QMessageBox::critical(this, QStringLiteral("错误"), QStringLiteral("请输入1~12之间的整数"), QMessageBox::Ok);
        return;
    }
    salaryShowNum = ui->sschNum->text().trimmed();
    show_table_woker();
}

void MainWindow::on_sschNum_returnPressed()
{
    ui->sschMonth->setFocus();
}

void MainWindow::on_btnSchApart_clicked()
{
    delete model2;
    model2 = new QSqlQueryModel;

    QString strMonth;
    int intMonth;
    bool isInt;

    strMonth = ui->pschMonth->text().trimmed();
    intMonth = strMonth.toInt(&isInt);
    if (!strMonth.isEmpty() && (!isInt || intMonth < 0 || intMonth > 12)) {
        QMessageBox::critical(this, QStringLiteral("错误"), QStringLiteral("请输入1~12之间的整数"), QMessageBox::Ok);
        return;
    }
    if (!strMonth.isEmpty())
        departShowMonth = intMonth;
    else
        departShowMonth = 0;

    departShowName = ui->pschApart->text().trimmed();
    show_table_depart();
}

void MainWindow::on_pschApart_returnPressed()
{
    ui->pschMonth->setFocus();
}
