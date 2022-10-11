#include "ReaderManagement.h"
#include "ui_ReaderManagement.h"
#include<QHeaderView>
#include<QDate>

ReaderManagement::ReaderManagement(QSqlDatabase db,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReaderManagement)
{
    ui->setupUi(this);
    this->db = db;
}

ReaderManagement::~ReaderManagement()
{
    delete ui;
}

void ReaderManagement::Init()
{
    QWidget* readerw = new QWidget();
    readerw->setProperty("class", "SumW");
    readerw->setWindowTitle("Reader management");
    QFont font;
    readerw->resize(1920, 1080);
    tableView = new QTableView;//控制表格样式显示
    tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn); //垂直滚动条
    tableView->setProperty("class", "tableview");
    model = new QSqlTableModel(this);

    InsertBtn = new QPushButton("Add users");
    InsertBtn->setProperty("class", "FunctionBtn");
    UpdateBtn = new QPushButton("Update users");
    UpdateBtn->setProperty("class", "FunctionBtn");
    DeleteBtn = new QPushButton("Delete users");
    DeleteBtn->setProperty("class", "FunctionBtn");
    InsertBtn->setFixedSize(250,70);
    UpdateBtn->setFixedSize(250,70);
    DeleteBtn->setFixedSize(250,70);



    canditionL = new QLabel("Keyword:");
    canditionL->setProperty("class", "SumLabel");

    reader_nameL = new QLabel("Name");
    reader_nameL->setProperty("class", "SumLabel");
    reader_enterpriseL = new QLabel("Enterprise");
    reader_enterpriseL->setProperty("class", "SumLabel");
    reader_typeL = new QLabel("Type");
    reader_typeL->setProperty("class", "SumLabel");
    readerIdL = new QLabel("ID");
    readerIdL->setProperty("class", "SumLabel");

    reader_name = new QLineEdit(this);
    reader_name->setPlaceholderText(tr("Name"));
    reader_name->setFixedSize(120, 30);
    reader_enterprise = new QLineEdit(this);
    reader_enterprise->setPlaceholderText(tr("Enterprise"));
    reader_enterprise->setFixedSize(120, 30);
    readerId = new QLineEdit(this);
    readerId->setFixedSize(120, 30);
    readerId->setPlaceholderText(tr("ID"));
    reader_type = new QLineEdit(this);
    reader_type->setFixedSize(120, 30);
    reader_type->setPlaceholderText(tr("Type"));
    SearchBtn = new QPushButton("Query");
    SearchBtn->setProperty("class", "SelectBtn");
    DisplayAllbtn = new QPushButton("Display all");
    DisplayAllbtn->setProperty("class", "SelectBtn");
    SearchBtn->setFixedSize(80, 25);
    DisplayAllbtn->setFixedSize(120,25);



    font.setPointSize(15);
    InsertBtn->setFont(font);//字体大小
    UpdateBtn->setFont(font);
    DeleteBtn->setFont(font);

    QGridLayout* pQ = new QGridLayout; //布局
    //设置控件位置
    pQ->addWidget(InsertBtn, 2, 8, 2, 2);
    pQ->addWidget(UpdateBtn, 4, 8, 2, 2);
    pQ->addWidget(DeleteBtn, 6, 8, 2, 2);

    pQ->addWidget(canditionL, 0, 0, 1, 1);
    pQ->addWidget(readerIdL, 0, 1, 1, 1);
    pQ->addWidget(readerId, 0, 2, 1, 1);
    pQ->addWidget(reader_nameL, 0, 3, 1, 1);
    pQ->addWidget(reader_name, 0, 4, 1, 1);
    pQ->addWidget(reader_enterpriseL, 0, 5, 1, 1);
    pQ->addWidget(reader_enterprise, 0, 6, 1, 1);
    pQ->addWidget(reader_typeL, 0, 7, 1, 1);
    pQ->addWidget(reader_type, 0, 8, 1, 1);
    pQ->addWidget(SearchBtn, 0, 9, 1, 1);
    pQ->addWidget(DisplayAllbtn, 0, 10, 1, 1);
    pQ->addWidget(tableView, 1, 0, 16, 8);



    //告诉布局方式
    readerw->setLayout(pQ);
    readerw->show();

    connect(InsertBtn, SIGNAL(clicked()), this, SLOT(Insertreaders()));
    connect(UpdateBtn, SIGNAL(clicked()), this, SLOT(Updatereaders()));
    connect(DeleteBtn, SIGNAL(clicked()), this, SLOT(Deletereaders()));
    connect(SearchBtn, SIGNAL(clicked()), this, SLOT(Selectreaders()));
    connect(DisplayAllbtn, SIGNAL(clicked()), this, SLOT(DisplayAllreadrs()));


}



