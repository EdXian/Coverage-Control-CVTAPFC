#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

     ui->setupUi(this);

     // create timer
     timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()),this, SLOT(loop()));
     timer->start(10);




}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::loop(void){



}
