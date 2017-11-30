#ifndef WIDGET_H
#define WIDGET_H

//this class provides visualisation by OpenGL

#include <QtGui>
#include <QGLWidget>
// my class
#include "../../Models/GeoPoint/GeoPoint.h"

class Widget : public QGLWidget
{
private:
    QList<GeoPoint> Points; // QList of Points on the Map
    int xRotation,yRotation,zRotation; // 3D scene rotation values
    double scale; // scaling value
    QPoint mousePos; // value for saving mouse posittion
    int w; // scene size width
    int h; // -//- height
    int gridSize;
    int cartesianScale = 100; // 1 m * cartesianScale = 1 * cartesianScale px on the OpenGL
    // my Open GL methods for gas map app
    void screenInfo();
    void drawGrid();
    void drawAxis(); // axis shower
    void colorCalc(unsigned char color); // change color from green to red according 0 - 255 number

protected:
    // Open GL
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
    // mouse
    void mousePressEvent(QMouseEvent* pe);   // mouse button is pressed
    void mouseMoveEvent(QMouseEvent* pe);    // mouse button is mooving
    void mouseReleaseEvent(QMouseEvent* pe); // mouse button is unpressed
    void wheelEvent(QWheelEvent *);          // mouse wheel spinning

public:
    Widget(QWidget *parent = 0);
    void setSceneParam(int outW, int outH, int outGridSize);
    void drawPoint(); // draw one point // !!!!!!!!!! it is possible to optimise it by showing only 300 points
    void getAllPointsList(const QList<GeoPoint> &GeoMap);

    void showAllPoints(); // just for Debugging
};

#endif // WIDGET_H
