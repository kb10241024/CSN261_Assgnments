#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <iostream>
#include <vector>
#include <map>
#include<algorithm>
#include <cmath>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addSegment(double x1, double y1, double x2, double y2);
    void printIntersection();

    void linearFit();
private slots:
    void plotData(double x1,double y1,double x2,double y2);
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

};


#endif // MAINWINDOW_H
