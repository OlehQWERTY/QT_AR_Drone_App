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
    int xRotation, yRotation, zRotation; // 3D scene rotation values
    double scale; // scaling value
    QPoint mousePos; // value for saving mouse posittion
    int w; // scene size width
    int h; // -//- height
    int gridSize;
    int cartesianScale = 100; // 1 m * cartesianScale = 1 * cartesianScale px on the OpenGL
    long int numbHighlightedPoint = 0; // chose point that will be sized to big one (flight visualiser)
    // my Open GL methods for gas map app
    void screenInfo();
    void drawGrid() const;
    void drawAxis() const; // axis shower

protected:
    // Open GL
    void initializeGL() const;
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
    // mouse
    void mousePressEvent(QMouseEvent* pe);   // mouse button is pressed
    void mouseMoveEvent(QMouseEvent* pe);    // mouse button move
    void mouseReleaseEvent(QMouseEvent* pe) const; // mouse button is unpressed
    void mouseDoubleClickEvent(QMouseEvent* pe) const; // mouse double click // i don't nead it now
    void wheelEvent(QWheelEvent *);          // mouse wheel spinning
    void keyPressEvent(QKeyEvent* ke);       // key press

public:
    Widget(QWidget *parent = 0);
    void setSceneParam(int outW, int outH, int outGridSize);
    void drawPoint() const; // it is possible to optimise it by showing only 300 points or using glDrawArrays()
    void getAllPointsList(const QList<GeoPoint> &GeoMap);

    void showAllPoints() const; // just for Debugging
};

#endif // WIDGET_H
