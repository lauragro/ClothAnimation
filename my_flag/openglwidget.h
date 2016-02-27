#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QGLWidget>
#include "sim.h"
class Sim;

class OpenGLWidget : public QGLWidget
{
    Q_OBJECT


public:
    // Constructor
    OpenGLWidget(QWidget *parent = 0);

    // Destructor
    ~OpenGLWidget();


protected:
    // Initialize graphics engine
    void initializeGL();

    // All painting things
    void paintGL();
    void draw();

    // Resizing
    void resizeGL(int width, int height);

public:
    Sim * mySim;
    bool simMode;
    QTimer * timer;
    QTimer * frameTimer;
    void startup();


public:
    Sim * getMySim(){return mySim;}

public slots:
    void button_go();
    void button_stop();
    void button_reset();

    void advanceTime(void);
    void advanceFrame(void);
    void endit(){exit(0);}

};
#endif // OPENGLWIDGET_H
