#include "User.h"
#include "ui_User.h"
#include<QHeaderView>
User::User(QSqlDatabase db,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::User)
{
    ui->setupUi(this);
    this->db = db;
}

User::~User()
{
    delete ui;
}
void User::Init()
{
    QWidget* Userw = new QWidget();
    Userw->setProperty("class", "SumW");
    Userw->setWindowTitle("User page");
    QFont font;
    Userw->resize(1920, 1080);
    tableView = new QTableView;//控制表格样式显示
    tableView->setProperty("class", "tableview"); //声明类选择器
    tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn); //表格的垂直滚动条
    model = new QSqlTableModel(this); //表格模板初始化



    QGridLayout* pQ = new QGridLayout; //网格布局

    font.setPointSize(15);    //设置字体大小
    canditionL = new QLabel("key");
    canditionL->setProperty("class", "SumLabel");
    book_IDL = new QLabel("ID");
    book_IDL->setProperty("class", "SumLabel");
    book_nameL = new QLabel("NAME");
    book_nameL->setProperty("class", "SumLabel");
    book_typeL = new QLabel("TYPE");
    book_typeL->setProperty("class", "SumLabel");
    book_authorL = new QLabel("AUTHOR");
    book_authorL->setProperty("class", "SumLabel");
    book_pressL = new QLabel("PRESS");
    book_pressL->setProperty("class", "SumLabel");
    book_yearL = new QLabel("YEAR");
    book_yearL->setProperty("class", "SumLabel");

    book_ID = new QLineEdit(this);
    book_ID->setPlaceholderText(tr("ID"));
    book_name = new QLineEdit(this);
    book_name->setPlaceholderText(tr("Name"));
    book_type = new QLineEdit(this);
    book_type->setPlaceholderText(tr("Type"));
    book_author = new QLineEdit(this);
    book_author->setPlaceholderText(tr("Author"));
    book_press = new QLineEdit(this);
    book_press->setPlaceholderText(tr("Press"));
    book_year = new QLineEdit(this);
    book_year->setPlaceholderText(tr("Year"));

    SearchBtn = new QPushButton("Query");
    SearchBtn->setFixedSize(80, 25);
    SearchBtn->setProperty("class", "SelectBtn");
    DisplayAllbtn = new QPushButton("Display all");
    DisplayAllbtn->setFixedSize(120,25);
    DisplayAllbtn->setProperty("class", "SelectBtn");

    BorrowBtn = new QPushButton("Borrow");
    BorrowBtn->setFont(font);
    BorrowBtn->setProperty("class", "FunctionBtn");
    ReturnBtn = new QPushButton("Return");
    ReturnBtn->setFont(font);
    ReturnBtn->setProperty("class", "FunctionBtn");
    BorrowBtn->setFixedSize(250,70);
    ReturnBtn->setFixedSize(250,70);
    UpdtPwdBtn = new QPushButton("Update Password");
    UpdtPwdBtn->setFont(font);
    UpdtPwdBtn->setProperty("class", "FunctionBtn");
    UpdtPwdBtn->setFixedSize(250,70);

    pQ->addWidget(canditionL, 0, 0, 1, 1);
    pQ->addWidget(book_IDL, 0, 1, 1, 1);
    pQ->addWidget(book_ID, 0, 2, 1, 1);
    pQ->addWidget(book_nameL, 0, 3, 1, 1);
    pQ->addWidget(book_name, 0, 4, 1, 1);
    pQ->addWidget(book_typeL, 0, 5, 1, 1);
    pQ->addWidget(book_type, 0, 6, 1, 1);
    pQ->addWidget(book_authorL, 0, 7, 1, 1);
    pQ->addWidget(book_author, 0, 8, 1, 1);
    pQ->addWidget(book_pressL, 0, 9, 1, 1);
    pQ->addWidget(book_press, 0, 10, 1, 1);
    pQ->addWidget(book_yearL, 0, 11, 1, 1);
    pQ->addWidget(book_year, 0, 12, 1, 1);
    pQ->addWidget(SearchBtn, 0, 13, 1, 1);
    pQ->addWidget(DisplayAllbtn, 0, 14, 1, 1);
    pQ->addWidget(tableView, 1, 0, 24, 10);


    pQ->addWidget(BorrowBtn, 4, 11, 2, 2);
    pQ->addWidget(ReturnBtn, 8, 11, 2, 2);
    pQ->addWidget(UpdtPwdBtn, 12, 11, 2, 2);

    Userw->setLayout(pQ);
    Userw->show();


    connect(BorrowBtn, SIGNAL(clicked()), this, SLOT(BorrowBooks()));
    connect(ReturnBtn, SIGNAL(clicked()), this, SLOT(ReturnBooks()));
    connect(UpdtPwdBtn, SIGNAL(clicked()), this, SLOT(UpdatePwd()));
    connect(SearchBtn, SIGNAL(clicked()), this, SLOT(Selectbooks()));
    connect(DisplayAllbtn, SIGNAL(clicked()), this, SLOT(DisplayAllbooks()));

}

