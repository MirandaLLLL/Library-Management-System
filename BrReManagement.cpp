#include "BrreManagement.h"
#include "ui_BrreManagement.h"
#include<QTableView>
#include<QHeaderView>

BrReManagement::BrReManagement(QSqlDatabase db,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BrReManagement)
{
    ui->setupUi(this);
    this->db = db;
}

BrReManagement::~BrReManagement()
{
    delete ui;
}

void BrReManagement::Init()
{
    QWidget* BrRew = new QWidget();
    BrRew->setProperty("class", "SumW");
    BrRew->setWindowTitle("Loan Management");
    QFont font;
    BrRew->resize(1920, 1080);
    tableView = new QTableView;//控制表格样式显示
    tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn); //垂直滚动条
    tableView->setProperty("class", "tableview");
    model = new QSqlTableModel(this);


    BorrowBtn =new QPushButton("Borrow books");
    BorrowBtn->setProperty("class", "FunctionBtn");
    ReturnBtn = new QPushButton("Return books");
    ReturnBtn->setProperty("class", "FunctionBtn");
    UpdateBtn= new QPushButton("Update records");
    UpdateBtn->setProperty("class", "FunctionBtn");
    DeleteBtn= new QPushButton("Delete records");
    DeleteBtn->setProperty("class", "FunctionBtn");
    BorrowBtn->setFixedSize(250,70);
    ReturnBtn->setFixedSize(250,70);
    UpdateBtn->setFixedSize(250,70);
    DeleteBtn->setFixedSize(250,70);

    canditionL= new QLabel("Key word:");
    canditionL->setProperty("class", "SumLabel");
    br_IDL= new QLabel("Book_ID");
    br_IDL->setProperty("class", "SumLabel");
    reader_IDL= new QLabel("User_ID");
    reader_IDL->setProperty("class", "SumLabel");
    Aadmin_IDL= new QLabel("Admin_ID");
    Aadmin_IDL->setProperty("class", "SumLabel");

    br_ID= new QLineEdit(this);
    br_ID->setPlaceholderText(tr("Book_ID"));
    br_ID->setFixedSize(200, 20);
    reader_ID= new QLineEdit(this);
    reader_ID->setPlaceholderText(tr("User_ID"));
    reader_ID->setFixedSize(200, 20);
    Aadmin_ID= new QLineEdit(this);
    Aadmin_ID->setPlaceholderText(tr("Admin_ID"));
    Aadmin_ID->setFixedSize(200, 20);

    SearchBtn = new QPushButton("Query");
    SearchBtn->setProperty("class", "SelectBtn");
    DisplayAllbtn = new QPushButton("All records");
    DisplayAllbtn->setProperty("class", "SelectBtn");
    DisplayAllBookbtn = new QPushButton("All books");
    DisplayAllBookbtn->setProperty("class", "SelectBtn");
    SearchBtn->setFixedSize(80, 25);
    DisplayAllbtn->setFixedSize(120,25);
    DisplayAllBookbtn->setFixedSize(120,25);


    font.setPointSize(15);
    BorrowBtn->setFont(font);//字体大小
    ReturnBtn->setFont(font);
    UpdateBtn->setFont(font);
    DeleteBtn->setFont(font);

    QGridLayout* pQ = new QGridLayout; //布局
    pQ->addWidget(BorrowBtn, 2, 8, 2, 2);
    pQ->addWidget(ReturnBtn, 4, 8, 2, 2);
    pQ->addWidget(UpdateBtn, 6, 8, 2, 2);
    pQ->addWidget(DeleteBtn, 8, 8, 2, 2);

    pQ->addWidget(canditionL, 0, 0, 1, 1);
    pQ->addWidget(br_IDL, 0, 1, 1, 1, Qt::AlignRight);
    pQ->addWidget(br_ID, 0, 2, 1, 1);
    pQ->addWidget(reader_IDL, 0, 3, 1, 1,Qt::AlignRight);
    pQ->addWidget(reader_ID, 0, 4, 1, 1);
    pQ->addWidget(Aadmin_IDL, 0, 5, 1, 1,Qt::AlignRight);
    pQ->addWidget(Aadmin_ID, 0, 6, 1, 1);

    pQ->addWidget(SearchBtn, 0, 7, 1, 1);
    pQ->addWidget(DisplayAllbtn, 0, 8, 1, 1);
    pQ->addWidget(DisplayAllBookbtn, 0, 9, 1, 1);
    pQ->addWidget(tableView, 1, 0, 10, 8);

    BrRew->setLayout(pQ);
    BrRew->show();

    connect(BorrowBtn, SIGNAL(clicked()), this, SLOT(BorrowBooks()));
    connect(ReturnBtn, SIGNAL(clicked()), this, SLOT(ReturnBooks()));
    connect(UpdateBtn, SIGNAL(clicked()), this, SLOT(UpdateInfos()));
    connect(DeleteBtn, SIGNAL(clicked()), this, SLOT(DeleteInfos()));
    connect(SearchBtn, SIGNAL(clicked()), this, SLOT(SelectInfos()));
    connect(DisplayAllbtn, SIGNAL(clicked()), this, SLOT(DisplayAllInfos()));
    connect(DisplayAllBookbtn, SIGNAL(clicked()), this, SLOT(DisplayAllbooks()));

}

