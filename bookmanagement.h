#ifndef BOOKMANAGEMENT_H
#define BOOKMANAGEMENT_H

#include <QWidget>
#include "ui_BookManagement.h"
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
#include <QAxObject>
#include "Menu.h"

namespace Ui {
class BookManagement;
}

class BookManagement : public QWidget
{
    Q_OBJECT

public:
    explicit BookManagement(QSqlDatabase db,QWidget *parent = Q_NULLPTR);
    ~BookManagement();
    void Init();

private:
    Ui::BookManagement *ui;
    QPushButton* InsertBtn; //新增按钮
    QPushButton* UpdateBtn; //修改按钮
    QPushButton* DeleteBtn; //删除按钮
    QPushButton* ReturnBtn; //返回菜单


    QLabel* canditionL; //查询条件标签
    QLabel* book_nameL; //书名标签
    QLabel* book_authorL;  //作者标签
    QLabel* book_pressL;//出版社标签
    QLabel* book_IDL;  //作者标签
    QLabel* book_typeL;
    QLabel* book_yearL;

        //对应标签的文本框
    QLineEdit* book_name;
    QLineEdit* book_author;
    QLineEdit* book_press;
    QLineEdit* book_ID;
    QLineEdit* book_type;
    QLineEdit* book_year;


        //查询按钮
    QPushButton* SearchBtn;
    QPushButton* DisplayAllbtn;

        //确定修改按钮
    //QPushButton *pSubmit,*pRevert;

        //表格视图
    QTableView* tableView;
        //表格模板
    QSqlTableModel *model;
        //数据库对象
    QSqlDatabase db;

    QWidget* Addw;
    QWidget* Deletew;
    QWidget* Updatew;

    QPushButton* Add_Ok;
    QLabel* Abook_IDL;
    QLineEdit* Abook_ID;
    QLabel* AtypeL;
    QLineEdit* Atype;
    QLabel* Abook_NAMEL;
    QLineEdit* Abook_NAME;
    QLabel* AauthorL;
    QLineEdit* Aauthor;
    QLabel* ApressL;
    QLineEdit* Apress;
    QLabel* AyearL;
    QLineEdit* Ayear;
    QLabel* ApriceL;
    QLineEdit* Aprice;
    QLabel* ATot_amtL;
    QLineEdit* ATot_amt;
    QLabel* AstockL;
    QLineEdit* Astock;

    QPushButton* Delete_Ok;
    QLabel* Dbook_IDL;
    QLineEdit* Dbook_ID;

    QPushButton* Batch_add;

    QPushButton* Update_Ok;
    QLabel* Ubook_IDL;
    QLineEdit* Ubook_ID;
    QLabel* UtypeL;
    QLineEdit* Utype;
    QLabel* Ubook_NAMEL;
    QLineEdit* Ubook_NAME;
    QLabel* UauthorL;
    QLineEdit* Uauthor;
    QLabel* UpressL;
    QLineEdit* Upress;
    QLabel* UyearL;
    QLineEdit* Uyear;
    QLabel* UpriceL;
    QLineEdit* Uprice;
    QLabel* UTot_amtL;
    QLineEdit* UTot_amt;
    QLabel* UstockL;
    QLineEdit* Ustock;

public slots:
    void Insertbooks();
    void Updatebooks();
    void Deletebooks();

    void Selectbooks();
    void DisplayAllbooks();

    void Add_clicked();
    void Update_clicked();
    void Delete_clicked();
    void Batch_clicked();

};

#endif // BOOKMANAGEMENT_H
