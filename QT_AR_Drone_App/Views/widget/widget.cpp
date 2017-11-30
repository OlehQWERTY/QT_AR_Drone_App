#include "widget.h"
 
Widget::Widget(QWidget *parent) // constructor
    : QGLWidget(parent)
{
    resize(300, 300); // set default window size

    xRotation = 0; // x rotation angle
    yRotation = 0; // y -//-
    zRotation = 0; // z -//-
    scale = 0.6; // default scale
}

void Widget::setSceneParam(int outW, int outH, int outGridSize)
{
    w = outW;
    h = outH;
    gridSize = outGridSize;
    if(w >= 300 && h >= 300 && gridSize >= 30) // checking window size and grid size
    {
        resize(w, h);
    }
    else
    {
        w = 300;
        h = 300;
        gridSize = 30;
        resize(w, h);
    }
}
 
void Widget::initializeGL()
{
   qglClearColor(Qt::black); // filling screen with black color (background color)
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_FLAT); // without antialiasing for colors
   glEnable(GL_CULL_FACE); // build outdor shapes
   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); // figures painted front and back // !!!!!! test GL_FRONT
}
 
void Widget::resizeGL(int nWidth, int nHeight)
{
    glViewport(0, 0, nWidth, nHeight); // set view point
    glMatrixMode(GL_PROJECTION);       // set matrix mode
    glLoadIdentity();                  // load 1 matrix
    double maxVal = w > h ? w : h;
    glOrtho(-100.0, w + 100.0, -100.0, h + 100.0, -100 + -1.0 * maxVal, 100.0 + maxVal);/* left(-100) right(900) bottom(-100) top(900)
        near_val(-900) har_val(900) for scene 800 * 800*/
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
 
void Widget::paintGL() // draving
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // display clearing
    glMatrixMode(GL_MODELVIEW); // set model-view matrix
    glLoadIdentity();           // load 1 matrix

    int r_x = w / 2; // 400 - half of width
    int r_y = h / 2; // 400 - half of hight
    int r_z = w > h ? w : h / 2; // half of max val (w or h)
    // drawGrid
    glPushMatrix(); // remember transp matrix
    glTranslatef(r_x, r_y, r_z); // rotate round point x y z
    // rotation and scaling
    glScalef(scale, scale, scale);          // scaling
    glRotatef(xRotation, 1.0f, 0.0f, 0.0f); // ratation along X
    glRotatef(yRotation, 0.0f, 1.0f, 0.0f); // ratation along Y
    glRotatef(zRotation, 0.0f, 0.0f, 1.0f); // ratation along Z
    glTranslatef(-1*r_x, -1*r_y, -1*r_z); // rotate round point x y z
    drawGrid();
    drawPoint();
    glPopMatrix(); // recovering of previously saved matrix
    // show xyz axis
    glPushMatrix(); // remember transp matrix
    // rotation and scaling
    glScalef(0.6, 0.6, 0.6);                // scaling
    glRotatef(xRotation, 1.0f, 0.0f, 0.0f); // ratation along X
    glRotatef(yRotation, 0.0f, 1.0f, 0.0f); // ratation along Y
    glRotatef(zRotation, 0.0f, 0.0f, 1.0f); // ratation along Z
    drawAxis();
    glPopMatrix(); // recovering of previously saved matrix
    // screenInfo
    screenInfo();

}

void Widget::mousePressEvent(QMouseEvent* pe) // mouse button is pressed
{
   // save mouse coordinates
   mousePos = pe->pos();
}

void Widget::mouseMoveEvent(QMouseEvent* pe) // mouse arrow position is changed
{ // calculation of rotation angle acording to pressed mouse pos
   xRotation += 180/scale*(GLfloat)(pe->y()-mousePos.y())/height();
   zRotation += 180/scale*(GLfloat)(pe->x()-mousePos.x())/width();

   mousePos = pe->pos();

   updateGL(); // image update
}

void Widget::mouseReleaseEvent(QMouseEvent *pe)
{
}

void Widget::drawAxis()
{
    glLineWidth(4.0f); // set line width

    glColor4f(1.00f, 0.00f, 0.00f, 1.0f); // set color of the line
    // axis x
    glBegin(GL_LINES); // line
    glVertex3f( 80.0f,  0.0f,  0.0f); // first point
    glVertex3f(0.0f,  0.0f,  0.0f); // second point

    glColor4f(0.00f, 1.00f, 0.00f, 1.0f); // set color of the line
    // axis y
    glVertex3f( 0.0f,  0.0f,  0.0f);
    glVertex3f( 0.0f, -80.0f,  0.0f);

    glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
    // axis z
    glVertex3f( 0.0f,  0.0f,  80.0f);
    glVertex3f( 0.0f,  0.0f, 0.0f);
    glEnd();
}

void Widget::wheelEvent(QWheelEvent* pe) // mouse wheel spinning
{
    // keep scale in 0.3 - 0.8 range
    if(scale <= 0.3)
    {
        scale = 0.3;
    }
    else if(scale >= 0.65)
    {
        scale = 0.65;
    }

    // if mouse wheel spinning + -> scale *= 1.1
    // else -> scale =/ 1.1
    if ((pe->delta())>0)
    {
        scale*=1.1;
    }
    else if ((pe->delta())<0)
    {
        scale/=1.1;
    }

    updateGL(); // image update
}

