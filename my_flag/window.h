#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include "ui_MainWindow.h"
#include "openglwidget.h"
#include "spring.h"

namespace Ui {
    class sim;
    class OpenGLWidget;
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    OpenGLWidget *myopenglwidget;
    Sim *mySim;
    void displaySpringDetails();

public slots:
    void box_dampingConstant(double value);
    void box_restLength(double value);
    void box_mass(double value);
    void box_springConstant(double value);


};

#endif // MAINWINDOW_H
