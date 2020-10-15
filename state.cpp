#include "state.h"

State::State(Item *item) : _item(item)
{
    init();
}

State::~State()
{
    _item = nullptr;
}

void State::init()
{
    // Do nothing
}
