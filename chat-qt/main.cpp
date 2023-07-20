#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication ChatApp(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return ChatApp.exec();
}
