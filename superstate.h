#ifndef SUPERSTATE_H
#define SUPERSTATE_H

#include "state.h"


class SuperState : public State
{
public:
    SuperState(Item *item);
    virtual void draw(QPainter &p) override;

private:
    virtual void init() override;
    void drawIcon(QPainter &p);
    QRect calcCenterRect(QRect rect, QSize size);

private:
    QSize _sizeIcon;

};

#endif // SUPERSTATE_H