void User::UpdatePwd()
{
    Upw = new QWidget();
    Upw->setProperty("class", "RegisterPage");
    Upw->setWindowTitle("Update password");
    Upw->setMinimumSize(500, 600);
    Upw->setMaximumSize(600, 720);

    Update_IDL = new QLabel("Input User_ID");
    Update_ID = new QLineEdit(this);
    OriPwdL= new QLabel("Input original password");
    OriPwd= new QLineEdit(this);
    OriPwd->setEchoMode(QLineEdit::Password);
    NewPwdL = new QLabel("Input New password");
    NewPwd = new QLineEdit(this);
    NewPwd->setEchoMode(QLineEdit::Password);

    Update_ID->setPlaceholderText(tr("User_ID"));
    Update_ID->setProperty("class", "QLineEdit1");
    OriPwd->setPlaceholderText(tr("Original password"));
    OriPwd->setProperty("class", "QLineEdit1");
    NewPwd->setPlaceholderText(tr("New password"));
    NewPwd->setProperty("class", "QLineEdit1");

    Update_Ok = new QPushButton("Comfirm to borrow");
    Update_Ok->setProperty("class", "RegisterBtn");
    Update_Ok->setFixedSize(220, 50);

    Update_IDL->setProperty("class","RegisterLbl");
    OriPwdL->setProperty("class","RegisterLbl");
    NewPwdL->setProperty("class","RegisterLbl");

    QGridLayout* pG = new QGridLayout; //布局
    pG->addWidget(Update_IDL, 1, 0, 1, 1);
    pG->addWidget(Update_ID, 1, 1, 1, 1);
    pG->addWidget(OriPwdL, 2, 0, 1, 1);
    pG->addWidget(OriPwd, 2, 1, 1, 1);
    pG->addWidget(NewPwdL, 3, 0, 1, 1);
    pG->addWidget(NewPwd, 3, 1, 1, 1);
    pG->addWidget(Update_Ok, 4, 1, 1, 1);

    Upw->setLayout(pG);
    Upw->show();


    //用户输入信息后需要判断信息准确性
    connect(Update_Ok, SIGNAL(clicked()), this, SLOT(Update_clicked()));
}

void User::Update_clicked() //修改密码
{

    //如果输入信息为空，则提示用户输入信息
    if (Update_ID->text().trimmed() == ""||OriPwd->text().trimmed() == ""||NewPwd->text().trimmed() == "")
    {
        QMessageBox::information(this, "Warning", "Please input the information");
        return;
    }

    QSqlQuery myQuery(db);



    QString username=Update_ID->text();
    QString password=OriPwd->text();
    QString str_sql1 = "select * from user_card where user_ID='"  //用户登录从读者表中找到姓名和密码
        + username
       +"'and user_password='"
        + password
        + "'";
     int judge=0;

    if (myQuery.exec(str_sql1))
                {
                    while (myQuery.next())//遍历数据表格每一行，从第0行到最后一行
                    {
                        //获取读者表中的姓名密码
                        QString user = myQuery.value(0).toString();
                        QString pwd = myQuery.value(2).toString();

                        if (username == user && password == pwd) //与用户输入的姓名密码比对
                        {
                            judge=1;
                           QMessageBox::information(this, "Log", "Log in successfully");
                           int n = 0;
                           for (int i = 0;i < NewPwd->text().trimmed().length();i++)
                           {
                               n++;
                           }
                           if (n < 6)
                           {
                               QMessageBox::information(this, "", "your new password need to be no less than 6 digits");
                               return;
                           }

                           QString str_sql = "update user_card set user_password='"+NewPwd->text().trimmed()+"' where user_ID='" + Update_ID->text().trimmed()+"'";
                           myQuery.exec(str_sql);
                           QMessageBox::information(this, "", "Update successfully");
                           Upw->close();
                           delete Upw;
                           return;
                        }

                    }
                    if(judge==0){
                         QMessageBox::information(this, "warning", "wrong username or password");
             }
     }


}


void User::Selectbooks() //查询图书
{
    QSqlQueryModel* model = new QSqlQueryModel(this);
    QString str_sql = "select * from book where book_ID like '%" + book_ID->text().trimmed() + "%' and \
                        book_name like '%" + book_name->text().trimmed() + "%' and \
                        book_type like '%" + book_type->text().trimmed() + "%' and \
                        author like '%" + book_author->text().trimmed() + "%' and \
                        year like '%" + book_year->text().trimmed() + "%' and \
                        press like '%" + book_press->text().trimmed() + "%'";

    if (book_name->text().trimmed() == "" && book_type->text().trimmed() == ""&& book_ID->text().trimmed() == ""&& book_year->text().trimmed() == ""&& book_author->text().trimmed() == "" && book_press->text().trimmed() == "")
    {
        QMessageBox::information(this, "query", "you do not input the conditions");
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
    if (count == 0)  //如果查询的结果集为空，提示用户重新输入条件
    {
        QMessageBox::information(this, "", "there is no record matching your conditions");
        return;
    }


    model->setQuery(str_sql); //执行查询

                              //设置表头列名
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("NAME"));
    model->setHeaderData(2, Qt::Horizontal, tr("TYPE"));
    model->setHeaderData(3, Qt::Horizontal, tr("AUTHOR"));
    model->setHeaderData(4, Qt::Horizontal, tr("PRESS"));
    model->setHeaderData(5, Qt::Horizontal, tr("YEAR"));
    model->setHeaderData(6, Qt::Horizontal, tr("PRICE"));
    model->setHeaderData(7, Qt::Horizontal, tr("TOT AMT"));
    model->setHeaderData(8, Qt::Horizontal, tr("STOCK"));
    this->tableView->setModel(model);//数据放置进去
    this->tableView->verticalHeader()->hide();//不显示序号
    this->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //表的列宽均匀充满空间
    tableView->show();

    book_name->clear(); //清空输入内容
    book_author->clear();
    book_press->clear();
    book_ID->clear(); //清空输入内容
    book_year->clear();
    book_type->clear();

}

