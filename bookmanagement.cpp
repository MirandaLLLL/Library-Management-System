#include "bookmanagement.h"
#include "ui_BookManagement.h"
#include<QHeaderView>
#include <QFileDialog>
#include <QAxObject>

BookManagement::BookManagement(QSqlDatabase db,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookManagement)
{
    ui->setupUi(this);
    this->db = db;
}

BookManagement::~BookManagement()
{
    delete ui;
}

void BookManagement::Init()
{

    QWidget* bookw = new QWidget();
    bookw->setProperty("class", "SumW");
    bookw->setWindowTitle("Book Management");
    QFont font;
    bookw->resize(1920, 1080);
    tableView = new QTableView;//控制表格样式显示
    tableView->setProperty("class", "tableview"); //声明类选择器

    tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn); //表格的垂直滚动条
    model = new QSqlTableModel(this); //表格模板初始化

    InsertBtn = new QPushButton("Add books");
    InsertBtn->setProperty("class", "FunctionBtn");
    UpdateBtn = new QPushButton("Update books");
    UpdateBtn->setProperty("class", "FunctionBtn");
    DeleteBtn= new QPushButton("Delete books");
    DeleteBtn->setProperty("class", "FunctionBtn");
    InsertBtn->setFixedSize(250,70);
    UpdateBtn->setFixedSize(250,70);
    DeleteBtn->setFixedSize(250,70);

    //ReturnBtn= new QPushButton("Return");
    //ReturnBtn->setProperty("class", "FunctionBtn");

    QGridLayout* pQ = new QGridLayout;
    pQ->addWidget(InsertBtn, 2, 12, 2, 2);
    pQ->addWidget(UpdateBtn, 5, 12, 2, 2);
    pQ->addWidget(DeleteBtn, 8, 12, 2, 2);



    font.setPointSize(15);    //设置字体大小

    InsertBtn->setFont(font);
    UpdateBtn->setFont(font);
    DeleteBtn->setFont(font);


    canditionL = new QLabel("Key word：");
    canditionL->setProperty("class", "SumLabel");
    book_IDL=new QLabel("Book_ID");
    book_IDL->setProperty("class", "SumLabel");
    book_nameL=new QLabel("Book_name");
    book_nameL->setProperty("class", "SumLabel");
    book_authorL=new QLabel("Author");
    book_authorL->setProperty("class", "SumLabel");
    book_pressL=new QLabel("Press");
    book_pressL->setProperty("class", "SumLabel");
    book_typeL=new QLabel("Type");
    book_typeL->setProperty("class", "SumLabel");
    book_yearL=new QLabel("Year");
    book_yearL->setProperty("class", "SumLabel");



    book_ID = new QLineEdit(this);
    book_ID->setFixedSize(100, 30);
    book_ID->setPlaceholderText(tr("ID"));
    book_name = new QLineEdit(this);
    book_name->setFixedSize(100, 30);
    book_name->setPlaceholderText(tr("Name"));
    book_author = new QLineEdit(this);
    book_author->setFixedSize(100, 30);
    book_author->setPlaceholderText(tr("Author"));
    book_press = new QLineEdit(this);
    book_press->setFixedSize(100, 30);
    book_press->setPlaceholderText(tr("Press"));
    book_type = new QLineEdit(this);
    book_type->setFixedSize(100, 30);
    book_type->setPlaceholderText(tr("Type"));
    book_year = new QLineEdit(this);
    book_year->setFixedSize(100, 30);
    book_year->setPlaceholderText(tr("Year"));



    SearchBtn = new QPushButton("Query");
    SearchBtn->setProperty("class", "SelectBtn");
    DisplayAllbtn =new QPushButton("Display all");
    DisplayAllbtn->setProperty("class", "SelectBtn");
    SearchBtn->setFixedSize(80, 25);
    DisplayAllbtn->setFixedSize(120,25);


    pQ->addWidget(canditionL, 0, 0, 1, 1);
    pQ->addWidget(book_IDL, 0, 1, 1, 1);
    pQ->addWidget(book_ID, 0, 2, 1, 1);
    pQ->addWidget(book_nameL, 0, 3, 1, 1);
    pQ->addWidget(book_name, 0, 4, 1, 1);
    pQ->addWidget(book_typeL, 0, 5, 1, 1);
    pQ->addWidget(book_type, 0, 6, 1, 1);
    pQ->addWidget(book_authorL, 0,7, 1, 1);
    pQ->addWidget(book_author, 0, 8, 1, 1);
    pQ->addWidget(book_pressL, 0, 9, 1, 1);
    pQ->addWidget(book_press, 0, 10, 1, 1);
    pQ->addWidget(book_yearL, 0, 11, 1, 1);
    pQ->addWidget(book_year, 0, 12, 1, 1);
    pQ->addWidget(SearchBtn, 0, 13, 1, 1);
    pQ->addWidget(DisplayAllbtn, 0, 14, 1, 1);
    pQ->addWidget(tableView,1, 0, 22, 11);


    bookw->setLayout(pQ);
    bookw->show();

    connect(InsertBtn, SIGNAL(clicked()), this, SLOT(Insertbooks()));
    connect(UpdateBtn, SIGNAL(clicked()), this, SLOT(Updatebooks()));
    connect(DeleteBtn, SIGNAL(clicked()), this, SLOT(Deletebooks()));
    connect(SearchBtn, SIGNAL(clicked()), this, SLOT(Selectbooks()));
    connect(DisplayAllbtn, SIGNAL(clicked()), this, SLOT(DisplayAllbooks()));


}



