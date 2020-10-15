#include "item.h"
#include "normalstate.h"
#include "superstate.h"
#include <QLabel>
#include <QStyleOption>
#include <QMouseEvent>


Item::Item(StateType type, QWidget *parent)
    : ControlContainer<Item>(parent), _stateType(type)
{
    init();
}

Item::~Item()
{
    if (_state) delete _state;
    if (_labTitle) _labTitle->deleteLater();
    if (_wgtLeft) _wgtLeft->deleteLater();
    if (_wgtRight) _wgtRight->deleteLater();
}

bool Item::add(Item *item)
{
    if (_stateType != Super) setStateType(Super);
    return ControlContainer::add(item);
}

bool Item::insert(int idx, Item *item)
{
    if (_stateType != Super) setStateType(Super);
    return ControlContainer::insert(idx, item);
}

bool Item::remove(int idx)
{
    bool res = ControlContainer::remove(idx);
    if (isEmpty() && _stateType != Normal) setStateType(Normal);

    return res;
}

bool Item::remove(Item *item)
{
    bool res = ControlContainer::remove(item);
    if (isEmpty() && _stateType != Normal) setStateType(Normal);

    return res;
}

void Item::clear()
{
    if (_stateType != Normal) setStateType(Normal);
}

void Item::setStateType(StateType type)
{
    if (type == _stateType && _state) return;
    _stateType = type;

    // Destroy old state
    if (_state)
    {
        delete _state;
        _state = nullptr;
    }

    // Set new state
    if (_stateType == Normal) _state = new NormalState(this);
    else if (_stateType == Super) _state = new SuperState(this);

    update();
}

void Item::setFold(bool flag)
{
    if (flag == _fold) return;
    _fold = flag;

    showSubItems(!flag);
    refresh();
}

void Item::setSelected(bool flag)
{
    if (flag == _selected) return;
    // Cancel last select first, then select this item
    _selected = flag;

    // Update style
    style()->unpolish(_labTitle);
    style()->polish(_labTitle);
}

void Item::setItemHeight(int h)
{
    if (h == _itemHeight) return;
    _itemHeight = h;

    _labTitle->setFixedHeight(h);
    refresh();
}

void Item::setMargin(int m)
{
    if (m == _margin) return;
    _margin = m;

    refresh();
}

void Item::setTitle(const QString &title)
{
    _labTitle->setText(title);
}

Item::StateType Item::getStateType() const
{
    return _stateType;
}

bool Item::isFold() const
{
    return _fold;
}

bool Item::isSelected() const
{
    return _selected;
}

int Item::getItemHeight() const
{
    return _itemHeight;
}

int Item::getMargin() const
{
    return _margin;
}

QString Item::getTitle() const
{
    return _labTitle->text();
}

int Item::totalHeight() const
{
    int h = _itemHeight;

    if (_wgtRight->isVisible())
    {
        for (auto item : _listItems) h += item->totalHeight();
    }

    return (isVisible() ? h : 0);
}

Item *Item::parentItem() const
{
    Item *parItem = nullptr;

    if (!parent() || !parent()->parent()) return parItem;
    parItem = qobject_cast<Item *>(parent()->parent());

    return parItem;
}

Item *Item::root() const
{
    Item *root = const_cast<Item *>(this);
    while (root->parentItem()) root = root->parentItem();

    return root;
}

Item *Item::getSelectedItem() const
{
    if (isSelected()) return const_cast<Item *>(this);
    for (auto item : _listItems)
    {
        auto res = item->getSelectedItem();
        if (res) return res;
    }

    return nullptr;
}

void Item::destroyMe()
{
    auto par = parentItem();
    if (!par) return;

    par->remove(this);
    delete this;
}

void Item::addItem()
{
    auto item = new Item();
    item->setTitle("New item");
    add(item);
}

void Item::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    const int wLeft = 30;

    _labTitle->setFixedHeight(_itemHeight);
    _wgtLeft->setFixedWidth(wLeft);
    _wgtRight->setFixedWidth(width()-wLeft);
    _labTitle->move(_itemHeight, 0);
    _wgtLeft->move(0, _itemHeight);
    _wgtRight->move(wLeft, _itemHeight);
}

void Item::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    // Enable style sheet
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    // Draw user interface
    if (_state) _state->draw(p);
}

void Item::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    QRect rect(0, 0, _itemHeight, _itemHeight);

    if (_stateType == Super && rect.contains(pos))
    {
        setFold(!_fold);
    }

    rect = _labTitle->geometry();
    if (rect.contains(pos))
    {
        // Here must use `root()` to start the traverse
        cancelLastSelect();
        setSelected(true);
    }
}

void Item::refresh()
{
    // Clear old layout
    for (auto kid : _wgtRight->children())
    {
        auto item = qobject_cast<Item *>(kid);
        if (!item) continue;
        if (_listItems.contains(item))
        {
            item->setParent(nullptr);
            item->hide();
        }
    }

    // Add elements to new layout
    int h = 0;
    for (auto item : _listItems)
    {
//        item->move(0, h);
        item->setParent(_wgtRight);
        item->show();
        item->setGeometry(0, h, _wgtRight->width(), item->totalHeight());

        h += item->totalHeight() + _margin;
    }

    // Resize this item widget
    _wgtLeft->setFixedHeight(h);
    _wgtRight->setFixedHeight(h);
    if (!_fold) setFixedHeight(h+_itemHeight+_margin*2);
    else setFixedHeight(_itemHeight+_margin);

    // If has parent item, then refresh it too
    if (parentItem()) parentItem()->refresh();
}

void Item::init()
{
    initMember();
    initUI();
    initSignalSlot();
}

void Item::initMember()
{
    // Assign member variables with different value, so that we can let the `set` functions make effects
    _state = nullptr;
    _fold = false;
    _selected = true;
    _itemHeight = -1;
    _margin = -1;
    _labTitle = new QLabel(this);
    _wgtLeft = new QWidget(this);
    _wgtRight = new QWidget(this);

    // Set object name
    _labTitle->setObjectName("_labTitle");
}

void Item::initUI()
{
    // Set style sheet
    QFile file(":/qss/item");
    file.open(QIODevice::ReadOnly);
    QString style = file.readAll();
    setStyleSheet(style);
    file.close();

    // Set other attributes
    setMinimumWidth(400);   // To modify
    setSelected(false);
    setItemHeight(30);
    setMargin(0);
    setStateType(_stateType);
    setFold(true);

    // Set member attributes
    _labTitle->setScaledContents(true);
}

void Item::initSignalSlot()
{
    // To do
}

void Item::showSubItems(bool flag)
{
    _wgtLeft->setVisible(flag);
    _wgtRight->setVisible(flag);
}

void Item::cancelLastSelect()
{
    auto item = root()->getSelectedItem();
    if (item) item->setSelected(false);
}
