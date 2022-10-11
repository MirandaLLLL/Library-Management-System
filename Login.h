#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "ui_Login.h"
#include "Menu.h"
#include "User.h"
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QRadioButton>
#include <QTableView>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    //explicit Login(QWidget *parent = nullptr);
    Login(QWidget *parent = nullptr);
    ~Login();
    void Init(); //界面初始化
    bool ConnectSql(QString username, QString password); //连接数据库验证账号密码

private:
    Ui::Login *ui;
    QSqlDatabase db;
    QPushButton* pButton_OK, * pButton_cancel;
    QLabel* userNameLbl;         //"用户名"标签
    QLabel* pwdLbl;              //"密码"标签
    QLineEdit* userName;      //用户名编辑行
    QLineEdit* pwd;           //密码编辑行
    QPushButton* loginBtn_u;       //登录按钮
    QPushButton* loginBtn_a;
    QPushButton* registerBtn;    //注册按钮

    QTableView* tableView;
    QLabel* TitleLbl;


    QLabel* nameL;
    QLabel* enterpriseL;
    QLabel* typeL;
    QLabel* passwordL;
    QLabel* passwordAgainL;

    QLineEdit* name;
    QLineEdit* enterprise;
    QLineEdit* type;
    QLineEdit* password;
    QLineEdit* passwordAgain;

    QPushButton* Sure_Register;
    QWidget* rw;

    int judge=0;
    int n;
    int flag;
public slots:
    void login_u();//登录的槽函数
    void login_a();
    void Register();//注册
    void RegisterInfo(); //确认注册
};

#endif // LOGIN_H
