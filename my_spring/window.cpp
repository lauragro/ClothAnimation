#include "window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Create an instance of the widget and sim used for simulation
    myopenglwidget = new OpenGLWidget(parent);

    // Create all required components of application
    ui->setupUi(this);

    // Display initial spring details
    displaySpringDetails();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displaySpringDetails()
{
    ui->lcd_damping_constant->display(mySim->mySpring->dampingConstant );
    ui->lcd_mass->display( mySim->mySpring->mass );
    ui->lcd_rest_length->display( mySim->mySpring->restLength );
    ui->lcd_spring_constant->display( mySim->mySpring->springConstant );
}

// Boxes for changing logic
void MainWindow::box_dampingConstant(double value)
{
    myopenglwidget->mySim->mySpring->dampingConstant = value;
    ui->lcd_damping_constant->display(value);
    myopenglwidget->button_reset();
}

void MainWindow::box_restLength(double value)
{
    myopenglwidget->mySim->mySpring->restLength = value;
    ui->lcd_rest_length->display(value);
    myopenglwidget->button_reset();
}

void MainWindow::box_mass(double value)
{
    myopenglwidget->mySim->mySpring->mass = value;
    ui->lcd_mass->display(value);
    myopenglwidget->button_reset();
}

void MainWindow::box_springConstant(double value)
{
    myopenglwidget->mySim->mySpring->springConstant = value;
    ui->lcd_spring_constant->display(value);
    myopenglwidget->button_reset();
}
