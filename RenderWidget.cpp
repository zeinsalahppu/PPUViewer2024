//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as 
// this commented part is listed
//
// Last modified by: Zein Salah, on 23.04.2024
//


#include "RenderWidget.h"
#include <glut.h>
#include <QPainter>

RenderWidget::RenderWidget(QWidget* parent) : QOpenGLWidget(parent)
{
  m_ViewPoint.x = 5.0;
  m_ViewPoint.y = 5.0;
  m_ViewPoint.z = 5.0;
}


RenderWidget::~RenderWidget()
{

}


QSize RenderWidget::minimumSizeHint() const
{
  return QSize(100, 100);
}


QSize RenderWidget::sizeHint() const
{
  return QSize(600, 600);
}


void RenderWidget::initializeGL()
{
  glClearColor(1.0, 1.0, 1.0, 0.0);

  glMatrixMode(GL_PROJECTION);
  gluPerspective(15.0, 1.0, 1.0, 100.0);
}


void RenderWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(m_ViewPoint.x, m_ViewPoint.y, m_ViewPoint.z,      /* view point */
    0.0, 0.0, 0.0,      /* ref point */
    0.0, 1.0, 0.0);     /* up direction is positive y-axis */

  drawCube();
}


void RenderWidget::resizeGL(int width, int height)
{
  int side = qMin(width, height);
  glViewport((width - side) / 2, (height - side) / 2, side, side);

  //  glViewport(0, 0, width, height);
}


void RenderWidget::zoomIn()
{
//  std::cout << "Zooming In..\n";

  m_ViewPoint.x *= 0.95;
  m_ViewPoint.y *= 0.95;
  m_ViewPoint.z *= 0.95;

  update();
}


void RenderWidget::zoomOut()
{
//  std::cout << "Zooming Out..\n";

  m_ViewPoint.x /= 0.95;
  m_ViewPoint.y /= 0.95;
  m_ViewPoint.z /= 0.95;

  update();
}


void RenderWidget::rotateAboutY()
{
  double angle = 5.0 / 180 * M_PI;

//  std::cout << "Rotating about Y by " << angle << "\n";

  double newx = m_ViewPoint.x * cos(angle) + m_ViewPoint.z * sin(angle);
  double newz = -m_ViewPoint.x * sin(angle) + m_ViewPoint.z * cos(angle);

  m_ViewPoint.x = newx;
  m_ViewPoint.z = newz;

  update();
}


void RenderWidget::drawCube(void)
{
  GLfloat cubeCorner[8][3];

  cubeCorner[0][0] = -0.5;  cubeCorner[0][1] = -0.5;  cubeCorner[0][2] = -0.5;
  cubeCorner[1][0] = 0.5;   cubeCorner[1][1] = -0.5;  cubeCorner[1][2] = -0.5;
  cubeCorner[2][0] = 0.5;   cubeCorner[2][1] = 0.5;   cubeCorner[2][2] = -0.5;
  cubeCorner[3][0] = -0.5;  cubeCorner[3][1] = 0.5;   cubeCorner[3][2] = -0.5;
  cubeCorner[4][0] = -0.5;  cubeCorner[4][1] = -0.5;  cubeCorner[4][2] = 0.5;
  cubeCorner[5][0] = 0.5;   cubeCorner[5][1] = -0.5;  cubeCorner[5][2] = 0.5;
  cubeCorner[6][0] = 0.5;   cubeCorner[6][1] = 0.5;   cubeCorner[6][2] = 0.5;
  cubeCorner[7][0] = -0.5;  cubeCorner[7][1] = 0.5;   cubeCorner[7][2] = 0.5;

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glLineWidth(3);
  glBegin(GL_QUADS);

  glColor3f(0.0, 0.0, 0.0);   // blue
  glVertex3fv(cubeCorner[3]);
  glVertex3fv(cubeCorner[2]);
  glVertex3fv(cubeCorner[1]);
  glVertex3fv(cubeCorner[0]);

  glColor3f(1.0, 1.0, 0.0);  // yellow
  glVertex3fv(cubeCorner[1]);
  glVertex3fv(cubeCorner[5]);
  glVertex3fv(cubeCorner[4]);
  glVertex3fv(cubeCorner[0]);

  glColor3f(0.0, 1.0, 1.0);
  glVertex3fv(cubeCorner[3]);
  glVertex3fv(cubeCorner[7]);
  glVertex3fv(cubeCorner[6]);
  glVertex3fv(cubeCorner[2]);

  glColor3f(1.0, 0.0, 0.0);   // red
  glVertex3fv(cubeCorner[4]);
  glVertex3fv(cubeCorner[5]);
  glVertex3fv(cubeCorner[6]);
  glVertex3fv(cubeCorner[7]);

  glColor3f(1.0, 0.0, 1.0);
  glVertex3fv(cubeCorner[4]);
  glVertex3fv(cubeCorner[7]);
  glVertex3fv(cubeCorner[3]);
  glVertex3fv(cubeCorner[0]);

  glColor3f(0.0, 1.0, 0.0);   // green
  glVertex3fv(cubeCorner[2]);
  glVertex3fv(cubeCorner[6]);
  glVertex3fv(cubeCorner[5]);
  glVertex3fv(cubeCorner[1]);
  glEnd();

  glFlush();
}