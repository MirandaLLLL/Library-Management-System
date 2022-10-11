#ifndef LIBRARYMANAGEMENTSYSTEM_H
#define LIBRARYMANAGEMENTSYSTEM_H

#include <QMainWindow>
#include <QtWidgets/QMainWindow>
#include "ui_LibraryManagementSystem.h"

namespace Ui {
class LibraryManagementSystem;
}

class LibraryManagementSystem : public QMainWindow
{
    Q_OBJECT

public:
    explicit LibraryManagementSystem(QWidget *parent = nullptr);
    //~LibraryManagementSystem();

private:
    Ui::LibraryManagementSystem *ui;
};

#endif // LIBRARYMANAGEMENTSYSTEM_H
