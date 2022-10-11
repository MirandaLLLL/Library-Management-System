#include "Login.h"
#include "ui_Login.h"
#include <QMessageBox>
#include<QButtonGroup>
#include<QDate>


Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}
void Login::Init()
{
    //连接数据库
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("library_sys1");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("AImo@19981229");
    db.open();

    this->resize(1920,1080); //控制窗口大小
    this->setProperty("class", "Login"); //类选择器名Login
    this->setWindowTitle("Log in Page"); //设置窗口标题

    tableView = new QTableView;  //表格视图
    tableView->setProperty("class", "view");
    tableView->setFixedSize(600, 400);

    QHBoxLayout* p = new QHBoxLayout(this);

    p->addWidget(tableView);

    //QGridLayout* pG = new QGridLayout(tableView);

    //添加控件
    //用户名Label
    TitleLbl= new QLabel(this);
    TitleLbl->move(710, 20);     //移动到(720, 400)位置(Label左上角坐标，相对于父窗体)
    TitleLbl->setText("Welcome to Library");  //设置标签文本
    TitleLbl->setProperty("class", "Slogan");
    TitleLbl->setFixedSize(1000,400);

    userNameLbl = new QLabel(this);  //new一个标签对象

    userNameLbl->move(750, 420);     //移动到(720, 400)位置(Label左上角坐标，相对于父窗体)
    userNameLbl->setText("User ID:");  //设置标签文本
    userNameLbl->setProperty("class", "LoginLabel");

    //密码Label
    pwdLbl = new QLabel(this);

    pwdLbl->move(750, 530);
    pwdLbl->setText("Password:");
    pwdLbl->setProperty("class", "LoginLabel");


    //用户名输入框
    userName = new QLineEdit(this); //new一个文本输入框对象
    userName->move(900, 420);
    userName->setFixedSize(200, 30);  //设置控件尺寸
    userName->setPlaceholderText(tr("UserID")); //占位符
    userName->setProperty("class", "logininput");

    //密码输入框
    pwd = new QLineEdit(this);
    pwd->move(900, 530);
    pwd->setFixedSize(200, 30);
    pwd->setPlaceholderText("Password");
    pwd->setEchoMode(QLineEdit::Password); //输入的密码以圆点显示
    pwd->setProperty("class", "logininput");

    //登录按钮
    loginBtn_u = new QPushButton(this);
    loginBtn_u->move(900, 650);
    loginBtn_u->setText("User Log");
    loginBtn_u->setProperty("class", "btn1");
    loginBtn_u->setFixedSize(150, 40);

    loginBtn_a = new QPushButton(this);
    loginBtn_a->move(700, 650);
    loginBtn_a->setText("Admin Log");
    loginBtn_a->setProperty("class", "btn1");
    loginBtn_a->setFixedSize(150, 40);

    //退出按钮
    registerBtn = new QPushButton(this);

    registerBtn->move(1100, 650);
    registerBtn->setText("Register");
    registerBtn->setProperty("class", "btn1");
    registerBtn->setFixedSize(150, 40);

    //告诉窗口是哪个布局
    this->setLayout(p);
    this->show(); //显示

    //单击登录按钮时 执行 Login::login 槽函数(自定义)；单击退出按钮时 执行 Login::close 槽函数(窗体的关闭函数，不用自己写)
    connect(loginBtn_u, &QPushButton::clicked, this, &Login::login_u);
    connect(loginBtn_a, &QPushButton::clicked, this, &Login::login_a);
    connect(registerBtn, &QPushButton::clicked, this, &Login::Register);

}

void Login::login_u()
{

    //获得userNameLEd输入框的文本：userName->text()；
    //trimmed()去掉前后空格
    if (db.open()) //数据库连接成功
    {

        QMessageBox::information(this, "", "connect sql database successfully");
    }
    else //数据库连接失败
    {
        QMessageBox::warning(this, tr("Warning！"), tr("connect to sql fail"), QMessageBox::Yes);

    }
        QSqlQuery myQuery(db);
        QString username=userName->text();
        QString password=pwd->text();
        QString str_sql1 = "select * from user_card where user_ID='"  //用户登录从读者表中找到姓名和密码
            + username
           +"'and user_password='"
            + password
            + "'";

         judge=0;
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
                       User* p_user = new User(db);
                       this->close();//关闭对话框
                       delete this;  //释放内存
                       p_user->Init();
                    }
              }
                if(judge==0){
                     QMessageBox::information(this, "warning", "wrong username or password");
          }
     }

}

void Login::login_a()
{

    //获得userNameLEd输入框的文本：userName->text()；
    //trimmed()去掉前后空格
    if (db.open()) //数据库连接成功
    {

        QMessageBox::information(this, "", "connect sql database successfully");
    }
    else //数据库连接失败
    {
        QMessageBox::warning(this, tr("Warning！"), tr("connect to sql fail"), QMessageBox::Yes);

    }
        QSqlQuery myQuery(db);
        QString username=userName->text();
        QString password=pwd->text();
        QString str_sql2 = "select * from faculty where fal_ID='"  //用户登录从读者表中找到姓名和密码
            + username

            +"'and password='"
            + password
            + "'";
        judge=0;
        if (myQuery.exec(str_sql2))
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
                               Menu* p_menu = new Menu(db); //初始化菜单窗口
                               this->close();//关闭对话框
                               delete this;  //释放内存
                               p_menu->Init();
                            }

                        }
                        if(judge==0){
                             QMessageBox::information(this, "warning", "wrong username or password");
                 }
         }

}



