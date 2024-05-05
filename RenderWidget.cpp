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
#include <QMouseEvent>


#include <iostream>


RenderWidget::RenderWidget(QWidget* parent) : QOpenGLWidget(parent)
{
  m_ViewPoint.x = 100.0;
  m_ViewPoint.y = 100.0;
  m_ViewPoint.z = 100.0;

  m_Mesh.LoadMeshFile("d:/3d models/sax.3ds");
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
  gluPerspective(25.0, 1.0, 0.1, 5000.0);
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

  //drawCube();
  renderMesh(&m_Mesh);
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


void RenderWidget::rotateAboutX(double angle)
{
  // to be implemented
  update();
}


void RenderWidget::rotateAboutY(double angle)
{
  angle = angle / 180 * M_PI;

 // std::cout << "Rotating about Y by " << angle << "\n";

  double newx = m_ViewPoint.x*cos(angle) + m_ViewPoint.z*sin(angle);
  double newz = -m_ViewPoint.x*sin(angle) + m_ViewPoint.z*cos(angle);

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


void RenderWidget::renderMesh(MeshModel* mshModel)
{
  glEnable(GL_DEPTH_TEST);

  glShadeModel(GL_FLAT);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  long numTrg = mshModel->GetNumTriangles();
  long v0, v1, v2;

  glBegin(GL_TRIANGLES);
  for (long i = 0; i < numTrg; ++i)
  {
    v0 = mshModel->GetTriangle(i, 0);
    v1 = mshModel->GetTriangle(i, 1);
    v2 = mshModel->GetTriangle(i, 2);

    glColor3f(1.0, 0.5, 0.5);
    glNormal3f(mshModel->GetNormal(v0).x(), mshModel->GetNormal(v0).y(), mshModel->GetNormal(v0).z());
    glVertex3f(mshModel->GetVertex(v0).x(), mshModel->GetVertex(v0).y(), mshModel->GetVertex(v0).z());


    glNormal3f(mshModel->GetNormal(v1).x(), mshModel->GetNormal(v1).y(), mshModel->GetNormal(v1).z());
    glVertex3f(mshModel->GetVertex(v1).x(), mshModel->GetVertex(v1).y(), mshModel->GetVertex(v1).z());

    glNormal3f(mshModel->GetNormal(v2).x(), mshModel->GetNormal(v2).y(), mshModel->GetNormal(v2).z());
    glVertex3f(mshModel->GetVertex(v2).x(), mshModel->GetVertex(v2).y(), mshModel->GetVertex(v2).z());
  }
  glEnd();

  glFlush();
}


void RenderWidget::mouseReleaseEvent(QMouseEvent *event)
{
  IS_LeftButton = IS_MiddleButton = IS_RightButton = false;
}


void RenderWidget::mousePressEvent(QMouseEvent *event)
{
  m_LastMouseX = event->x();
  m_LastMouseY = event->y();

 // std::cout << "Mouse pressed buttom is: " << event->button() << std::endl;

  if (event->button() == LeftButton)    IS_LeftButton = true;
  if (event->button() == MiddleButton)  IS_MiddleButton = true;
  if (event->button() == RightButton)   IS_RightButton = true;
};


void RenderWidget::mouseMoveEvent(QMouseEvent *event)
{
  int dx = event->x() - m_LastMouseX;
  int dy = event->y() - m_LastMouseY;

  if (IS_LeftButton && !IS_MiddleButton)
  {
    rotateAboutY(-(double)dx / 2);
    rotateAboutX(-(double)dy / 2);
  }

  m_LastMouseX = event->x();
  m_LastMouseY = event->y();
};


void RenderWidget::wheelEvent(QWheelEvent * event)
{

};