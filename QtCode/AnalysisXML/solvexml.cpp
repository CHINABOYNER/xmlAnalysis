#include "solvexml.h"
#include <QFile>
#include <QTextStream>

SolveXML::SolveXML() {

}

void SolveXML::showXML(const QDomElement& element, QStandardItem *parentItem, QHash<QStandardItem*,QDomElement> &map) {
    // 处理属性
    QDomNamedNodeMap attributes = element.attributes();
    for (int i = 0; i < attributes.count(); ++i) {
        QDomAttr attribute = attributes.item(i).toAttr();
//        QStandardItem* attributeItem = new QStandardItem(attribute.name() + ":" + attribute.value());

        QStandardItem* attributeItemLeft = new QStandardItem(attribute.name());
        attributeItemLeft->setEditable(false); //属性名不可编辑
        QStandardItem* attributeItemRight = new QStandardItem(attribute.value());
        parentItem->setChild(i,0,attributeItemLeft);
        parentItem->setChild(i,1,attributeItemRight);

//        parentItem->appendRow(attributeItem);
    }

    // 处理元素名和值
    if (element.firstChild().isText()) {
        QString elementText = element.text();
        if(!elementText.isEmpty()){
//            QStandardItem* valueItem = new QStandardItem("元素的值:" + elementText);

            QStandardItem* attributeItemLeft = new QStandardItem("元素的值");
            attributeItemLeft->setEditable(false); //不可编辑
            QStandardItem* attributeItemRight = new QStandardItem(elementText);
            parentItem->setChild(attributes.count(),0,attributeItemLeft);
            parentItem->setChild(attributes.count(),1,attributeItemRight);

//            parentItem->appendRow(valueItem);
        }
    }

    // 处理子元素
    QDomNodeList children = element.childNodes();
    for (int i = 0; i < children.count(); ++i) {
        QDomNode child = children.at(i);
        if (child.isElement()) {
            QDomElement childElement = child.toElement();
            QStandardItem* childItem = new QStandardItem(childElement.tagName());

            //添加记录到map中
            map[childItem] = childElement;

            parentItem->appendRow(childItem); //添加结点

            showXML(childElement, childItem, map);
        }
    }
}

bool SolveXML::updateAttribute(QDomElement &element, const QStringList &str) {
    if (element.hasAttribute(str.at(0))) {
        element.setAttribute(str.at(0), str.at(1));
        qDebug()<<"属性已修改";
        return true;
    }
    qDebug()<<"属性修改失败";
    return false;
}

bool SolveXML::updateName(QDomElement &element, const QString &str) {
    element.setTagName(str);
    return true;
}

bool SolveXML::updateValue(QDomElement &element, const QString &str) {
    if(element.firstChild().isText()){
        element.firstChild().toText().setNodeValue(str);
        qDebug()<<"元素名已修改";
        return true;
    }
    qDebug()<<"元素名修改失败";
    return false;
}

void SolveXML::saveXML(QDomDocument &doc, QString fileName) {
    QFile file(fileName);
    bool isOk = file.open(QIODevice::WriteOnly);
    if(isOk) {
        QTextStream stream(&file);
        doc.save(stream,1);
    }
    file.close();
}
