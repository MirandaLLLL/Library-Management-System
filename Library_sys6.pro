#include <QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
QT       += core gui
QT +=sql
QT+=axcontainer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BookManagement.cpp \
    BrreManagement.cpp \
    LibraryManagementSystem.cpp \
    Login.cpp \
    Menu.cpp \
    ReaderManagement.cpp \
    User.cpp \
    main.cpp

HEADERS += \
    BrreManagement.h \
    LibraryManagementSystem.h \
    Login.h \
    Menu.h \
    ReaderManagement.h \
    User.h \
    bookmanagement.h

FORMS += \
    BookManagement.ui \
    BrreManagement.ui \
    LibraryManagementSystem.ui \
    Login.ui \
    Menu.ui \
    ReaderManagement.ui \
    User.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QT+= widgets

RESOURCES += \
    LibraryManagementSystem.qrc

DISTFILES +=
