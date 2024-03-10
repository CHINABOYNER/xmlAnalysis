#ifndef SOLVEXML_H
#define SOLVEXML_H
#include<QTreeView>
#include<QDomDocument>
#include<QMap>
#include<QStandardItem>


class SolveXML
{
public:
    SolveXML();

    void static showXML(const QDomElement& element, QStandardItem* parentItem,QHash<QStandardItem*,QDomElement>& map); //显示XML属性
    bool static updateAttribute(QDomElement &element, const QStringList &str); //更新属性
    bool static updateName(QDomElement &element, const QString &str); //更新元素名
    bool static updateValue(QDomElement &element, const QString &str); //更新元素值
    void static saveXML(QDomDocument& doc,QString fileName); //保存XML文件
};

#endif // SOLVEXML_H
