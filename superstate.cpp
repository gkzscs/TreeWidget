#include "superstate.h"
#include "item.h"
#include <QLabel>


SuperState::SuperState(Item *item)
    : State(item)
{
    init();
}

void SuperState::draw(QPainter &p)
{
    drawIcon(p);
}

void SuperState::init()
{
    _sizeIcon = QSize(20, 20);
    if (!_item) return;

//    _item->_labTitle->move(_item->getItemHeight(), 0);
}

void SuperState::drawIcon(QPainter &p)
{
    QString pixPath = (_item->isFold() ? "plus" : "subtract");
    QRect rect(0, 0, _item->getItemHeight(), _item->getItemHeight());
    QSize size(20, 20);
    rect = calcCenterRect(rect, size);

    p.save();
    p.drawPixmap(rect, QPixmap(":/icon/" + pixPath));
    p.restore();
}

QRect SuperState::calcCenterRect(QRect rect, QSize size)
{
    int x = rect.x() + rect.width()/2 - size.width()/2;
    int y = rect.y() + rect.height()/2 - size.height()/2;

    return QRect(x, y, size.width(), size.height());
}