void User::DisplayAllbooks()
{

    QSqlQueryModel* model = new QSqlQueryModel(this);
    model->setQuery("select * from book");
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("TYPE"));
    model->setHeaderData(2, Qt::Horizontal, tr("NAME"));
    model->setHeaderData(4, Qt::Horizontal, tr("AUTHOR"));
    model->setHeaderData(5, Qt::Horizontal, tr("PRESS"));
    model->setHeaderData(7, Qt::Horizontal, tr("YEAR"));
    model->setHeaderData(8, Qt::Horizontal, tr("PRICE"));
    model->setHeaderData(9, Qt::Horizontal, tr("TOT AMT"));
    model->setHeaderData(10, Qt::Horizontal, tr("STOCK"));
    this->tableView->setModel(model);//数据放置进去
    this->tableView->verticalHeader()->hide();//不显示序号
    //this->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //表的列宽均匀充满空间
    tableView->show();

}
void User::BorrowBooks() //借书
{
    //用户可先查看书信息
    //再输入个人姓名和书的ID号完成借书
    this->DisplayAllbooks();

    Brw = new QWidget();
    Brw->setProperty("class", "RegisterPage");
    Brw->setWindowTitle("borrow_page");
    Brw->setMinimumSize(500, 600);
    Brw->setMaximumSize(600, 720);

    borrow_reader_IDL = new QLabel("Input your User_ID");
    borrow_reader_ID = new QLineEdit(this);
    admin_IDL= new QLabel("Input Admin ID");
    admin_ID= new QLineEdit(this);
    book_IDL = new QLabel("Input book_ID：");
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

    borrow_reader_IDL->setProperty("class","RegisterLbl");
    admin_IDL->setProperty("class","RegisterLbl");
    book_IDL->setProperty("class","RegisterLbl");

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
void User::Borrow_clicked()//借书响应
{
    //如果输入信息为空，则提示用户输入信息
    if (borrow_reader_ID->text().trimmed() == "" || book_ID->text().trimmed() == "")
    {
        QMessageBox::information(this, "query", "your information is incomplete, please try again");
        return;
    }


    //如果用户输入的姓名不存在,停止借书操作
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

void User::ReturnBooks() //还书
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

    return_reader_IDL = new QLabel("User_ID");
    return_reader_ID = new QLineEdit(this);
    return_reader_ID->setPlaceholderText(tr("User_ID"));
    return_reader_ID->setProperty("class", "QLineEdit1");

    return_br_IDL = new QLabel("book_ID");
    return_br_ID = new QLineEdit(this);
    return_br_ID->setPlaceholderText(tr("book_ID"));
    return_br_ID->setProperty("class", "QLineEdit1");

    return_reader_IDL->setProperty("class","RegisterLbl");
    return_br_IDL->setProperty("class","RegisterLbl");

    QGridLayout* pG = new QGridLayout; //布局
    pG->addWidget(return_reader_IDL, 1, 0, 1, 1, Qt::AlignRight);
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

void User::SelectBorrowBooksList() //查询个人所借图书
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
void User::Return_clicked() //还书响应
{
    //如果输入信息为空，则提示用户输入信息
    if (return_br_ID->text().trimmed() == "")
    {
        QMessageBox::information(this, "return_back", "you do not input any information, please try again");
        return;
    }


    //用户还书后系统修改对应的还书时间为当前时间
    //根据输入的借阅ID完成还书，因为借阅ID唯一
    QSqlQuery myQuery(db);
    QString str_sql = "update loan_record set back_date=Now() where user_ID='" + return_reader_ID->text().trimmed()+"' and book_ID='"+return_br_ID->text().trimmed()+"'order by loan_date asc LIMIT 1";
    myQuery.exec(str_sql);

    //根据用户输入的br_re id号,锁定对应的图书,使图书库存加1
    str_sql = "update book set stock=stock+1 where \
                book_ID='" + return_br_ID->text().trimmed()+"'";
    myQuery.exec(str_sql);
    QMessageBox::information(this, "", "Return successfully");
    Rew->close();
    delete Rew;
    return;
}