void ReaderManagement::Insertreaders()
{
    Addw = new QWidget();
    Addw->setProperty("class", "RegisterPage");
    Addw->setWindowTitle("Add_page");
    Addw->setMinimumSize(500, 600);
    Addw->setMaximumSize(500, 600);
    Add_Ok = new QPushButton("confirm to add");
    Add_Ok->setProperty("class", "RegisterBtn");
    Add_Ok->setFixedSize(200, 30);

    //Auser_IDL = new QLabel("User_ID");
    //Auser_ID = new QLineEdit(this);
    //Auser_ID->setPlaceholderText(tr("User_ID"));
    //Auser_ID->setProperty("class", "QLineEdit1");

    Auser_nameL = new QLabel("User_name");
    Auser_name = new QLineEdit(this);
    Auser_name->setPlaceholderText(tr("User_name"));
    Auser_name->setProperty("class", "QLineEdit1");

    Auser_passwordL = new QLabel("password");
    Auser_password = new QLineEdit(this);
    Auser_password->setPlaceholderText(tr("password"));
    Auser_password->setProperty("class", "QLineEdit1");

    AenterpriseL = new QLabel("Enterprise");
    Aenterprise = new QLineEdit(this);
    Aenterprise->setPlaceholderText(tr("Enterprise"));
    Aenterprise->setProperty("class", "QLineEdit1");

    AtypeL = new QLabel("Type");
    Atype = new QLineEdit(this);
    Atype->setPlaceholderText(tr("Type"));
    Atype->setProperty("class", "QLineEdit1");
    Auser_nameL->setProperty("class","RegisterLbl");
    Auser_passwordL->setProperty("class","RegisterLbl");
    AenterpriseL->setProperty("class","RegisterLbl");
    AtypeL->setProperty("class","RegisterLbl");


    QGridLayout* pG = new QGridLayout; //布局
    pG->addWidget(Auser_nameL, 1, 0, 1, 1);
    pG->addWidget(Auser_name, 1, 1, 1, 1);
    pG->addWidget(Auser_passwordL, 2, 0, 1, 1);
    pG->addWidget(Auser_password, 2, 1, 1, 1);
    pG->addWidget(AenterpriseL, 3, 0, 1, 1);
    pG->addWidget(Aenterprise, 3, 1, 1, 1);
    pG->addWidget(AtypeL, 4, 0, 1, 1);
    pG->addWidget(Atype, 4, 1, 1, 1);
    pG->addWidget(Add_Ok, 5, 1, 1, 1);
    Addw->setLayout(pG);
    Addw->show();

    connect(Add_Ok, SIGNAL(clicked()), this, SLOT(Add_clicked()));
}

void ReaderManagement::Add_clicked() //还书响应
{


    //编号   "ID"+"当前年份"+"1-10000以内的五位数字(不足前面补0)"
       qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));//设置随机数种子
       QDate date(QDate::currentDate());
       int year = date.year(); //获取当前年份
       QString id1 = QString("%1").arg(year); //将int型转化为string
       int n = qrand() % 100000;  //产生10000以内的随机数
       QString id2 = QString("%1").arg(n,5,10,QLatin1Char('0'));

       QString id = "ID" + id1 + id2;
       //查重
       QSqlDatabase db;
       QSqlQuery query(db);

       QString sqlCode,_id,_id2; //_id用于查重
       int _n;
       int flag = 1; //设置一个查询标志
       sqlCode = "SELECT user_ID FROM user_card";
       query.exec(sqlCode);
       while(flag == 1)
       {
           while(query.next())
           {
               if(query.value("user_ID").toString() == id)//若找到则flag = 1 ，跳出循环，再次查重
               {
                   _n = qrand() % 100000;
                   _id2 = QString("%1").arg(_n,5,10,QLatin1Char('0'));
                   _id = "ID" + id1 + _id2;
                   id = _id;  //更新id
                   flag = 1;
                   break;
               }
               else//若不一样，则flag=0，直到查询完整个表，若flag还是0，则跳出外循环
               {
                   flag = 0;
               }
           }
   }

    //   qDebug() << id;
       //ui->lineEdit_id->setText(id);


    QString str_sql = "insert into user_card(user_ID,user_name,user_password,enterprise,user_type) values('" +
        id+ "','" +
        Auser_name->text().trimmed() + "','" +
        Auser_password->text().trimmed() + "','"+
        Aenterprise->text().trimmed()+"','"+
        Atype->text().trimmed()+"')";


    //if (ID->text().trimmed() == "" || name->text().trimmed() == "" ||password->text().trimmed() == ""|| passwordAgain->text().trimmed()==""||enterprise->text().trimmed()==""||type->text().trimmed()=="")
        if (Auser_name->text().trimmed() == "" ||Auser_password->text().trimmed() == ""|| Aenterprise->text().trimmed()==""||Atype->text().trimmed()=="")
    {
        QMessageBox::information(this, "query", "your information is incomplete, please try again");
        this->Addw->close();
        delete Addw;
        return;
    }


    //限制密码需要大于6位
    n = 0;
    for (int i = 0;i < Auser_password->text().trimmed().length();i++)
    {
        n++;
    }
    if (n < 6)
    {
        QMessageBox::information(this, "", "your password need to be no less than 6 digits");
        return;
    }

    //如果输入信息为空，则提示用户输入信息


    //用户还书后系统修改对应的还书时间为当前时间
    //根据输入的借阅ID完成还书，因为借阅ID唯一
    QSqlQuery myQuery(db);
   // QString str_sql = "insert into user_card values('" + Auser_ID->text().trimmed()+"','"+ Auser_name->text().trimmed()+"','"+ Auser_password->text().trimmed()+"','"+ Aenterprise->text().trimmed()+"','"+ Atype->text().trimmed()+"')";
    myQuery.exec(str_sql);

    QMessageBox::information(this, "", "Add successfully");
    QMessageBox::information(this, "query", "Please remember your user_ID:"+id);
    Addw->close();
    delete Addw;
    return;
}

