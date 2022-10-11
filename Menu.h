#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include "ui_Menu.h"
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>

namespace Ui {
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    Menu(QSqlDatabase db,QWidget *parent = Q_NULLPTR);
    ~Menu();
    void Init();

private:
    Ui::Menu *ui;
    QPushButton* BookManage; //图书管理
    QPushButton* readerManage; //读者管理
    QPushButton* BrReManage; //借阅管理
    QPushButton* ExitSystem; //退出系统
    QPushButton* UpdtPwdBtn;//改变密码

    QLabel*Update_IDL;
    QLineEdit* Update_ID;
    QLabel*OriPwdL;
    QLineEdit* OriPwd;
    QLabel*NewPwdL;
    QLineEdit* NewPwd;

    QPushButton* Update_Ok;

    QSqlDatabase db; //数据库对象

    QWidget* Upw; //修改密码

private slots: //响应的槽函数
    void InitBookMangage();
    void InitReaderMangage();
    void InitBrReMangage();
    void UpdatePwd();
    void Update_clicked();
    void Exit();
};

#endif // MENU_H
