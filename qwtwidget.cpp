#include "qwtwidget.hpp"

QwtWidget::QwtWidget(QWidget *parent) :
    QWidget(parent)
{

}


void QwtWidget::show(bool b){
    curve->setVisible(b);
    plot->replot();
}
