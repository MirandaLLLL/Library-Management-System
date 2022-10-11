#ifndef READERMANAGEMENT_H
#define READERMANAGEMENT_H

#include <QWidget>
#include "ui_ReaderManagement.h"
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

namespace Ui {
class ReaderManagement;
}

class ReaderManagement : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderManagement(QSqlDatabase db,QWidget *parent = Q_NULLPTR);
    ~ReaderManagement();
    void Init();
private:
    Ui::ReaderManagement *ui;
    QPushButton* InsertBtn;
    QPushButton* UpdateBtn;
    QPushButton* DeleteBtn;
    QPushButton* Add_Ok;
    QPushButton* Delete_Ok;
    QPushButton* Update_Ok;

    QWidget * Addw;
    QWidget * Deletew;
    QWidget * Updatew;

    QLabel* canditionL;
    QLabel* reader_nameL;
    QLabel* reader_enterpriseL;
    QLabel* reader_typeL;
    QLabel* reader_logdateL;
    QLabel* readerIdL;

    QLineEdit* reader_name;
    QLineEdit* reader_enterprise;
    QLineEdit* reader_type;
    QLineEdit* readerId;


    QLabel* Auser_nameL;
    QLineEdit* Auser_name;
    QLabel* Auser_passwordL;
    QLineEdit* Auser_password;
    QLabel* AenterpriseL;
    QLineEdit* Aenterprise;
    QLabel* AtypeL;
    QLineEdit* Atype;

    QLabel* Uuser_IDL;
    QLineEdit* Uuser_ID;
    QLabel* Uuser_nameL;
    QLineEdit* Uuser_name;
    QLabel* UpasswordL;
    QLineEdit* Upassword;
    QLabel* UenterpriseL;
    QLineEdit* Uenterprise;
    QLabel* UtypeL;
    QLineEdit* Utype;

    QLabel* Duser_IDL;
    QLineEdit* Duser_ID;

    QPushButton* SearchBtn;
    QPushButton* DisplayAllbtn;
    //QPushButton* p1;

    QLabel* reader_name1L;
    QLabel* reader_enterprise1L;
    QLabel* reader_logdate1L;
    QLabel* reader_type1L;
    QLineEdit* reader_name1;
    QLineEdit* reader_enterprise1;
    QLineEdit* reader_logdate1;
    QLineEdit* reader_type1;

    QTableView* tableView;
    QSqlTableModel* model;
    QSqlDatabase db;
public slots:
    void Insertreaders();
    void Updatereaders();
    void Deletereaders();
    void Selectreaders();
    void DisplayAllreadrs();
    void Add_clicked();
    void Delete_clicked();
    void Update_clicked();

};

#endif // READERMANAGEMENT_H
