#ifndef STATE_H
#define STATE_H

#include <QPainter>


class Item;

class State
{
public:
    State(Item *item);
    virtual ~State();

    virtual void draw(QPainter &p) = 0;

protected:
    virtual void init();

protected:
    Item *_item;

};

#endif // STATE_H
