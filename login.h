#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QtSql>
#include <QSqlQuery>
#include "mainwindow.h"

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

public slots:
    void on_pushButton_clicked();

private:
    Ui::login *ui;
    MainWindow * sms;
};

#endif // LOGIN_H
