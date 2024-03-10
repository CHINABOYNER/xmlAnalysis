#include "mainwindow.h"

#include <QApplication>
#include <QVBoxLayout>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("XML解析器");
    w.setWindowIcon(QIcon("D:\\File\\任务6思路.jpg"));
    w.show();
    return a.exec();
}
