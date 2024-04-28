//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as 
// this commented part is listed
//
// Last modified by: Zein Salah, on 23.04.2024
//


#pragma once

#include <QOpenGLWidget>

class RenderWidget : public QOpenGLWidget
{
  Q_OBJECT

  public:
    #define M_PI   3.14159265358979323846


    RenderWidget(QWidget *parent = 0);
    ~RenderWidget();

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

  protected slots:
    void zoomIn();
    void zoomOut();
    void rotateAboutX(double angle);
    void rotateAboutY(double angle);

  protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent * event);

    void drawCube(void);

    typedef struct
    {
      double x, y, z;
    } Point3D;

    Point3D m_ViewPoint;

    enum MouseButtonState 
    {
      NoButton = 0x00000000,
      LeftButton = 0x00000001,
      RightButton = 0x00000002,
      MiddleButton = 0x00000004,
    };

    int m_LastAngle;
    int m_LastMouseX;
    int m_LastMouseY;

    MouseButtonState mouseButton;
    bool IS_LeftButton, IS_MiddleButton, IS_RightButton;

};