void BrReManagement::BorrowBooks() //借书
{
    //this->DisplayAllbooks();

    Brw = new QWidget();
    Brw->setProperty("class", "RegisterPage");
    Brw->setWindowTitle("borrow_page");
    Brw->setMinimumSize(500, 600);
    Brw->setMaximumSize(600, 720);

    borrow_reader_IDL = new QLabel("Input your User_ID");
    borrow_reader_IDL->setProperty("class", "RegisterLbl");
    borrow_reader_ID = new QLineEdit(this);
    admin_IDL= new QLabel("Input Admin ID");
    admin_IDL->setProperty("class", "RegisterLbl");
    admin_ID= new QLineEdit(this);
    //borrow_DATEL= new QLabel("Input borrow date");
    //borrow_DATE= new QLineEdit(this);
    book_IDL = new QLabel("Input book_ID：");
    book_IDL->setProperty("class", "RegisterLbl");
    book_ID = new QLineEdit(this);

    borrow_reader_ID->setPlaceholderText(tr("User_ID"));
    borrow_reader_ID->setProperty("class", "QLineEdit1");
    book_ID->setPlaceholderText(tr("Book_ID"));
    book_ID->setProperty("class", "QLineEdit1");
    admin_ID->setPlaceholderText(tr("Admin_ID"));
    admin_ID->setProperty("class", "QLineEdit1");


    Borrow_Ok = new QPushButton("Comfirm to borrow");
    Borrow_Ok->setProperty("class", "RegisterBtn");
    Borrow_Ok->setFixedSize(220, 50);

    QGridLayout* pG = new QGridLayout; //布局
    pG->addWidget(borrow_reader_IDL, 1, 0, 1, 1);
    pG->addWidget(borrow_reader_ID, 1, 1, 1, 1);
    pG->addWidget(admin_IDL, 2, 0, 1, 1);
    pG->addWidget(admin_ID, 2, 1, 1, 1);
    pG->addWidget(book_IDL, 3, 0, 1, 1);
    pG->addWidget(book_ID, 3, 1, 1, 1);
    pG->addWidget(Borrow_Ok, 4, 1, 1, 1);

    Brw->setLayout(pG);
    Brw->show();

    //用户输入信息后需要判断信息准确性
    connect(Borrow_Ok, SIGNAL(clicked()), this, SLOT(Borrow_clicked()));

}
void BrReManagement::ReturnBooks()//还书
{
    Rew = new QWidget();
    Rew->setProperty("class", "RegisterPage");
    Rew->setWindowTitle("return_page");
    Rew->setMinimumSize(500, 600);
    Rew->setMaximumSize(500, 600);
    Return_Ok = new QPushButton("confirm to return");
    Return_Ok->setProperty("class", "RegisterBtn");
    Return_Ok->setFixedSize(200, 50);
    SelectBorrowBooks = new QPushButton("borrowed books");
    SelectBorrowBooks->setProperty("class", "RegisterBtn");
    SelectBorrowBooks->setFixedSize(200, 50);

    return_reader_IDL = new QLabel("User ID");
    return_reader_IDL->setProperty("class", "RegisterLbl");
    return_reader_ID= new QLineEdit(this);
    return_reader_ID->setPlaceholderText(tr("User ID"));
    return_reader_ID->setProperty("class", "QLineEdit1");

    return_br_IDL = new QLabel("Input book_ID");
    return_br_IDL->setProperty("class", "RegisterLbl");
    return_br_ID = new QLineEdit(this);
    return_br_ID->setPlaceholderText(tr("book_ID"));
    return_br_ID->setProperty("class", "QLineEdit1");



    QGridLayout* pG = new QGridLayout; //布局
    pG->addWidget(return_reader_IDL, 1, 0, 1, 1,Qt::AlignRight);
    pG->addWidget(return_reader_ID, 1, 1, 1, 1);
    pG->addWidget(SelectBorrowBooks, 2, 1, 1, 1);
    pG->addWidget(return_br_IDL, 3, 0, 1, 1);
    pG->addWidget(return_br_ID, 3, 1, 1, 1);
    pG->addWidget(Return_Ok, 4, 1, 1, 1);

    Rew->setLayout(pG);
    Rew->show();

    connect(SelectBorrowBooks, SIGNAL(clicked()), this, SLOT(SelectBorrowBooksList()));
    connect(Return_Ok, SIGNAL(clicked()), this, SLOT(Return_clicked()));

}

