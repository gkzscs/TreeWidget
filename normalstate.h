#ifndef NORMALSTATE_H
#define NORMALSTATE_H

#include "state.h"


class NormalState : public State
{
public:
    using State::State;
    virtual void draw(QPainter &p) override;

};

#endif // NORMALSTATE_H
