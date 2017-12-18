#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QTimer"
#include <vector>
#include "stdio.h"
#include "iostream"
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

private:
    QTimer *timer;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