void BookManagement::Insertbooks() //添加图书
{

    Addw = new QWidget();
    Addw->setProperty("class", "RegisterPage");
    Addw->setWindowTitle("Add_page");
    Addw->setMinimumSize(600, 800);
    Addw->setMaximumSize(600, 800);
    Add_Ok = new QPushButton("Confirm to add");
    Add_Ok->setProperty("class", "RegisterBtn");
    Add_Ok->setFixedSize(200, 50);
    Add_Ok->setProperty("class", "RegisterBtn");
    Add_Ok->setFixedSize(200, 50);
    Batch_add=new QPushButton("Batch Addition");
    Batch_add->setProperty("class", "RegisterBtn");
    Batch_add->setFixedSize(200, 50);
    Batch_add->setProperty("class", "RegisterBtn");
    Batch_add->setFixedSize(200, 50);

    Abook_IDL = new QLabel("Book_ID");
    Abook_IDL->setProperty("class", "RegisterLbl");
    Abook_ID = new QLineEdit(this);
    Abook_ID->setPlaceholderText(tr("Book_ID"));
    Abook_ID->setProperty("class", "QLineEdit1");

    AtypeL = new QLabel("Type");
    AtypeL->setProperty("class", "RegisterLbl");
    Atype = new QLineEdit(this);
    Atype->setPlaceholderText(tr("Type"));
    Atype->setProperty("class", "QLineEdit1");

    Abook_NAMEL = new QLabel("book_name");
    Abook_NAMEL->setProperty("class", "RegisterLbl");
    Abook_NAME = new QLineEdit(this);
    Abook_NAME->setPlaceholderText(tr("Name"));
    Abook_NAME->setProperty("class", "QLineEdit1");


    AauthorL = new QLabel("Author");
    AauthorL->setProperty("class", "RegisterLbl");
    Aauthor = new QLineEdit(this);
    Aauthor->setPlaceholderText(tr("Author"));
    Aauthor->setProperty("class", "QLineEdit1");


    ApressL = new QLabel("Press");
    ApressL->setProperty("class", "RegisterLbl");
    Apress = new QLineEdit(this);
    Apress->setPlaceholderText(tr("Press"));
    Apress->setProperty("class", "QLineEdit1");

    AyearL = new QLabel("Year");
    AyearL->setProperty("class", "RegisterLbl");
    Ayear = new QLineEdit(this);
    Ayear->setPlaceholderText(tr("Year"));
    Ayear->setProperty("class", "QLineEdit1");

    ApriceL = new QLabel("Price");
    ApriceL->setProperty("class", "RegisterLbl");
    Aprice = new QLineEdit(this);
    Aprice->setPlaceholderText(tr("Price"));
    Aprice->setProperty("class", "QLineEdit1");

    ATot_amtL = new QLabel("Tot_AMT");
    ATot_amtL->setProperty("class", "RegisterLbl");
    ATot_amt = new QLineEdit(this);
    ATot_amt->setPlaceholderText(tr("Tot_amount"));
    ATot_amt->setProperty("class", "QLineEdit1");

    AstockL = new QLabel("Stock");
    AstockL->setProperty("class", "RegisterLbl");
    Astock = new QLineEdit(this);
    Astock->setPlaceholderText(tr("Stock"));
    Astock->setProperty("class", "QLineEdit1");

    QGridLayout* pG = new QGridLayout; //布局
    pG->addWidget(Abook_IDL, 1, 0, 1, 1);
    pG->addWidget(Abook_ID, 1, 1, 1, 1);
    pG->addWidget(AtypeL, 2, 0, 1, 1);
    pG->addWidget(Atype, 2, 1, 1, 1);
    pG->addWidget(Abook_NAMEL, 3, 0, 1, 1);
    pG->addWidget(Abook_NAME, 3, 1, 1, 1);
    pG->addWidget(AauthorL, 4, 0, 1, 1);
    pG->addWidget(Aauthor, 4, 1, 1, 1);
    pG->addWidget(ApressL, 5, 0, 1, 1);
    pG->addWidget(Apress, 5, 1, 1, 1);
    pG->addWidget(AyearL, 6, 0, 1, 1);
    pG->addWidget(Ayear, 6, 1, 1, 1);
    pG->addWidget(ApriceL, 7, 0, 1, 1);
    pG->addWidget(Aprice, 7, 1, 1, 1);
    pG->addWidget(ATot_amtL, 8, 0, 1, 1);
    pG->addWidget(ATot_amt, 8, 1, 1, 1);
    pG->addWidget(AstockL, 9, 0, 1, 1);
    pG->addWidget(Astock, 9, 1, 1, 1);
    pG->addWidget(Add_Ok, 10, 1, 1, 1);
    pG->addWidget(Batch_add, 10, 0, 1, 1);

    Addw->setLayout(pG);
    Addw->show();

    connect(Add_Ok, SIGNAL(clicked()), this, SLOT(Add_clicked()));
    connect(Batch_add,SIGNAL(clicked()),this,SLOT(Batch_clicked()));
}
void BookManagement::Batch_clicked(){
    QAxObject excel("ket.Application");
    excel.setProperty("Visible", false);
    QAxObject * workbooks =excel.querySubObject("WorkBooks");

    workbooks->dynamicCall("Open(const QString&)", QString("C:/Users/98317/Desktop/Batch_Add_list.xls"));

    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");

    QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);
    QAxObject *range = worksheet->querySubObject("UsedRange");
    QAxObject *rows = range->querySubObject("Rows");


    //int row_start = range->property("Row").toInt();  //获取起始行

    int row_count = rows->property("Count").toInt();  //获取行数
    int i;
    for(i = 2; i <= row_count;i++){
     //QMessageBox::information(this, "", row_count);
     QAxObject *cell1 = worksheet->querySubObject("Cells(int,int)", i, 1);
     QString B_id = cell1->dynamicCall("Value2()").toString();

     QAxObject *cell2 = worksheet->querySubObject("Cells(int,int)", i, 2);
     QString B_type = cell2->dynamicCall("Value2()").toString();

     QAxObject *cell3 = worksheet->querySubObject("Cells(int,int)", i, 3);
     QString B_name = cell3->dynamicCall("Value2()").toString();

     QAxObject *cell4 = worksheet->querySubObject("Cells(int,int)", i, 4);
     QString author = cell4->dynamicCall("Value2()").toString();

     QAxObject *cell5 = worksheet->querySubObject("Cells(int,int)", i, 5);
     QString press = cell5->dynamicCall("Value2()").toString();

     QAxObject *cell6 = worksheet->querySubObject("Cells(int,int)", i, 6);
     QString year = cell6->dynamicCall("Value2()").toString();

     QAxObject *cell7 = worksheet->querySubObject("Cells(int,int)", i, 7);
     QString price = cell7->dynamicCall("Value2()").toString();

     QAxObject *cell8 = worksheet->querySubObject("Cells(int,int)", i, 8);
     QString tot_amt = cell8->dynamicCall("Value2()").toString();

     QAxObject *cell9 = worksheet->querySubObject("Cells(int,int)", i, 9);
     QString stock = cell9->dynamicCall("Value2()").toString();


     QSqlQuery myQuery(db);

     QString strSql = "insert into book values('"+B_id+"','"+ B_type+"','"+B_name+"','"+ author+"','"+ press+"','" + year+"','"+ price+"','"+ tot_amt+"','"+ stock+"')";
     myQuery.exec(strSql);

    }
    for(i=2;i<row_count;i++){
    QAxObject *cell =  worksheet->querySubObject("Rows(int)",i);//获取选定的行
        if ( cell )
        {
            cell->dynamicCall("Delete()"); //修改所选行
        }
    }

    QMessageBox::information(this, "", "Batch add successfully");
    Addw->close();
    delete Addw;
    return;

}

