#ifndef WORKERQUERY_H
#define WORKERQUERY_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class workerQuery;
}

class workerQuery : public QMainWindow
{
    Q_OBJECT

public:
    explicit workerQuery(const QString &workerNum, QWidget *parent = 0);
    ~workerQuery();

private slots:
    void on_btnQuerySalary_clicked();

    void on_btnQueryAward_clicked();

    void on_btnQueryAttendance_clicked();

    void on_btnQueryAllowance_clicked();

private:
    Ui::workerQuery *ui;
    QString workerNum;
    int month;
    bool setMonth();
};

#endif // WORKERQUERY_H