void BrReManagement::UpdateInfos()//修改信息
{
    Updatew = new QWidget();
    Updatew->setProperty("class", "RegisterPage");
    Updatew->setWindowTitle("Update_page");
    Updatew->setMinimumSize(600, 800);
    Updatew->setMaximumSize(600, 800);
    Update_Ok = new QPushButton("confirm to update");
    Update_Ok->setProperty("class", "RegisterBtn");
    Update_Ok->setFixedSize(200, 50);

    Ubook_IDL = new QLabel("book_ID");
    Ubook_IDL->setProperty("class", "RegisterLbl");
    Ubook_ID = new QLineEdit(this);
    Ubook_ID->setPlaceholderText(tr("input book ID you want to update"));
    Ubook_ID->setProperty("class", "QLineEdit1");

    Uuser_IDL = new QLabel("User_ID");
    Uuser_IDL->setProperty("class", "RegisterLbl");
    Uuser_ID = new QLineEdit(this);
    Uuser_ID->setPlaceholderText(tr("input user ID you want to update"));
    Uuser_ID->setProperty("class", "QLineEdit1");

    Uloan_dateL = new QLabel("Loan_date");
    Uloan_dateL->setProperty("class", "RegisterLbl");
    Uloan_date = new QLineEdit(this);
    Uloan_date->setPlaceholderText(tr("Loan_date"));
    Uloan_date->setProperty("class", "QLineEdit1");

    Uback_dateL = new QLabel("Back_date");
    Uback_dateL->setProperty("class", "RegisterLbl");
    Uback_date = new QLineEdit(this);
    Uback_date->setPlaceholderText(tr("Back_date"));
    Uback_date->setProperty("class", "QLineEdit1");

    Uad_IDL = new QLabel("Admin_ID");
    Uad_IDL->setProperty("class", "RegisterLbl");
    Uad_ID = new QLineEdit(this);
    Uad_ID->setPlaceholderText(tr("Admin_ID"));
    Uad_ID->setProperty("class", "QLineEdit1");

    QGridLayout* pG = new QGridLayout; //布局
    pG->addWidget(Ubook_IDL, 1, 0, 1, 1);
    pG->addWidget(Ubook_ID, 1, 1, 1, 1);
    pG->addWidget(Uuser_IDL, 2, 0, 1, 1);
    pG->addWidget(Uuser_ID, 2, 1, 1, 1);
    pG->addWidget(Uloan_dateL, 3, 0, 1, 1);
    pG->addWidget(Uloan_date, 3, 1, 1, 1);
    pG->addWidget(Uback_dateL, 4, 0, 1, 1);
    pG->addWidget(Uback_date, 4, 1, 1, 1);
    pG->addWidget(Uad_IDL, 5, 0, 1, 1);
    pG->addWidget(Uad_ID, 5, 1, 1, 1);
    pG->addWidget(Update_Ok, 6, 1, 1, 1);

    Updatew->setLayout(pG);
    Updatew->show();


    connect(Update_Ok, SIGNAL(clicked()), this, SLOT(Update_clicked()));
}