void BookManagement::Add_clicked() //还书响应
{
    //如果输入信息为空，则提示用户输入信息
    if (Abook_ID->text().trimmed() == ""||Atype->text().trimmed() == ""||Abook_NAME->text().trimmed() == ""||Aauthor->text().trimmed() == ""||Apress->text().trimmed() == ""||Ayear->text().trimmed() == ""||Aprice->text().trimmed() == ""||ATot_amt->text().trimmed() == ""||Astock->text().trimmed() == "")
    {
        QMessageBox::information(this, "warning", "the information is incomplete, please try again");
        return;
    }


    //用户还书后系统修改对应的还书时间为当前时间
    //根据输入的借阅ID完成还书，因为借阅ID唯一
    QSqlQuery myQuery(db);
    QString str_sql = "insert into book values('" + Abook_ID->text().trimmed()+"','"+ Atype->text().trimmed()+"','"+ Abook_NAME->text().trimmed()+"','"+ Aauthor->text().trimmed()+"','"+ Apress->text().trimmed()+"','"+ Ayear->text().trimmed()+"','"+ Aprice->text().trimmed()+"','"+ ATot_amt->text().trimmed()+"','"+ Astock->text().trimmed()+"')";
    myQuery.exec(str_sql);

    QMessageBox::information(this, "", "Add successfully");
    Addw->close();
    delete Addw;
    return;
}


