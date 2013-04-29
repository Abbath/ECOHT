#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    currLayerNumber = 0;

    ui->setupUi(this);

    ui->qwtPlot->setTitle("Error");
    ui->qwtPlot->setAxisTitle(ui->qwtPlot->xBottom, "Epoch");
    ui->qwtPlot->setAxisTitle(ui->qwtPlot->yLeft,"Error");

    QPen pen = QPen(Qt::red);
    curve = new QwtPlotCurve;
    curve->setRenderHint(QwtPlotItem::RenderAntialiased);
    curve->setPen(pen);
    curve->attach(ui->qwtPlot);

    connect(ui->saveImageButton,SIGNAL(clicked()),this,SLOT(saveImage()));
    connect(ui->numberOfLayers,SIGNAL(valueChanged(int)),this,SLOT(changeLayers(int)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::plot(QVector<QPointF>& vec){
    QwtPointSeriesData * data = new QwtPointSeriesData(vec);
    curve->setData(data);
    ui->qwtPlot->replot();
}


void MainWindow::saveImage(){
    QString filename = QFileDialog::getSaveFileName(this,tr("Save Image"), "image.png", tr("Image Files (*.png *.jpg *.bmp)"));
    QPixmap pixmap = QPixmap::grabWidget(ui->qwtPlot);

    pixmap.save(filename);
}

void MainWindow::changeLayers( int layersNumber ){
    //layers.resize(layersNumber);
    if( layersNumber > currLayerNumber ){
        layers.resize( layersNumber );
    }
    for ( auto it = layers.begin(); it != layers.end(); ++it ){
        qint32 num = it - layers.begin() + 1;
        if( num > currLayerNumber && num <= layersNumber ){
            (*it).label = new QLabel( QString::number( num ) );
            (*it).fSpacer = new QSpacerItem( 20, 20 );
            (*it).neuronsNumber = new QSpinBox();
            (*it).sSpacer = new QSpacerItem( 20, 20 );
            (*it).activationFunction = new QComboBox();

            (*it).activationFunction->addItem( "Linear" );
            (*it).activationFunction->addItem( "Sigma" );

            ui->layersGrid->addWidget( (*it).label, num, 0, 1, 1 );
            ui->layersGrid->addItem( (*it).fSpacer, num, 1 );
            ui->layersGrid->addWidget( (*it).neuronsNumber, num, 2, 1, 1 );
            ui->layersGrid->addItem( (*it).sSpacer, num, 3 );
            ui->layersGrid->addWidget( (*it).activationFunction, num, 4, 1, 1 );
        }
        if( num <= currLayerNumber && num > layersNumber ){
            ui->layersGrid->removeWidget( (*it).label );
            ui->layersGrid->removeItem( (*it).fSpacer );
            ui->layersGrid->removeWidget( (*it).neuronsNumber );
            ui->layersGrid->removeItem( (*it).sSpacer );
            ui->layersGrid->removeWidget( (*it).activationFunction );

            delete (*it).label;
            delete (*it).fSpacer;
            delete (*it).neuronsNumber;
            delete (*it).sSpacer;
            delete (*it).activationFunction;
        }
        ui->layersGrid->update();
    }
    if( layersNumber < currLayerNumber ){
        layers.resize( layersNumber );
    }
    currLayerNumber = layersNumber;
}