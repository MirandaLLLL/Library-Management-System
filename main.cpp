#include <QApplication>
#include "LibraryManagementSystem.h"
#include <QFile>
#include <QtWidgets/QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include "Login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);//创建一个QApplication实例对象a

        //读取样式文件
        QFile qss(":/LibraryManagementSystem/stylesheet.qss");
        if (qss.open(QFile::ReadOnly)) { //只读方式打开
            QString styleString = qss.readAll();
            a.setStyleSheet(styleString);
            qss.close();
        }

        Login* p_login = new Login();
        p_login->Init();
        return a.exec();

}