void BookManagement::Updatebooks() //还书
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
    Ubook_ID->setPlaceholderText(tr("input ID you want to update"));
    Ubook_ID->setProperty("class", "QLineEdit1");

    UtypeL = new QLabel("Type");
    UtypeL->setProperty("class", "RegisterLbl");
    Utype = new QLineEdit(this);
    Utype->setPlaceholderText(tr("type"));
    Utype->setProperty("class", "QLineEdit1");

    Ubook_NAMEL = new QLabel("book_name");
    Ubook_NAMEL->setProperty("class", "RegisterLbl");
    Ubook_NAME = new QLineEdit(this);
    Ubook_NAME->setPlaceholderText(tr("book_name"));
    Ubook_NAME->setProperty("class", "QLineEdit1");


    UauthorL = new QLabel("Author");
    UauthorL->setProperty("class", "RegisterLbl");
    Uauthor = new QLineEdit(this);
    Uauthor->setPlaceholderText(tr("Author"));
    Uauthor->setProperty("class", "QLineEdit1");


    UpressL = new QLabel("Press");
    UpressL->setProperty("class", "RegisterLbl");
    Upress = new QLineEdit(this);
    Upress->setPlaceholderText(tr("Press"));
    Upress->setProperty("class", "QLineEdit1");

    UyearL = new QLabel("Year");
    UyearL->setProperty("class", "RegisterLbl");
    Uyear = new QLineEdit(this);
    Uyear->setPlaceholderText(tr("Year"));
    Uyear->setProperty("class", "QLineEdit1");

    UpriceL = new QLabel("Price");
    UpriceL->setProperty("class", "RegisterLbl");
    Uprice = new QLineEdit(this);
    Uprice->setPlaceholderText(tr("Price"));
    Uprice->setProperty("class", "QLineEdit1");

    UTot_amtL = new QLabel("Tot_AMT");
    UTot_amtL->setProperty("class", "RegisterLbl");
    UTot_amt = new QLineEdit(this);
    UTot_amt->setPlaceholderText(tr("Tot_amount"));
    UTot_amt->setProperty("class", "QLineEdit1");

    UstockL = new QLabel("Stock");
    UstockL->setProperty("class", "RegisterLbl");
    Ustock = new QLineEdit(this);
    Ustock->setPlaceholderText(tr("Stock"));
    Ustock->setProperty("class", "QLineEdit1");

    QGridLayout* pG = new QGridLayout; //布局
    pG->addWidget(Ubook_IDL, 1, 0, 1, 1);
    pG->addWidget(Ubook_ID, 1, 1, 1, 1);
    pG->addWidget(UtypeL, 2, 0, 1, 1);
    pG->addWidget(Utype, 2, 1, 1, 1);
    pG->addWidget(Ubook_NAMEL, 3, 0, 1, 1);
    pG->addWidget(Ubook_NAME, 3, 1, 1, 1);
    pG->addWidget(UauthorL, 4, 0, 1, 1);
    pG->addWidget(Uauthor, 4, 1, 1, 1);
    pG->addWidget(UpressL, 5, 0, 1, 1);
    pG->addWidget(Upress, 5, 1, 1, 1);
    pG->addWidget(UyearL, 6, 0, 1, 1);
    pG->addWidget(Uyear, 6, 1, 1, 1);
    pG->addWidget(UpriceL, 7, 0, 1, 1);
    pG->addWidget(Uprice, 7, 1, 1, 1);
    pG->addWidget(UTot_amtL, 8, 0, 1, 1);
    pG->addWidget(UTot_amt, 8, 1, 1, 1);
    pG->addWidget(UstockL, 9, 0, 1, 1);
    pG->addWidget(Ustock, 9, 1, 1, 1);
    pG->addWidget(Update_Ok, 10, 1, 1, 1);

    Updatew->setLayout(pG);
    Updatew->show();


    connect(Update_Ok, SIGNAL(clicked()), this, SLOT(Update_clicked()));
}