void Login::Register()
{
    //setWindowModality(Qt::NonModal);
    rw = new QWidget();
    rw->setProperty("class", "RegisterPage");
    rw->setWindowTitle("Register");

    rw->setMinimumSize(600, 800);
    rw->setMaximumSize(600, 800);

    nameL=new QLabel("Name:");
    passwordL=new QLabel("Password:");
    passwordAgainL = new QLabel("Confirm password:");
    enterpriseL = new QLabel("Enterprise:");
    typeL = new QLabel("Type:");
    nameL->setProperty("class", "RegisterLbl");
    passwordL->setProperty("class", "RegisterLbl");
    passwordAgainL->setProperty("class", "RegisterLbl");
    typeL->setProperty("class", "RegisterLbl");
    enterpriseL->setProperty("class", "RegisterLbl");

    name = new QLineEdit(this);
    name->setProperty("class", "QLineEditRegister");
    name->setPlaceholderText(tr("Input your name"));
    enterprise= new QLineEdit(this);
    enterprise->setProperty("class", "QLineEditRegister");
    enterprise->setPlaceholderText(tr("Input your enterprise"));
    type= new QLineEdit(this);
    type->setProperty("class", "QLineEditRegister");
    type->setPlaceholderText(tr("Input your type"));
    password=new QLineEdit(this);
    password->setProperty("class", "QLineEditRegister");
    password->setPlaceholderText(tr("Input the password"));
    password->setEchoMode(QLineEdit::Password); //输入的密码以圆点显示
    passwordAgain = new QLineEdit(this);
    passwordAgain->setProperty("class", "QLineEditRegister");
    passwordAgain->setPlaceholderText(tr("confirm your password"));
    passwordAgain->setEchoMode(QLineEdit::Password); //输入的密码以圆点显示
    Sure_Register=new QPushButton("Confirm to register");
    Sure_Register->setFixedSize(220, 50);
    Sure_Register->setProperty("class", "RegisterBtn");


    //QGridLayout* pQ = new QGridLayout(this);
    QGridLayout* pQ = new QGridLayout;
    pQ->addWidget(nameL, 1, 0, 1, 1);
    pQ->addWidget(name, 1, 1, 1, 1);
    pQ->addWidget(enterpriseL, 2, 0, 1, 1);
    pQ->addWidget(enterprise, 2, 1, 1, 1);
    pQ->addWidget(passwordL, 3, 0, 1, 1);
    pQ->addWidget(password, 3, 1, 1, 1);
    pQ->addWidget(passwordAgainL, 4, 0, 1, 1);
    pQ->addWidget(passwordAgain, 4, 1, 1, 1);
    pQ->addWidget(typeL, 5, 0, 1, 1);
    pQ->addWidget(type, 5, 1, 1, 1);
    pQ->addWidget(Sure_Register, 6, 1, 1, 1);

    rw->setLayout(pQ);
    rw->show();

    connect(Sure_Register, SIGNAL(clicked()), this, SLOT(RegisterInfo()));
}

void Login::RegisterInfo()
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



    QString str_sql = "insert into user_card(user_ID,user_name,user_password,enterprise,user_type) values('" +
        id+ "','" +
        name->text().trimmed() + "','" +
        password->text().trimmed() + "','"+
        enterprise->text().trimmed()+"','"+
        type->text().trimmed()+"')";



        if (name->text().trimmed() == "" ||password->text().trimmed() == ""|| passwordAgain->text().trimmed()==""||enterprise->text().trimmed()==""||type->text().trimmed()=="")
    {
        QMessageBox::information(this, "query", "your information is incomplete, please try again");
        this->rw->close();
        delete rw;
        return;
    }


    //限制密码需要大于6位
    n = 0;
    for (int i = 0;i < password->text().trimmed().length();i++)
    {
        n++;
    }
    if (n < 6)
    {
        QMessageBox::information(this, "", "your password need to be no less than 6 digits");
        return;
    }


    if ( password->text().trimmed()!=passwordAgain->text().trimmed())
    {
        QMessageBox::information(this, "", "the password does not match");
        //->rw->close();
        //delete rw;
        return;
    }

    QSqlQuery myQuery(db);
    if (myQuery.exec(str_sql))
    {
        QMessageBox::information(this, "Register", " register successfully");
        QMessageBox::information(this, "query", "Please remember your user_ID:"+id);
        this->rw->close();
        delete rw;
        return;
    }
    else
    {
        QMessageBox::information(this, "", "the server is busy, please try again");
        this->rw->close();
        delete rw;
    }
}
