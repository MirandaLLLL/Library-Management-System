#ifndef BRREMANAGEMENT_H
#define BRREMANAGEMENT_H

#include <QWidget>
#include "ui_BrreManagement.h"
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
class BrReManagement;
}

class BrReManagement : public QWidget
{
    Q_OBJECT

public:
    explicit BrReManagement(QSqlDatabase db,QWidget *parent = Q_NULLPTR);
    ~BrReManagement();
    void Init();
private:
    Ui::BrReManagement *ui;
    QTableView* tableView; //视图
    QSqlTableModel* model; //表的模型
    QSqlDatabase db; //数据库对象

    QPushButton* BorrowBtn; //借书按钮
    QPushButton* ReturnBtn; //还书按钮
    QPushButton* UpdateBtn;
    QPushButton* DeleteBtn;

    QLabel* canditionL;
    QLabel* br_IDL;
    QLabel* reader_IDL;
    QLabel* book_IDL;
    QLabel* admin_IDL;


    QLineEdit* br_ID;
    QLineEdit* reader_ID;
    QLineEdit* book_ID;
    QLineEdit* admin_ID;

    QPushButton* SearchBtn;
    QPushButton* DisplayAllbtn;
    QPushButton* pSubmit, * pRevert; //提交和撤销按钮
    QPushButton* DisplayAllBookbtn;
    QPushButton *Borrow_Ok; //确认借书
    QPushButton* SelectBorrowBooks;
    QPushButton* Return_Ok; //确认还书

    QLabel* borrow_reader_IDL;
    QLineEdit* borrow_reader_ID;

    QLabel* return_br_IDL;
    QLabel* return_reader_IDL;
    QLineEdit* return_br_ID;
    QLineEdit* return_reader_ID;
    QLabel* Aadmin_IDL;
    QLineEdit* Aadmin_ID;


    QWidget* Brw; //借书界面
    QWidget* Rew; //还书界面

    QWidget* Addw;
    QWidget* Updatew;
    QWidget* Deletew;

    QPushButton* Add_Ok;
    QLabel* Abook_IDL;
    QLineEdit* Abook_ID;
    QLabel* Auser_IDL;
    QLineEdit* Auser_ID;
    QLabel* Aloan_dateL;
    QLineEdit* Aloan_date;
    QLabel* Aback_dateL;
    QLineEdit* Aback_date;
    QLabel* Aad_IDL;
    QLineEdit* Aad_ID;

    QPushButton* Delete_Ok;
    QLabel* Dbook_IDL;
    QLineEdit* Dbook_ID;
    QLabel* Duser_IDL;
    QLineEdit* Duser_ID;

    QPushButton* Update_Ok;
    QLabel* Ubook_IDL;
    QLineEdit* Ubook_ID;
    QLabel* Uuser_IDL;
    QLineEdit* Uuser_ID;
    QLabel* Uloan_dateL;
    QLineEdit* Uloan_date;
    QLabel* Uback_dateL;
    QLineEdit* Uback_date;
    QLabel* Uad_IDL;
    QLineEdit* Uad_ID;


public slots:  //槽函数
     void BorrowBooks(); //借书
     void ReturnBooks(); //还书
     void UpdateInfos();  //修改信息
     void DeleteInfos();  //删除信息
     void SelectInfos();  //查询信息
     void DisplayAllInfos(); //显示所有借阅信息
     void DisplayAllbooks(); //查询所有图书

     //void SureOk_clicked(); //确定修改事件
     //void Cancel_clicked(); //撤销修改事件
     void Borrow_clicked(); //借书响应
     void SelectBorrowBooksList(); //查询个人所借图书
     void Return_clicked();  //还书响应
     void Delete_clicked();
     //void Add_clicked();
     void Update_clicked();
};

#endif // BRREMANAGEMENT_H
