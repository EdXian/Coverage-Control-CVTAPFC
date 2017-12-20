#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QTimer"
#include <vector>
#include "stdio.h"
#include "iostream"
#include "src/robot.h"
#include "src/qcustomplot.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:


    void loop(void);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // for all obstacles
    obstacle_list all_obstacles;




    //robot
    QVector<QCPCurveData> robot_data;
    QCPCurve *robot_curve1;
    robot robot1;
    std::vector<robot> group;
    //obstacles
    typedef std::vector<QVector<QCPCurveData> > Curve_data_list;
    typedef std::vector<QCPCurve *> Curve_list;

    obstacle obs1;
    obstacle obs2;
    obstacle obs3;
    Curve_data_list obstacle_data_list;
    Curve_list obstacle_curve;
    Curve_list robot_curve;

    void plot_obstacle();
    void plot_robot();
    //

private:
    QTimer *timer;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
