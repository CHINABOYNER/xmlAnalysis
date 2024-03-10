#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QStandardItem>
#include "solvexml.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{    
    ui->setupUi(this);



    QVBoxLayout *layout = new QVBoxLayout(this);

    ui->centralwidget->setLayout(layout);
    ui->centralwidget->layout()->addWidget(ui->treeView);

//    QHBoxLayout *layout2 = new QHBoxLayout(this);
//    ui->centralwidget->setLayout(layout2);
    QRect r;
    r.setHeight(80);
    r.setWidth(30);
    ui->pushButton->setGeometry(420,550,80,30);
    ui->pushButton->setContentsMargins(100,100,100,100);
    ui->centralwidget->layout()->addWidget(ui->pushButton);




    QString styleSheet = "QTreeView::item {"
                         "    border: 1px solid #d9d9d9;"
                         "    border-top-color: transparent;"
                         "    border-bottom-color: transparent;"
                         "}"
                         "QTreeView::item:hover {"
                         "    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e7effd, stop: 1 #cbdaf1);"
                         "    border: 1px solid #bfcde4;"
                         "}"
                         "QTreeView::item:selected {"
                         "    border: 1px solid #567dbc;"
                         "}"
                         "QTreeView::item:selected:active {"
                         "    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6ea1f1, stop: 1 #567dbc);"
                         "}"
                         "QTreeView::item:selected:!active {"
                         "    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6b9be8, stop: 1 #577fbf);"
                         "}"
                         "QTreeView::branch {"
                         "    background-color: transparent;"
                         "}"
                         "QTreeView::branch:has-siblings:!adjoins-item {"
                         "    border-image: none;"
                         "}"
                         "QTreeView::branch:has-siblings:adjoins-item {"
                         "    border-image: none;"
                         "}"
                         "QTreeView::branch:closed:has-children {"
                         "    border-image: none;"
                         "    image: url(D:/File/QtCode/AnalysisXML/up.png);"
                         "}"
                         "QTreeView::branch:open:has-children {"
                         "    border-image: none;"
                         "    image: url(D:/File/QtCode/AnalysisXML/down.png);"
                         "}";

    ui->treeView->setStyleSheet(styleSheet);




    //建立指向“.xml”文件的QFile对象
    QFile file("D:/File/text.xml");
    //以只读方式打开
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"无法打开";
        return;
    }

    doc.setContent(&file);//将文件内容读到doc中  将这个文档的数据解析到这个树上
    //关闭文件
    file.close();

    //获得文件的根节点
    QDomElement docElem = doc.documentElement();

    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels(QStringList() << "Property" << "Value");


    // 创建 QTreeView 并设置 model
    ui->treeView->setModel(model);
    ui->treeView->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->treeView->header()->setSectionResizeMode(1, QHeaderView::Stretch);

    // 显示 QTreeView
    ui->treeView->show();

    QHash<QStandardItem*,QDomElement> myMap;

    // 构建属性树
    QStandardItem* rootItem = model->invisibleRootItem();
    SolveXML::showXML(docElem, rootItem, myMap);

    ui->treeView->setModel(model);

    //绑定点击事件
    connect(model, &QStandardItemModel::itemChanged, [=](QStandardItem* clickedItem) {
//        QStringList list = clickedItem->text().split(":"); //新属性的键值对
        int row = clickedItem->row();
        QStringList list; //新属性的键值对元素
        QDomElement temp = myMap[clickedItem]; //存储当前元素
        QStandardItem* tempItem = clickedItem; //当前值

        clickedItem = clickedItem->parent(); //寻找父节点
        if(!clickedItem){
            list.append(tempItem->text());
        }else{
            for(int i=0;i<2;i++){  //为list添键值对
                if(clickedItem->child(row,i)){
                    list.append(clickedItem->child(row,i)->text());
                }
            }
        }


        if (clickedItem && list.length() == 2) {
            // 获取到被点击的QStandardItem指针
            qDebug() << "Clicked Item: " << clickedItem->text();

            QDomElement elem = myMap[clickedItem]; //新属性对应的元素

            if(!SolveXML::updateAttribute(elem, list)) {//更新属性值
                SolveXML::updateValue(elem, list.at(1));
            }
        }else{
            SolveXML::updateName(temp, list.at(0)); //更新元素的名字
        }
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    SolveXML::saveXML(doc, "D:/File/textNew.xml");
    QMessageBox::information(this,"提示","保存成功");
}



