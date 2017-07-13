#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include "workerquery.h"

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    ui->password_lineEdit->setEchoMode(QLineEdit::Password);
    ui->user_lineEdit->setPlaceholderText("请输入用户账号");
    ui->password_lineEdit->setPlaceholderText("请输入密码");
    ui->pushButton->setCursor(QCursor(Qt::PointingHandCursor));
    connect(ui->password_lineEdit, SIGNAL(returnPressed()), this, SLOT(on_pushButton_clicked()));
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(QString("DRIVER={SQL SERVER};"
                               "SERVER=%1;"
                               "DATABASE=%2;"
                               "UID=%3;"
                               "PWD=%4;")
                       .arg("fan\\SQLEXPRESS")
                       .arg("Salary management system")
                       .arg("zjp")
                       .arg("101314"));
    db.open();
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    if (ui->user_lineEdit->text() == "zjp" && ui->password_lineEdit->text() == "101314") {
        this->close();
        sms = new MainWindow();
        sms->setWindowTitle("工资管理系统");
        sms->show();
        return;
    }
    QSqlQuery tmp;
    QString num, pwd;
    num = ui->user_lineEdit->text().trimmed();
    pwd = ui->password_lineEdit->text().trimmed();
    qDebug() << num << pwd;
    tmp.exec(QString("select anum, apassword from account where anum=%1").arg(num));
    tmp.next();
    if(tmp.value(1).toString() != pwd){
        qDebug() << tmp.value(1).toString();
        QMessageBox::critical(this, QStringLiteral("错误"), QStringLiteral("用户名或密码错误"), QMessageBox::Ok);
        return;
    }
    QString user = ui->user_lineEdit->text();
    workerQuery *window = new workerQuery(user);
    close();
    window->show();
}
