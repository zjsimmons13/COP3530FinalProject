#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "StockMap.h"
#include "avltree.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    bool mapStructure = false;
    bool avlStructure = false;
    bool mapExists = false;
    bool avlExists = false;
    double mapLoadTime;
    double treeLoadTime;
    StockMap stockContainer = StockMap(1000000);
    AVLTree stockTree;


public slots:
    void onMapButtonClicked();
    void onAVLButtonClicked();
    void onSearchButtonClicked();
    void disableButtons();
    void onResetButtonClicked();
    void updateProgressBar(int value);


private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
