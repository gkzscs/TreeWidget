#ifndef ITEM_H
#define ITEM_H

#include "controlcontainer.h"


class State;
class QLabel;

class Item : public ControlContainer<Item>
{
    friend class NormalState;
    friend class SuperState;

    Q_OBJECT
    Q_PROPERTY(bool selected READ isSelected WRITE setSelected)

public:
    enum StateType
    {
        Normal,
        Super
    };

public:
    Item(StateType type = Normal, QWidget *parent = nullptr);
    virtual ~Item() override;

    virtual bool add(Item *item) override;
    virtual bool insert(int idx, Item *item) override;
    virtual bool remove(int idx) override;
    virtual bool remove(Item *item) override;
    virtual void clear() override;

    void setStateType(StateType type);
    void setFold(bool flag);
    void setSelected(bool flag);
    void setItemHeight(int h);
    void setMargin(int m);
    void setTitle(const QString &title);

    StateType getStateType() const;
    bool isFold() const;
    bool isSelected() const;
    int getItemHeight() const;
    int getMargin() const;
    QString getTitle() const;

    int totalHeight() const;
    Item *parentItem() const;
    Item *root() const;
    Item *getSelectedItem() const;
    void destroyMe();
    void addItem();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void refresh() override;

protected:
    void init();
    void initMember();
    void initUI();
    void initSignalSlot();

private:
    void showSubItems(bool flag);
    void cancelLastSelect();

private:
    StateType _stateType;
    State *_state;
    bool _fold;
    bool _selected;
    int _itemHeight;
    int _margin;

    QLabel *_labTitle;
    QWidget *_wgtLeft;
    QWidget *_wgtRight;

};



/************************************** Explicit Instanciate ************************************/
extern template class ControlContainer<Item>;

#endif // ITEM_H
