#include "widget.h"
#include "item.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    init();
}

Widget::~Widget()
{
}

void Widget::init()
{
    resize(600, 800);

    _item = new Item(Item::Super, this);
    _item->setTitle("Root");
    _item->move(100, 100);

    auto tmpItem = new Item();
    tmpItem->setTitle("Middle Item 1");
    _item->add(tmpItem);

    for (int i = 0; i < 3; ++i)
    {
        auto supItem = new Item(Item::Super);
        supItem->setTitle("Super Item " + QString::number(i));
        _item->add(supItem);

        for (int j = 0; j < 5; ++j)
        {
            auto kidItem = new Item();
            kidItem->setTitle("Kid Item" + QString::number(j));
            supItem->add(kidItem);
        }
    }

    tmpItem = new Item();
    tmpItem->setTitle("Middle Item 2");
    _item->add(tmpItem);
}
