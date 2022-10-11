#ifndef USER_H
#define USER_H

#include <QWidget>
#include <QWidget>
#include "ui_User.h"
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include <QTableView>
#include <QSqlRecord>
#include <QScrollArea>

namespace Ui {
class User;
}

class User : public QWidget
{
    Q_OBJECT

public:
    explicit User(QSqlDatabase db,QWidget *parent = nullptr);
    ~User();
    void Init();

private:
    Ui::User *ui;
    QLabel* canditionL; //查询条件标签
    QLabel* book_IDL; //书名标签
    QLabel* book_typeL;  //作者标签
    QLabel* book_nameL;//出版社标签
    QLabel* book_authorL; //书名标签
    QLabel* book_pressL;  //作者标签
    QLabel* book_yearL;//出版社标签


    //对应标签的文本框
    QLineEdit* book_ID;
    QLineEdit* book_type;
    QLineEdit* book_name;
    QLineEdit* book_author;
    QLineEdit* book_press;
    QLineEdit* book_year;

    QPushButton* BorrowBtn; //借书按钮
    QPushButton* ReturnBtn; //还书按钮
    QPushButton* UpdtPwdBtn;//改变密码
    QPushButton* SearchBtn; //查询按钮
    QPushButton* DisplayAllbtn; //显示所有图书


    QLabel* borrow_reader_IDL;
    QLineEdit* borrow_reader_ID;
    QLabel* admin_IDL;
    QLineEdit* admin_ID;
    QLabel*Update_IDL;
    QLineEdit* Update_ID;
    QLabel*OriPwdL;
    QLineEdit* OriPwd;
    QLabel*NewPwdL;
    QLineEdit* NewPwd;

    QPushButton* Borrow_Ok;

    QLabel* return_reader_IDL;
    QLineEdit* return_reader_ID;
    QLabel* return_br_IDL;
    QLineEdit* return_br_ID;

    QPushButton* Return_Ok;
    QPushButton* Update_Ok;
    QPushButton* SelectBorrowBooks;

    //表格视图
    QTableView* tableView;
    //表格模板
    QSqlTableModel* model;

    //数据库对象
    QSqlDatabase db;

    QString username;
    QString password;

    QWidget* Brw; //借书界面
    QWidget* Rew; //还书界面
    QWidget* Upw; //修改密码

public slots:  //槽函数
    void Selectbooks();
    void DisplayAllbooks();
    void BorrowBooks(); //借书
    void ReturnBooks(); //还书
    void Borrow_clicked(); //借书响应
    void UpdatePwd();
    void SelectBorrowBooksList(); //查询个人所借图书
    void Return_clicked();  //还书响应
    void Update_clicked();
};

#endif // User_H
