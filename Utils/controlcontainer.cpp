#include "controlcontainer.h"
#include "item.h"


template <typename T>
ControlContainer<T>::ControlContainer(QWidget *parent)
    : QWidget(parent)
{

}

template <typename T>
ControlContainer<T>::~ControlContainer()
{
    qDeleteAll(_listItems);
    _listItems.clear();
}

template <typename T>
bool ControlContainer<T>::add(T *item)
{
    if (!item) return false;
    if (_listItems.contains(item)) _listItems.removeAll(item);

    _listItems.append(item);
    refresh();

    return true;
}

template <typename T>
bool ControlContainer<T>::insert(int idx, T *item)
{
    if (!item) return false;
    if (_listItems.contains(item)) _listItems.removeAll(item);

    if (idx <= 0) _listItems.prepend(item);
    else if (idx >= _listItems.size()) _listItems.append(item);
    else _listItems.insert(idx, item);

    refresh();
    return true;
}

template <typename T>
bool ControlContainer<T>::remove(T *item)
{
    if (!item) return false;
    int res = _listItems.removeAll(item);

    refresh();
    return res;
}

template <typename T>
bool ControlContainer<T>::remove(int idx)
{
    if (idx < 0 || idx >= _listItems.size()) return false;
    _listItems.removeAt(idx);

    refresh();
    return true;
}

template <typename T>
bool ControlContainer<T>::replace(T *oldItem, T *newItem)
{
    if (!oldItem || !newItem || !_listItems.contains(oldItem)) return false;

    int idx = _listItems.indexOf(oldItem);
    _listItems.insert(idx, newItem);
    _listItems.removeAll(oldItem);

    refresh();
    return true;
}

template <typename T>
bool ControlContainer<T>::replace(int idx, T *item)
{
    if (idx < 0 || idx >= _listItems.size() || !item) return false;
    _listItems.removeAt(idx);
    _listItems.insert(idx, item);

    refresh();
    return true;
}

template <typename T>
bool ControlContainer<T>::move(int oldIdx, int newIdx)
{
    if (oldIdx < 0 || oldIdx >= _listItems.size()) return false;
    if (newIdx < 0 || newIdx >= _listItems.size()) return false;
    _listItems.move(oldIdx, newIdx);

    refresh();
    return true;
}

template <typename T>
bool ControlContainer<T>::swap(int idx1, int idx2)
{
    if (idx1 < 0 || idx1 >= _listItems.size()) return false;
    if (idx2 < 0 || idx2 >= _listItems.size()) return false;
    _listItems.swap(idx1, idx2);

    refresh();
    return true;
}

template <typename T>
T *ControlContainer<T>::find(int idx) const
{
    if (idx < 0 || idx >= _listItems.size()) return nullptr;
    return _listItems.at(idx);
}

template <typename T>
int ControlContainer<T>::indexOf(T *item) const
{
    return _listItems.indexOf(item);
}

template <typename T>
void ControlContainer<T>::clear()
{
    _listItems.clear();
    refresh();
}

template <typename T>
int ControlContainer<T>::count() const
{
    return _listItems.count();
}

template <typename T>
bool ControlContainer<T>::isEmpty() const
{
    return _listItems.empty();
}

template <typename T>
void ControlContainer<T>::refresh()
{
    // Do nothing
}



/********************************* Explicit instantiate **************************************/
template class ControlContainer<Item>;

