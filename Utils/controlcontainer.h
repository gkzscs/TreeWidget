#ifndef CONTROLCONTAINER_H
#define CONTROLCONTAINER_H

#include <QWidget>


template <typename T>
class ControlContainer : public QWidget
{
public:
    ControlContainer(QWidget *parent = nullptr);
    virtual ~ControlContainer() override;

    virtual bool add(T *item);
    virtual bool insert(int idx, T *item);
    virtual bool remove(T *item);
    virtual bool remove(int idx);
    virtual bool replace(T *oldItem, T *newItem);
    virtual bool replace(int idx, T *item);
    virtual bool move(int oldIdx, int newIdx);
    virtual bool swap(int idx1, int idx2);
    virtual T *find(int idx) const;
    virtual int indexOf(T *item) const;
    virtual void clear();

    virtual int count() const;
    virtual bool isEmpty() const;

protected:
    virtual void refresh() = 0;

protected:
    QList<T *> _listItems;

};



#endif // CONTROLCONTAINER_H