void BrReManagement::Update_clicked()
{
    //如果输入信息为空，则提示用户输入信息
    if (Ubook_ID->text().trimmed() == ""||Uuser_ID->text().trimmed() == "")
    {
        QMessageBox::information(this, "warning", "please input the ID");
        return;
    }



    QSqlQuery myQuery(db);
    if (Uloan_date->text().trimmed() != ""){
        QString str_sql = "update loan_record set loan_date='" + Uloan_date->text().trimmed()+"' where book_ID='"+Ubook_ID->text().trimmed()+"' and user_ID='"+Uuser_ID->text().trimmed()+"'";
        myQuery.exec(str_sql);
    }

    if (Uback_date->text().trimmed() != ""){
        QString str_sql = "update loan_record set back_date='" + Uback_date->text().trimmed()+"' where book_ID='"+Ubook_ID->text().trimmed()+"' and user_ID='"+Uuser_ID->text().trimmed()+"'";
        myQuery.exec(str_sql);
    }

    if (Uad_ID->text().trimmed() != ""){
        QString str_sql = "update loan_record set fal_ID='" + Uad_ID->text().trimmed()+"' where book_ID='"+Ubook_ID->text().trimmed()+"' and user_ID='"+Uuser_ID->text().trimmed()+"'";
        myQuery.exec(str_sql);
    }

    QMessageBox::information(this, "", "Update successfully");
    Updatew->close();
    delete Updatew;
    return;
}


void BrReManagement::DeleteInfos()//删除信息
{
    Deletew = new QWidget();
    Deletew->setProperty("class", "RegisterPage");
    Deletew->setWindowTitle("Delete_page");
    Deletew->setMinimumSize(400, 400);
    Deletew->setMaximumSize(400, 400);
    Delete_Ok = new QPushButton("confirm to delete");
    Delete_Ok->setProperty("class", "RegisterBtn");
    Delete_Ok->setFixedSize(200, 50);

    Dbook_IDL = new QLabel("Input book_ID:");
    Dbook_IDL->setProperty("class", "RegisterLbl");
    Dbook_ID = new QLineEdit(this);
    Dbook_ID->setPlaceholderText(tr("book_ID"));
    Dbook_ID->setProperty("class", "QLineEdit1");
    Duser_IDL = new QLabel("Input user_ID:");
    Duser_IDL->setProperty("class", "RegisterLbl");
    Duser_ID = new QLineEdit(this);
    Duser_ID->setPlaceholderText(tr("user_ID"));
    Duser_ID->setProperty("class", "QLineEdit1");

    QGridLayout* pG = new QGridLayout;

    pG->addWidget(Duser_IDL, 0, 0, 1, 1);
    pG->addWidget(Duser_ID, 0, 1, 1, 1);
    pG->addWidget(Dbook_IDL, 1, 0, 1, 1);
    pG->addWidget(Dbook_ID, 1, 1, 1, 1);
    pG->addWidget(Delete_Ok, 2, 1, 1, 1);

    Deletew->setLayout(pG);
    Deletew->show();

    connect(Delete_Ok, SIGNAL(clicked()), this, SLOT(Delete_clicked()));
}

void BrReManagement::Delete_clicked(){
    if (Dbook_ID->text().trimmed() == "")
    {
        QMessageBox::information(this, "warning", "please input the ID");
        return;
    }


    QSqlQuery myQuery(db);
    QString str_sql = "delete from loan_record where book_ID='" + Dbook_ID->text().trimmed()+"' and user_ID='"+Duser_ID->text().trimmed()+"'";
    myQuery.exec(str_sql);


    QMessageBox::information(this, "", "Delete successfully");
    Deletew->close();
    delete Deletew;
    return;
}


