#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>

#include <QDomDocument>
#include <QTableWidgetItem>
#include <QList>
#include <QDomNode>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QDomDocument doc; //新建QDomDocument类对象，它代表一个XML文档

private slots:
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