void Widget::screenInfo()
{
    QColor halfRed(127, 0, 0, 255);
    int vertTextPos = w - 260;
    qglColor(halfRed); // set soft Red color
    renderText(10, vertTextPos + 20, "xRotation: ");
    renderText(80, vertTextPos + 20, QString::number(xRotation));

    QColor halfBlue(0, 0, 127, 255);
    qglColor(halfBlue); // set soft Blue color
    renderText(10, vertTextPos + 40, "zRotation: ");
    renderText(80, vertTextPos + 40, QString::number(zRotation));

    QColor halfWhite(127, 127, 127, 255);
    qglColor(halfWhite); // set soft White color
    renderText(10, vertTextPos + 60, "scale: ");
    //QString convertToNormalScaleForShowing = QString::number(scale);
    renderText(60, vertTextPos + 60, QString::number(scale * 1.66666666666666666666666)); // if scale = default (0.6) it creates it to 0.6 * 1.6(6) = 1

    //сітка 1 2 3 4 5 6 7 8 9 номерів квадратиків
//    double scaleCoof = scale * 1.66666666666666666666666;
//    if((xRotation == 90 || xRotation == -90 || xRotation == 0) &&
//            (zRotation == 90 || zRotation == -90 || zRotation == 0))
//    {
//        for(int i = 0; i < 10; i++)
//        {

//            renderText(200*2 - 200 * scaleCoof, 200*2 - 20 * scaleCoof - 200 * scaleCoof + 35 * i * scaleCoof/*+ (gridSize * scale * 0.75) * i*/, QString::number(i));
//        }
//    }

}

void Widget::drawGrid()//Drowing of Fields
{
    glLineWidth(2.0f); // set line width
    glColor3f(0.1, 0.1, 0.1); // color of Fields

    glBegin(GL_LINES);

    //xy
    for (int i = 0; i <= w; i += gridSize) // gridSize change grid size
    {
        glVertex3f(i, 0, 0);
        glVertex3f(i, h, 0);
    }
    for (int j = 0; j <= h; j += gridSize)
    {
        glVertex3f(0, j, 0);
        glVertex3f(w, j, 0);
    }
    //yz
    glColor3f(0.2, 0.2, 0.2); // color of Fields
    for (int i = 0; i <= w; i += gridSize)
    {
        glVertex3f(0, i, 0);
        glVertex3f(0, i, h);
    }
    for (int j = 0; j <= h; j += gridSize)
    {
        glVertex3f(0, 0, j);
        glVertex3f(0, w, j);
    }
    //xz
    glColor3f(0.3, 0.3 ,0.3); // color of Fields
    for (int i = 0; i <= w; i += gridSize)
    {
        glVertex3f(i, w, 0);
        glVertex3f(i, w, h);
    }
    for (int j = 0; j <= h; j += gridSize)
    {
        glVertex3f(0, w, j);
        glVertex3f(w, w, j);
    }
    glEnd();
}

void Widget::drawPoint()
{
    glPointSize(5);
    glColor4f(0.00f, 0.00f, 0.00f, 1.0f); // set default color of the Points (in case if color wasn't declarated)
    glBegin(GL_POINTS);
    foreach (GeoPoint tempGeoPoint, Points) { // it is possible to optimise it by showing 300 points
        //(show each # i =+ int(ammount points / 300) )
        // add color
        colorCalc(tempGeoPoint.color[0]); // ! rewrite it
        glVertex3f(tempGeoPoint.cartesianX * cartesianScale + w / 2, tempGeoPoint.cartesianY * cartesianScale + h/2,
                   tempGeoPoint.cartesianZ * cartesianScale); // w / 2 and h/2 set Zero position on the middle of grid
    }
    glEnd();
}

void Widget::colorCalc(unsigned char color) // rewrite me !!!!!!!!!!!!!!!!!!!!!!!!!!
{
    if(color < 127)
    {
        glColor4f((color + 1)/127.0, 1.0, 0, 1.0);
        //qDebug() << (color + 1);
    }
    else
    {
        glColor4f(1.0, 1.0 - (color + 1)/255.0, 0, 1.0);
        //qDebug() << (color + 1);
    }
}

void Widget::getAllPointsList(const QList<GeoPoint> &GeoMap)
{
    Points = GeoMap;
}

void Widget::showAllPoints() // just for Debugging
{
    foreach (GeoPoint tempGeoPoint, Points) {
        qDebug() << "Latitude   " << "[" << tempGeoPoint.id << "]" << tempGeoPoint.latitude;
        qDebug() << "Longitude  " << "[" << tempGeoPoint.id << "]" << tempGeoPoint.longitude;
        qDebug() << "CartesianX " << "[" << tempGeoPoint.id << "]" << tempGeoPoint.cartesianX;
        qDebug() << "cartesianY " << "[" << tempGeoPoint.id << "]" << tempGeoPoint.cartesianY;
        qDebug() << "cartesianZ " << "[" << tempGeoPoint.id << "]" << tempGeoPoint.cartesianZ;
        qDebug() << "Color      " << "[" << tempGeoPoint.id << "]"
                 << "r" << tempGeoPoint.color[0] << "g" << tempGeoPoint.color[1] << "b" << tempGeoPoint.color[2];
        qDebug() << "------------------";
    }
}