void BrReManagement::SelectInfos() //查询信息
{
    QSqlQueryModel* model = new QSqlQueryModel(this);
    QString str_sql = "select * from loan_record where user_ID like '%" + reader_ID->text().trimmed()+"%' and \
            fal_ID like '%" + Aadmin_ID->text().trimmed() + "%' and \
            book_ID like '%" + br_ID->text().trimmed() + "%'";

    if (br_ID->text().trimmed() == "" && reader_ID->text().trimmed() == ""&& Aadmin_ID->text().trimmed() == "")
    {
        QMessageBox::information(this, "query", "You do not input information,please try again");
        return;
    }

    int count = 0;
    QSqlQuery myQuery(db);
    if (myQuery.exec(str_sql))
    {
        while (myQuery.next())//遍历数据表格每一行，从第0行到最后一行
        {
            count++;
        }
    }
    if (count == 0)
    {
        QMessageBox::information(this, "", "There is no matching record, please try again");
        return;
    }

    model->setQuery(str_sql); //查询
    model->setHeaderData(0, Qt::Horizontal, tr("book_ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("user_ID"));
    model->setHeaderData(2, Qt::Horizontal, tr("loan_date"));
    model->setHeaderData(3, Qt::Horizontal, tr("back_date"));
    model->setHeaderData(4, Qt::Horizontal, tr("fal_ID"));

    this->tableView->setModel(model);//数据放置进去
    this->tableView->verticalHeader()->hide();//不显示序号
    this->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //表的列宽均匀充满空间
    tableView->show();


    reader_ID->clear();
    br_ID->clear();
}


void BrReManagement::DisplayAllInfos() //显示所有借阅信息
{
    QSqlQueryModel* model = new QSqlQueryModel(this);

    QString str_sql = "select * from loan_record";

    model->setQuery(str_sql);

    model->setHeaderData(0, Qt::Horizontal, tr("book_ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("user_ID"));
    model->setHeaderData(2, Qt::Horizontal, tr("loan_date"));
    model->setHeaderData(3, Qt::Horizontal, tr("back_date"));
    model->setHeaderData(4, Qt::Horizontal, tr("fal_ID"));

    this->tableView->setModel(model);//数据放置进去
    this->tableView->verticalHeader()->hide();//不显示序号
    this->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //表的列宽均匀充满空间
    tableView->show();
}

void BrReManagement::DisplayAllbooks() //查询所有图书
{
    QSqlQueryModel* model = new QSqlQueryModel(this);

    model->setQuery("select * from book order by book_ID asc LIMIT 50");
    model->setHeaderData(0, Qt::Horizontal, tr("Book_ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("type"));
    model->setHeaderData(2, Qt::Horizontal, tr("name"));
    model->setHeaderData(3, Qt::Horizontal, tr("author"));
    model->setHeaderData(4, Qt::Horizontal, tr("press"));
    model->setHeaderData(5, Qt::Horizontal, tr("year"));
    model->setHeaderData(6, Qt::Horizontal, tr("price"));
    model->setHeaderData(7, Qt::Horizontal, tr("total amount"));
    model->setHeaderData(8, Qt::Horizontal, tr("stock"));
    this->tableView->setModel(model);//数据放置进去
    this->tableView->verticalHeader()->hide();//不显示序号
    this->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //表的列宽均匀充满空间
    tableView->show();

}



void BrReManagement::Borrow_clicked() //确定借书
{


    //如果输入信息为空，则提示用户输入信息
    if (borrow_reader_ID->text().trimmed() == "" || book_ID->text().trimmed() == "")
    {
        QMessageBox::information(this, "query", "your information is incomplete, please try again");
        return;
    }


    //如果用户ID不存在,停止借书操作
    int count = 0;
    QSqlQuery myQuery(db);
    QString str_sql = "select user_ID from user_card where user_ID='" + borrow_reader_ID->text().trimmed() + "'";
    if (myQuery.exec(str_sql))
    {
        while (myQuery.next())//遍历结果集每一行，从第0行到最后一行
        {
            ++count;
        }

        if (count == 0) //如果查询的读者不在结果集中，返回记录为空
        {
            QMessageBox::information(this, "", "Sorry, your ID is not valid");
            Brw->close();
            delete Brw;
            return;
        }

    }

    //如果用户输入的图书ID不存在,停止借书操作
    count = 0;
    str_sql = "select book_ID from book where book_ID='" + book_ID->text().trimmed()+"'";
    if (myQuery.exec(str_sql))
    {
        while (myQuery.next())//遍历结果集每一行，从第0行到最后一行
        {
            ++count;
        }

        if (count == 0) //如果图书ID不在结果集中，返回记录为空
        {
            QMessageBox::information(this, "", "book_ID is not valid");
            return;
        }

    }

    //首先判断用户借书数量是否超出上限,超过则中断借书操作
    //还书时间判空，如果为空表示未还书
    count = 0;
    str_sql = "select * from loan_record \
                where back_date IS NULL and\
                user_ID=(select user_ID from user_card where user_ID='" + borrow_reader_ID->text().trimmed() + "')";
    if (myQuery.exec(str_sql))
    {
        while (myQuery.next())//遍历结果集每一行，从第0行到最后一行
        {
            ++count;
        }
    }

    if (count >= 5) //借书最多五本
    {
        QMessageBox::information(this, "", "You have borrowed 5 books, please borrow after returning the books");
        Brw->close();
        delete Brw;
        return;
    }

    //如果书的库存为0，系统提示无法借此书
    str_sql = "select stock from book where book_ID='" + book_ID->text().trimmed()+"'";
    if (myQuery.exec(str_sql))
    {
        while (myQuery.next())//遍历结果集每一行，从第0行到最后一行
        {
            if (0 == myQuery.value(0)) {
                QMessageBox::information(this, "", "Sorry, we have no stocks");
                return;
            }
        }
    }


    //根据姓名查找读者id，再将读者id和书的id增添到借阅记录中

    str_sql = "insert into loan_record(book_ID,user_ID,loan_date,fal_ID) values('" +book_ID->text()+"','"+borrow_reader_ID->text()+"',Now(),'"+admin_ID->text()+"')";
    myQuery.exec(str_sql);


    //借书后，相应的图书库存减1
    str_sql = "update book set stock=stock-1 where book_ID='" + book_ID->text().trimmed()+"'";
    myQuery.exec(str_sql);
    QMessageBox::information(this, "", "Borrow successfully");
    Brw->close();
    delete Brw;
    return;
}

void BrReManagement::SelectBorrowBooksList() //查询个人所借图书
{
    //如果输入信息为空，则提示用户输入信息
    if (return_reader_ID->text().trimmed() == "")
    {
        QMessageBox::information(this, "query", "you do not input information, please try again");
        return;
    }


    //根据用户输入的名字找到其借书记录,而且是还书时间为空的记录
    QSqlQueryModel* model = new QSqlQueryModel(this);
    QString str_sql = "select * from loan_record where user_ID='" + return_reader_ID->text().trimmed() + "' and back_date IS NULL";
    int count = 0;
    QSqlQuery myQuery(db);
    if (myQuery.exec(str_sql))
    {
        while (myQuery.next())//遍历数据表格每一行，从第0行到最后一行
        {
            count++;
        }
    }
    if (count == 0)
    {
        QMessageBox::information(this, "", "You have returned all the books or the input information is wrong");
        return;
    }


    model->setQuery(str_sql); //查询
    model->setHeaderData(0, Qt::Horizontal, tr("book_ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("user_ID"));
    model->setHeaderData(2, Qt::Horizontal, tr("loan_date"));
    model->setHeaderData(3, Qt::Horizontal, tr("back_date"));
    model->setHeaderData(4, Qt::Horizontal, tr("Admin_ID"));

    this->tableView->setModel(model);//数据放置进去
    this->tableView->verticalHeader()->hide();//不显示序号
    this->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //表的列宽均匀充满空间
    tableView->show();

    return_reader_ID->clear();
}

void BrReManagement::Return_clicked() //还书响应
{
    //如果输入信息为空，则提示用户输入信息
    if (return_br_ID->text().trimmed() == "")
    {
        QMessageBox::information(this, "return_back", "you do not input any information, please try again");
        return;
    }


    //用户还书后系统修改对应的还书时间为当前时间

    QSqlQuery myQuery(db);
    QString str_sql = "update loan_record set back_date=Now() where user_ID='" + return_reader_ID->text().trimmed()+"'";
    myQuery.exec(str_sql);

    //根据用户输入的br_re id号,锁定对应的图书,使图书库存加1
    str_sql = "update book,loan_record set stock=stock+1 where \
                loan_record.book_ID=book.book_ID and user_ID='" + return_br_ID->text().trimmed()+"'";
    myQuery.exec(str_sql);
    QMessageBox::information(this, "", "Return successfully");
    Rew->close();
    delete Rew;
    return;
}