void BookManagement::Update_clicked() //还书响应
{
    //如果输入信息为空，则提示输入信息
    if (Ubook_ID->text().trimmed() == "")
    {
        QMessageBox::information(this, "warning", "please input the ID");
        return;
    }


    QSqlQuery myQuery(db);
    if (Utype->text().trimmed() != ""){
        QString str_sql = "update book set book_type='" + Utype->text().trimmed()+"' where book_ID='"+Ubook_ID->text().trimmed()+"'";
        myQuery.exec(str_sql);
    }

    if (Ubook_NAME->text().trimmed() != ""){
        QString str_sql = "update book set book_name='" + Ubook_NAME->text().trimmed()+"' where book_ID='"+Ubook_ID->text().trimmed()+"'";
        myQuery.exec(str_sql);
    }

    if (Uauthor->text().trimmed() != ""){
        QString str_sql = "update book set author='" + Uauthor->text().trimmed()+"' where book_ID='"+Ubook_ID->text().trimmed()+"'";
        myQuery.exec(str_sql);
    }

    if (Upress->text().trimmed() != ""){
        QString str_sql = "update book set press='" + Upress->text().trimmed()+"' where book_ID='"+Ubook_ID->text().trimmed()+"'";
        myQuery.exec(str_sql);
    }

    if (Uyear->text().trimmed() != ""){
        QString str_sql = "update book set year=" + Uyear->text().trimmed()+" where book_ID='"+Ubook_ID->text().trimmed()+"'";
        myQuery.exec(str_sql);
    }

    if (Uprice->text().trimmed()!=""){
        QString str_sql = "update book set price=" + Uprice->text().trimmed()+" where book_ID='"+Ubook_ID->text().trimmed()+"'";
        myQuery.exec(str_sql);
    }

    if (UTot_amt->text().trimmed() != ""){
        QString str_sql = "update book set tot_amount=" + UTot_amt->text().trimmed()+" where book_ID='"+Ubook_ID->text().trimmed()+"'";
        myQuery.exec(str_sql);
    }

    if (Ustock->text().trimmed() != ""){
        QString str_sql = "update book set stock=" + Ustock->text().trimmed()+" where book_ID='"+Ubook_ID->text().trimmed()+"'";
        myQuery.exec(str_sql);
    }

    QMessageBox::information(this, "", "Update successfully");
    Updatew->close();
    delete Updatew;
    return;
}