void ReaderManagement::Updatereaders()
{
    Updatew = new QWidget();
    Updatew->setProperty("class", "RegisterPage");
    Updatew->setWindowTitle("Update_page");
    Updatew->setMinimumSize(600, 800);
    Updatew->setMaximumSize(600, 800);
    Update_Ok = new QPushButton("confirm to update");
    Update_Ok->setProperty("class", "RegisterBtn");
    Update_Ok->setFixedSize(180, 30);

    Uuser_IDL = new QLabel("user_ID");
    Uuser_ID = new QLineEdit(this);
    Uuser_ID->setPlaceholderText(tr("input ID you want to update"));
    Uuser_ID->setProperty("class", "QLineEdit1");

    UtypeL = new QLabel("Type");
    Utype = new QLineEdit(this);
    Utype->setPlaceholderText(tr("type"));
    Utype->setProperty("class", "QLineEdit1");

    Uuser_nameL = new QLabel("user_name");
    Uuser_name = new QLineEdit(this);
    Uuser_name->setPlaceholderText(tr("user_name"));
    Uuser_name->setProperty("class", "QLineEdit1");


    UpasswordL = new QLabel("Password");
    Upassword = new QLineEdit(this);
    Upassword->setPlaceholderText(tr("Password"));
    Upassword->setProperty("class", "QLineEdit1");


    UenterpriseL = new QLabel("Enterprise");
    Uenterprise = new QLineEdit(this);
    Uenterprise->setPlaceholderText(tr("Enterprise"));
    Uenterprise->setProperty("class", "QLineEdit1");

    Uuser_IDL->setProperty("class","RegisterLbl");
    UtypeL->setProperty("class","RegisterLbl");
    Uuser_nameL->setProperty("class","RegisterLbl");
    UpasswordL->setProperty("class","RegisterLbl");
    UenterpriseL->setProperty("class","RegisterLbl");

    QGridLayout* pG = new QGridLayout; //布局
    //pG->addWidget(Abook_IDL, 1, 0, 1, 1, Qt::AlignRight);
    pG->addWidget(Uuser_IDL, 1, 0, 1, 1);
    pG->addWidget(Uuser_ID, 1, 1, 1, 1);
    pG->addWidget(Uuser_nameL, 2, 0, 1, 1);
    pG->addWidget(Uuser_name, 2, 1, 1, 1);
    pG->addWidget(UpasswordL, 3, 0, 1, 1);
    pG->addWidget(Upassword, 3, 1, 1, 1);
    pG->addWidget(UenterpriseL, 4, 0, 1, 1);
    pG->addWidget(Uenterprise, 4, 1, 1, 1);
    pG->addWidget(UtypeL, 5, 0, 1, 1);
    pG->addWidget(Utype, 5, 1, 1, 1);
    pG->addWidget(Update_Ok, 6, 1, 1, 1);

    Updatew->setLayout(pG);
    Updatew->show();

    connect(Update_Ok, SIGNAL(clicked()), this, SLOT(Update_clicked()));
}

