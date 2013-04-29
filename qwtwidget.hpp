#ifndef QWTWIDGET_HPP
#define QWTWIDGET_HPP

#include <QWidget>
#include <QtGui>
#include <qwt.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>

using namespace Qwt;
class QwtWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QwtWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    void show(bool b);
private:
    QwtPlot *plot;


};

#endif // QWTWIDGET_HPP
