#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    robot_data(100)


{

     ui->setupUi(this);
    setWindowTitle("Coverage-Control");
     ui->statusBar->close();
     ui->statusBar->clearMessage();
    // create timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(loop()));
    timer->start(10);

    //set customplot
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot->xAxis->setRange(-10,10);
    ui->customPlot->yAxis->setRange(-10,10);
    //QCP set obstacle and robot item


    //create a robot
    robot robotx;
    robot1.robot_state.pos.x = -3;
    robot1.robot_state.pos.y = -3;
    robot1.robot_state.radius = 1;
    group.push_back(robot1);

    //create obstacles

//    obs1.position.x = 1 ;
//    obs1.position.y = 2 ;
//    obs1.gain = 5;
//    obs1.radius = 0.8;
//    all_obstacles.push_back(obs1);
    obs2.position.x = 2 ;
    obs2.position.y = 3 ;
    obs2.gain = 5;
    obs2.radius = 3;
    all_obstacles.push_back(obs2);
//    obs3.position.x = 4 ;
//    obs3.position.y = 5 ;
//    obs3.gain = 4;
//    obs3.radius = 1.2;
//    all_obstacles.push_back(obs3);

    for(unsigned int i=0;i<all_obstacles.size() ;i++){

        obstacle_curve.push_back(new QCPCurve(ui->customPlot->xAxis,ui->customPlot->yAxis));
    }

    for(unsigned int i=0;i<group.size() ;i++){

        robot_curve.push_back(new QCPCurve(ui->customPlot->xAxis,ui->customPlot->yAxis));

    }


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::loop(void){

    //robot_curve


   //robot detect obstacles

    group[0].detect_obstacle(all_obstacles);
    position target;
    target.x = 10;
    target.y = 10;
    group[0].p->gradient_phi(group[0].robot_state , all_obstacles , target);

   //the dynamics of robot

    group[0].robot_state.vel.x *= 40;
    group[0].robot_state.vel.y *= 40;

    if(group[0].robot_state.vel.x > 0.3){
        group[0].robot_state.vel.x=0.3;
    }else if(group[0].robot_state.vel.x <-0.3){
        group[0].robot_state.vel.x=-0.3;
    }
    if(group[0].robot_state.vel.y > 0.3){
        group[0].robot_state.vel.y=0.3;
    }else if(group[0].robot_state.vel.y <-0.3){
        group[0].robot_state.vel.y=-0.3;
    }


    if (group[0].p->distance(group[0].robot_state.pos , target)<1){
        group[0].robot_state.pos.x += -0.1*(group[0].robot_state.pos.x - target.x);
        group[0].robot_state.pos.y += -0.1*(group[0].robot_state.pos.y - target.y);

    }else{
        group[0].robot_state.pos.x  += group[0].robot_state.vel.x;
        group[0].robot_state.pos.y  += group[0].robot_state.vel.x;
    }

    //plot robot and obstacles
    plot_robot();
    plot_obstacle();
    ui->customPlot->replot();
}


void MainWindow::plot_robot(){

    QVector<QCPCurveData> data(100);
    for(unsigned int j = 0 ; j < group.size() ;j++){
        for (int i=0; i<100; ++i)
        {
            data[i] = QCPCurveData(i,
                                   group[j].robot_state.pos.x+group[j].robot_state.radius*cos(0.1*i),
                                   group[j].robot_state.pos.y+group[j].robot_state.radius*sin(0.1*i));
        }
         robot_curve[j]->setPen(QPen(Qt::blue));
         robot_curve[j]->data()->set(data,true);
    }
}


void MainWindow::plot_obstacle(){

    QVector<QCPCurveData> data(100);
    for(unsigned int j = 0 ; j < all_obstacles.size() ;j++){
        for (int i=0; i<100; ++i)
        {
            data[i] = QCPCurveData(                                         i,
                                   all_obstacles[j].position.x+all_obstacles[j].radius*cos(0.1*i),
                                   all_obstacles[j].position.y+all_obstacles[j].radius*sin(0.1*i));
        }

         obstacle_curve[j]->setPen(QPen(Qt::red));
         obstacle_curve[j]->data()->set(data,true);
    }

}

