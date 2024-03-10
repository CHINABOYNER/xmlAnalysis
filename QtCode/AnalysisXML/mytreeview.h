#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H

#include <QTreeView>

class MyTreeView : public QTreeView
{
    Q_OBJECT
public:
    MyTreeView();
    explicit MyTreeView(QWidget *parent = nullptr);
};

#endif // MYTREEVIEW_H
