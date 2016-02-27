#include "window.h"
#include "foundation.h"

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
    cout << "window deconstruction" << endl;
    delete myopenglwidget;
    delete ui;
}

void MainWindow::displaySpringDetails()
{
    /*ui->lcd_damping_constant->display(mySim->myFlag->dampingConstant );
    ui->lcd_mass->display( mySim->myFlag->particleMass );
    ui->lcd_rest_length->display( mySim->myFlag->springs[0]->restLength );
    ui->lcd_spring_constant->display( mySim->myFlag->springConstant );*/
}

// Boxes for changing logic
void MainWindow::box_dampingConstant(float value)
{
    myopenglwidget->mySim->myFlag->dampingConstant = value;
    ui->lcd_damping_constant->display(value);
    myopenglwidget->button_reset();
}

void MainWindow::box_restLength(float value)
{
    myopenglwidget->mySim->myFlag->springs[0]->restLength = value;
    ui->lcd_rest_length->display(value);
    myopenglwidget->button_reset();
}

void MainWindow::box_mass(float value)
{
    myopenglwidget->mySim->myFlag->particleMass = value;
    ui->lcd_mass->display(value);
    myopenglwidget->button_reset();
}

void MainWindow::box_springConstant(float value)
{
    myopenglwidget->mySim->myFlag->springConstant = value;
    ui->lcd_spring_constant->display(value);
    myopenglwidget->button_reset();
}
