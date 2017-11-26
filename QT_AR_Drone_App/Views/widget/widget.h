#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui>
#include <QGLWidget>
// my class
#include "../../Models/GeoPoint/GeoPoint.h"

class Widget : public QGLWidget
{
public:
    QList<GeoPoint> Points; // QList of Points on the Map

    Widget(QWidget *parent = 0);
    void setSceneParam(int outW, int outH, int outGridSize);
    void drawPoint(/*GeoPointValues PointStruct*/); // draw one point


    // It is needed for QList initialisation
    void addPoint(double, double, double, double, double, unsigned char[3]);  // add color
    GeoPointValues getFirst();
    GeoPointValues getLast();
    GeoPointValues getPoint(int);
    int getLength();

    void showAllPoints(); // just for Debugging
protected:
    // Open GL
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
    // mouse
    void mousePressEvent(QMouseEvent* pe);   // mouse button is pressed
    void mouseMoveEvent(QMouseEvent* pe);    // mouse button is unpressed
    void mouseReleaseEvent(QMouseEvent* pe); // отжатие клавиши мыши
    void wheelEvent(QWheelEvent *);          // mouse wheel spinning


private:
    int xRotation,yRotation,zRotation; // 3D scene rotation values
    double scale; // scaling value
    QPoint mousePos; // value for saving mouse posittion
    int w; // scene size width
    int h; // -//- height
    int gridSize;
    // my Open GL methods for gas map app
    void screenInfo();
    void drawGrid();
    void drawAxis(); // axis shower
    //rewrite me !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    void colorCalc(unsigned char color); // change color from green to red according 0 - 255 number
};

#endif // WIDGET_H