void BookManagement::Deletebooks(){
    Deletew = new QWidget();
    Deletew->setProperty("class", "RegisterPage");
    Deletew->setWindowTitle("Delete_page");
    Deletew->setMinimumSize(400, 400);
    Deletew->setMaximumSize(400, 400);
    Delete_Ok = new QPushButton("Confirm to delete");
    Delete_Ok->setProperty("class", "RegisterBtn");
    Delete_Ok->setFixedSize(200, 50);

    Dbook_IDL = new QLabel("Input book_ID:");
    Dbook_IDL->setProperty("class", "RegisterLbl");
    Dbook_ID = new QLineEdit(this);
    Dbook_ID->setPlaceholderText(tr("book_ID"));
    Dbook_ID->setProperty("class", "QLineEdit1");

    QGridLayout* pG = new QGridLayout;

    pG->addWidget(Dbook_IDL, 0, 0, 1, 1);
    pG->addWidget(Dbook_ID, 0, 1, 1, 1);
    pG->addWidget(Delete_Ok, 1, 1, 1, 1);

    Deletew->setLayout(pG);
    Deletew->show();

    connect(Delete_Ok, SIGNAL(clicked()), this, SLOT(Delete_clicked()));
}

void BookManagement::Delete_clicked(){
    if (Dbook_ID->text().trimmed() == "")
    {
        QMessageBox::information(this, "warning", "please input the ID");
        return;
    }



    QSqlQuery myQuery(db);
    QString str_sql = "delete from book where book_ID='" + Dbook_ID->text().trimmed()+"'";
    myQuery.exec(str_sql);


    QMessageBox::information(this, "", "Delete successfully");
    Deletew->close();
    delete Deletew;
    return;
}

void BookManagement::Selectbooks() //查询图书
{
    QSqlQueryModel* model = new QSqlQueryModel(this);
    QString str_sql = "select * from book where book_ID like '%" + book_ID->text().trimmed()+"%' and \
                      book_name like '%" + book_name->text().trimmed() + "%' and \
                      book_type like '%" + book_type->text().trimmed() + "%' and \
                      year like '%" + book_year->text().trimmed() + "%' and \
                      author like '%" + book_author->text().trimmed() + "%' and \
                      press like '%" + book_press->text().trimmed() + "%'";

    if (book_name->text().trimmed()==""&&book_type->text().trimmed()==""&& book_ID->text().trimmed()==""&& book_author->text().trimmed()==""&&book_press->text().trimmed()==""&&book_year->text().trimmed()=="")
    {
        QMessageBox::information(this, "query", "You do not input information, please try again");
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
        QMessageBox::information(this, "", "There is no matching record,please try again");
        return;
    }


    model->setQuery(str_sql); //执行查询

                              //设置表头列名
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

    book_name->clear(); //清空输入内容
    book_author->clear();
    book_press->clear();

}
void BookManagement::DisplayAllbooks() //显示所有图书
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

