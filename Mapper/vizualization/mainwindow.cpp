#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../mapper/configurator.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Configurator & conf = Configurator::instance();
    if ( conf.parseCLI(0,NULL)){
        Graph * task = NULL;
//        task = new Graph(4);
        if ( conf.getParser()->parse(task)){
            GraphPrinter printer;
            printer.print(task);
            Graph * grid = NULL;
            if ( conf.getScanner()->scan(grid)){
                printer.print(grid);
                Result result;
                if( conf.getAlgorithm()->process(task,grid,result)){
                }
                conf.getPrinter()->printResult(result);
            }
            delete grid;
        }
        delete task;
    }
    conf.getLogDevice()->close();
    conf.getLogDevice()->open(QIODevice::ReadOnly);

    QByteArray buff = conf.getLogDevice()->readAll();
    QString l(buff);
    qDebug() << l;
    this->ui->log->appendPlainText(l);
}
