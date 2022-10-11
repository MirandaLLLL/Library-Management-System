#include "LibraryManagementSystem.h"
#include "ui_LibraryManagementSystem.h"

LibraryManagementSystem::LibraryManagementSystem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LibraryManagementSystem)
{
    ui->setupUi(this);
    this->setWindowTitle("welcome to library system");
}

//LibraryManagementSystem::~LibraryManagementSystem()
//{
  //  delete ui;
//}