void ReaderManagement::Update_clicked() //还书响应
{
    //如果输入信息为空，则提示用户输入信息
    if (Uuser_ID->text().trimmed() == "")
    {
        QMessageBox::information(this, "warning", "please input the ID");
        return;
    }


    QSqlQuery myQuery(db);
    if (Utype->text().trimmed() != ""){
        QString str_sql = "update user_card set user_type='" + Utype->text().trimmed()+"' where user_ID='"+Uuser_ID->text().trimmed()+"'";
        myQuery.exec(str_sql);
    }

    if (Uuser_name->text().trimmed() != ""){
        QString str_sql = "update user_card set user_name='" + Uuser_name->text().trimmed()+"' where user_ID='"+Uuser_ID->text().trimmed()+"'";
        myQuery.exec(str_sql);
    }

    if (Uenterprise->text().trimmed() != ""){
        QString str_sql = "update user_card set enterprise='" + Uenterprise->text().trimmed()+"' where user_ID='"+Uuser_ID->text().trimmed()+"'";
        myQuery.exec(str_sql);
    }

    if (Upassword->text().trimmed() != ""){
        QString str_sql = "update user_card set user_password='" + Upassword->text().trimmed()+"' where user_ID='"+Uuser_ID->text().trimmed()+"'";
        myQuery.exec(str_sql);
    }


    QMessageBox::information(this, "", "Update successfully");
    Updatew->close();
    delete Updatew;
    return;
}

void ReaderManagement::Deletereaders(){
    Deletew = new QWidget();
    Deletew->setProperty("class", "RegisterPage");
    Deletew->setWindowTitle("Delete_page");
    Deletew->setMinimumSize(400, 400);
    Deletew->setMaximumSize(400, 400);
    Delete_Ok = new QPushButton("confirm to delete");
    Delete_Ok->setProperty("class", "RegisterBtn");
    Delete_Ok->setFixedSize(180, 30);



    Duser_IDL = new QLabel("Input user_ID:");
    Duser_IDL->setProperty("class","RegisterLbl");
    Duser_ID = new QLineEdit(this);
    Duser_ID->setPlaceholderText(tr("user_ID"));
    Duser_ID->setProperty("class", "QLineEdit1");

    QGridLayout* pG = new QGridLayout;

    pG->addWidget(Duser_IDL, 0, 0, 1, 1);
    pG->addWidget(Duser_ID, 0, 1, 1, 1);
    pG->addWidget(Delete_Ok, 1, 1, 1, 1);

    Deletew->setLayout(pG);
    Deletew->show();

    connect(Delete_Ok, SIGNAL(clicked()), this, SLOT(Delete_clicked()));
}

void ReaderManagement::Delete_clicked(){
    if (Duser_ID->text().trimmed() == "")
    {
        QMessageBox::information(this, "warning", "please input the ID");
        return;
    }


    QSqlQuery myQuery(db);
    QString str_sql = "delete from user_card where user_ID='" + Duser_ID->text().trimmed()+"'";
    myQuery.exec(str_sql);


    QMessageBox::information(this, "", "Delete successfully");
    Deletew->close();
    delete Deletew;
    return;
}


void ReaderManagement::Selectreaders()
{
    QSqlQueryModel* model = new QSqlQueryModel(this);

    QString str_sql = "select user_ID,user_name,enterprise,user_type from user_card where \
                        user_name like '%" + reader_name->text().trimmed() + "%' and \
                        user_type like '%" + reader_type->text().trimmed() + "%' and \
                        enterprise like '%" + reader_enterprise->text().trimmed() + "%' and \
                        user_ID like '%" + readerId->text().trimmed() + "%'";

    if (reader_name->text().trimmed() == "" && reader_enterprise->text().trimmed() == "" && reader_type->text().trimmed() == "" && readerId->text().trimmed() == "")
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
        QMessageBox::information(this, "", "There is no matching record,please try again");
        return;
    }

    model->setQuery(str_sql);
    model->setHeaderData(0, Qt::Horizontal, tr("User_ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("name"));
    model->setHeaderData(2, Qt::Horizontal, tr("enterprise"));
    model->setHeaderData(3, Qt::Horizontal, tr("type"));

    this->tableView->setModel(model);//数据放置进去
    this->tableView->verticalHeader()->hide();//不显示序号
    this->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //表的列宽均匀充满空间
    tableView->show();

    reader_name->clear();
    reader_type->clear();
    reader_enterprise->clear();
    readerId->clear();

}
void ReaderManagement::DisplayAllreadrs()
{
    //QDialog* Dw = new QDialog();
    QSqlQueryModel* model = new QSqlQueryModel(this);
    //QSqlTableModel*model = new  QSqlTableModel(this);


    model->setQuery("select user_ID,user_name,enterprise,user_type from user_card");
    model->setHeaderData(0, Qt::Horizontal, tr("User_ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("name"));
    model->setHeaderData(2, Qt::Horizontal, tr("enterprise"));
    model->setHeaderData(3, Qt::Horizontal, tr("type"));


    this->tableView->setModel(model);//数据放置进去
    this->tableView->verticalHeader()->hide();//不显示序号
    this->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //表的列宽均匀充满空间
    tableView->show();
}





