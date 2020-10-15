#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>


class Item;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void init();

private:
    Item *_item;

};
#endif // WIDGET_H
