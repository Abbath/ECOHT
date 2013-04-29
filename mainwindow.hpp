#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <qwt.h>
#include <qwt_plot_curve.h>

struct LayerStruct{
    QLabel* label;
    QSpacerItem* fSpacer;
    QSpinBox* neuronsNumber;
    QSpacerItem* sSpacer;
    QComboBox* activationFunction;
};

typedef QVector < LayerStruct > LayersGUI;

namespace Ui{

class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QwtPlotCurve *curve;
    LayersGUI layers;
    qint32 currLayerNumber;
public slots:
    void plot(QVector<QPointF>&);
    void saveImage();
    void changeLayers(int);
};

#endif // MAINWINDOW_H
