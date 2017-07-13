#include "workerquery.h"
#include "ui_workerquery.h"
#include <QMessageBox>
#include <QStandardItemModel>

workerQuery::workerQuery(const QString &workerNum, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::workerQuery)
{
    ui->setupUi(this);
    this->workerNum = workerNum;
    setWindowTitle(QStringLiteral("工资管理系统"));
    month = 0;
}

workerQuery::~workerQuery()
{
    delete ui;
}

void workerQuery::on_btnQuerySalary_clicked()
{
    if (!setMonth())
        return;
    auto getModel = ui->tableView->model();
    ui->tableView->setModel(NULL);
    delete getModel;

    QSqlQueryModel *model;
    model = new QSqlQueryModel;
    QString queryCommand = QString("select smonth, smoney from salary where snum='%1'").arg(workerNum);

    if (month > 0)
        queryCommand += QString(" and smonth=%1").arg(month);
    model->setQuery(queryCommand);
    model->setHeaderData(0, Qt::Horizontal, "月份");
    model->setHeaderData(1, Qt::Horizontal, "工资");
    ui->tableView->setModel(model);
}

bool workerQuery::setMonth()
{
    int intMonth;
    QString strMonth;
    bool isInt;

    strMonth = ui->lineEdit->text().trimmed();
    intMonth = strMonth.toInt(&isInt);
    if (!strMonth.isEmpty() && (!isInt || intMonth < 0 || intMonth > 12)) {
        QMessageBox::critical(this, QStringLiteral("错误"), QStringLiteral("请输入1~12之间的整数"), QMessageBox::Ok);
        return false;
    }

    if (strMonth.isEmpty())
        month = 0;
    else
        month = intMonth;
    return true;
}

void workerQuery::on_btnQueryAward_clicked()
{
    auto getModel = ui->tableView->model();
    ui->tableView->setModel(NULL);
    delete getModel;

    QSqlQueryModel *model;
    model = new QSqlQueryModel;
    QString queryCommand = QString("select yyear, ymoney from yaward where ynum='%1'").arg(workerNum);

    model->setQuery(queryCommand);
    model->setHeaderData(0, Qt::Horizontal, "年份");
    model->setHeaderData(1, Qt::Horizontal, "年终奖");
    ui->tableView->setModel(model);
}

void workerQuery::on_btnQueryAttendance_clicked()
{
    if (!setMonth())
        return;

    auto getModel = ui->tableView->model();
    ui->tableView->setModel(NULL);
    delete getModel;

    QSqlQueryModel *model;
    model = new QSqlQueryModel;
    QString queryCommand = QString("select admonth, addays from attendance where adnum='%1'").arg(workerNum);

    if (month > 0)
        queryCommand += QString(" and admonth=%1").arg(month);
    model->setQuery(queryCommand);
    model->setHeaderData(0, Qt::Horizontal, "月份");
    model->setHeaderData(1, Qt::Horizontal, "缺勤天数");
    ui->tableView->setModel(model);
}

void workerQuery::on_btnQueryAllowance_clicked()
{
    if (!setMonth())
        return;

    auto getModel = ui->tableView->model();
    ui->tableView->setModel(NULL);
    delete getModel;

    QStandardItemModel *model = new QStandardItemModel;
    model->setColumnCount(4);
    model->setHeaderData(0, Qt::Horizontal, "类型");
    model->setHeaderData(1, Qt::Horizontal, "时间");
    model->setHeaderData(2, Qt::Horizontal, "天数");
    model->setHeaderData(3, Qt::Horizontal, "津贴");
    QSqlQuery query;
    int rows = 0;

    query.exec(QString("select atype, atime, adays, aallow from allowance where anum='%1'").arg(workerNum));
    while (query.next()) {
        QString qrType = query.value(0).toString();
        QDateTime qrDate = query.value(1).toDateTime();
        int qrMonth = qrDate.date().month();
        int qrDays = query.value(2).toInt();
        float qrAllow = query.value(3).toFloat();

        if (month == 0 || month == qrMonth) {
            model->setItem(rows, 0, new QStandardItem(qrType));
            model->setItem(rows, 1, new QStandardItem(qrDate.toString("yyyy-M-d dddd h:m:s")));
            model->setItem(rows, 2, new QStandardItem(QString::number(qrDays)));
            model->setItem(rows, 3, new QStandardItem(QString::number(qrAllow)));
            rows++;
        }
    }
    ui->tableView->setModel(model);
}
