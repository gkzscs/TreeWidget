#include "widget.h"
#include "item.h"
#include <QToolButton>
#include <QDebug>


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
    initMember();
    initUI();
    initSignalSlot();
}

void Widget::initMember()
{
    _item = new Item(Item::Super, this);
    _btnAdd = createToolButton(":/icon/plus", "Add");
    _btnDelete = createToolButton(":/icon/subtract", "Delete");
    _btnOk = createToolButton("", "Ok");
    _btnCancel = createToolButton("", "Cancel");
}

void Widget::initUI()
{
    resize(600, 800);

    // Set layout
    // Item
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

    // Buttons
    _btnAdd->move(300, 100);
    _btnDelete->move(400, 100);
    _btnOk->move(100, 700);
    _btnCancel->move(200, 700);
}

void Widget::initSignalSlot()
{
    connect(_btnAdd, &QToolButton::clicked, this, &Widget::btnAddSlot);
    connect(_btnDelete, &QToolButton::clicked, this, &Widget::btnDeleteSlot);
    connect(_btnOk, &QToolButton::clicked, this, &Widget::btnOkSlot);
    connect(_btnCancel, &QToolButton::clicked, this, &Widget::btnCancelSlot);
}

QToolButton *Widget::createToolButton(const QString &icon, const QString &txt)
{
    auto btn = new QToolButton(this);

    if (icon.isEmpty()) btn->setToolButtonStyle(Qt::ToolButtonTextOnly);
    else btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    btn->setIcon(QIcon(icon));
    btn->setText(txt);
    btn->resize(80, 30);
    btn->setIconSize(QSize(20, 20));

    return btn;
}

void Widget::btnAddSlot()
{
    auto item = _item->getSelectedItem();
    if (!item) return;

    qDebug() << "btnAddSlot";
    item->addItem();
}

void Widget::btnDeleteSlot()
{
    auto item = _item->getSelectedItem();
    if (!item) return;

    qDebug() << "btnDeleteSlot";
    item->destroyMe();
}

void Widget::btnOkSlot()
{
    qDebug() << "btnOkSlot";
}

void Widget::btnCancelSlot()
{
    qDebug() << "btnCancelSlot";
}



