#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>


class Item;
class QToolButton;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void init();
    void initMember();
    void initUI();
    void initSignalSlot();

private:
    QToolButton *createToolButton(const QString &icon, const QString &txt);

private slots:
    void btnAddSlot();
    void btnDeleteSlot();
    void btnOkSlot();
    void btnCancelSlot();

private:
    Item *_item;
    QToolButton *_btnAdd;
    QToolButton *_btnDelete;
    QToolButton *_btnOk;
    QToolButton *_btnCancel;

};
#endif // WIDGET_H
