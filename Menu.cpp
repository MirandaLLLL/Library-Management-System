#include "Menu.h"
#include "ui_Menu.h"
#include "bookmanagement.h"
#include "ReaderManagement.h"
#include "BrreManagement.h"

Menu::Menu(QSqlDatabase db,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    this->db = db;
}

Menu::~Menu()
{
 //   delete ui;
}

void Menu::Init()
{
    //界面控件设置和之前的一致
    QWidget* w = new QWidget();
    w->setProperty("class", "Menu");
    w->setWindowTitle("Menu page");
    QFont font; //字体
    w->resize(1920, 1080);
    BookManage = new QPushButton("Book Management");
    readerManage = new QPushButton("User Management");
    BrReManage = new QPushButton("LoanManagement");
    ExitSystem = new QPushButton("EXIT");
    BookManage->setProperty("class", "MenuBtn");
    readerManage->setProperty("class", "MenuBtn");
    BrReManage->setProperty("class", "MenuBtn");
    ExitSystem->setProperty("class", "MenuBtn");

    UpdtPwdBtn = new QPushButton("Update Password");
    UpdtPwdBtn->setProperty("class", "MenuBtn");
    UpdtPwdBtn->setFixedSize(300, 80);

    BookManage->setFixedSize(300, 80);
    readerManage->setFixedSize(300, 80);
    BrReManage->setFixedSize(300, 80);
    ExitSystem->setFixedSize(300, 80);



    QGridLayout* layout = new QGridLayout;  //网格布局

    layout->addWidget(BookManage, 0, 2, 1, 1);  //括号里参数(控件名，起始位置坐标0,2，控件所占行列1,1)
    layout->addWidget(readerManage, 1, 2, 1, 1);
    layout->addWidget(BrReManage, 2, 2, 1, 1);
    layout->addWidget(UpdtPwdBtn,3,2,1,1);
    layout->addWidget(ExitSystem,4, 2, 1, 1);

    w->setLayout(layout);
    w->show();


    connect(BookManage, SIGNAL(clicked()), this, SLOT(InitBookMangage()));
    connect(readerManage, SIGNAL(clicked()), this, SLOT(InitReaderMangage()));
    connect(BrReManage, SIGNAL(clicked()), this, SLOT(InitBrReMangage()));
    connect(UpdtPwdBtn, SIGNAL(clicked()), this, SLOT(UpdatePwd()));
    connect(ExitSystem, SIGNAL(clicked()), this, SLOT(Exit()));

}

void Menu::InitBookMangage() //图书管理
{
    BookManagement* PBM = new BookManagement(db);
    PBM->Init();
}

void Menu::InitReaderMangage()//读者管理
{
    ReaderManagement* PRM = new ReaderManagement(db);
    PRM->Init();
}

void Menu::InitBrReMangage()//借阅管理
{
    BrReManagement *PBR = new BrReManagement(db);
    PBR->Init();
}


void Menu::Exit()//退出
{
    exit(0);
}

void Menu::UpdatePwd()
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

void Menu::Update_clicked() //修改密码
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
    QString str_sql1 = "select * from faculty where fal_ID='"  //用户登录从读者表中找到姓名和密码
        + username
       +"'and password='"
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
                          // QMessageBox::information(this, "Log", "Log in successfully");
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

                           QString str_sql = "update faculty set password='"+NewPwd->text().trimmed()+"' where fal_ID='" + Update_ID->text().trimmed()+"'";
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
