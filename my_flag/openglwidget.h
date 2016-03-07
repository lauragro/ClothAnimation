#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QGLWidget>
#include "camera.h"
#include "sim.h"
class Camera;
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
    Camera * myCamera;
    bool simMode;
    QTimer * timer;
    QTimer * frameTimer;
    void startup();


public:
    Sim * getMySim(){return mySim;}
    Camera * getMyCamera(){return myCamera;}

public slots:
    void button_go();
    void button_stop();
    void button_reset();

    void advanceTime(void);
    void advanceFrame(void);
    void endit(){exit(0);}

protected:
    //==============Mouse Event Handling =============================
        void mousePressEvent(QMouseEvent *e);
        void mouseReleaseEvent(QMouseEvent *e);
        void mouseMoveEvent(QMouseEvent *e);
    //================================================================

private:
        //=======Camera Stuff=================
//        Camera* m_Camera; /**< The camera object.*/
//
  //      glm::mat4 m_LastRotation; /**< Holds the previous arcball rotation.*/
    //    glm::mat4 m_CurrentRotation; /**< Holds the current arcball rotation.*/
//
  //      glm::mat4 m_LastScale; /**< Holds the last dolly transform.*/
    //    glm::mat4 m_CurrentScale; /**< Holds the current dolly transform.*/
//
  //      glm::mat4 m_LastTranslate; /**< Holds the last track transform.*/
    //    glm::mat4 m_CurrentTranslate; /**< Holds the current track transform.*/
//
  //      int m_IsDrag; /**< If the mouse is dragging true, false otherwise.*/
    //    int m_DrawGrid; /**< If set it draws the ground grid.*/
      //  int m_Play; /**< If set we update the objects.*/
//
  //      double m_LastTime; /**< The previous tick.*/
        //========================================

};
#endif // OPENGLWIDGET_H
