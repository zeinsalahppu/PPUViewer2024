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
#include "baselib/Matrix4D.h"


#include <iostream>


RenderWidget::RenderWidget(QWidget* parent) : QOpenGLWidget(parent)
{
  m_ViewPoint.x = 3.0;
  m_ViewPoint.y = 3.0;
  m_ViewPoint.z = 3.0;

  m_UpDirection = gris::Vector3D(0, 1, 0);

  m_ProjectionType = Perspective;

  //m_Mesh.LoadMeshFile("d:/3d models/sax.3ds");
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
//  gluPerspective(25.0, 1.0, 0.1, 5000.0);
}


void RenderWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if (m_ProjectionType == Perspective)
    gluPerspective(25.0, 1.0, 0.1, 5000.0);
  else
    glOrtho(-1.3, 1.3, -1.3, 1.3, -2.0, 10000.0);

  gluLookAt(m_ViewPoint.x, m_ViewPoint.y, m_ViewPoint.z,      /* view point */
    0.0, 0.0, 0.0,      /* ref point */
    m_UpDirection.x(), m_UpDirection.y(), m_UpDirection.z());      /* up direction is positive y-axis */

  //drawCube();
  //drawCubeWithLighting();
  drawRGBCube();
  //renderMesh(&m_Mesh);
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
  angle = angle / 180 * M_PI;

//std::cout << "Rotating about X by " << angle << "\n";

  Vector3D viewDir = gris::Point3D(0, 0, 0) - gris::Point3D(m_ViewPoint.x, m_ViewPoint.y, m_ViewPoint.z);
  Vector3D rightDir = viewDir ^ m_UpDirection;
  rightDir.normalize();

  Matrix4D rot_Matrix = Matrix4D::Rotate(rightDir, angle);

  gris::Point3D vp = gris::Point3D(m_ViewPoint.x, m_ViewPoint.y, m_ViewPoint.z);

  vp = rot_Matrix * vp;

  m_ViewPoint.x = vp.x();
  m_ViewPoint.y = vp.y();
  m_ViewPoint.z = vp.z();

  m_UpDirection = rot_Matrix * m_UpDirection;
  m_UpDirection.normalize();

  update();
}


void RenderWidget::rotateAboutY(double angle)
{
  angle = angle / 180 * M_PI;

//  std::cout << "Rotating about Y by " << angle << "\n";

  Matrix4D rot_Matrix = Matrix4D::Rotate(m_UpDirection, angle);

  gris::Point3D vp = gris::Point3D(m_ViewPoint.x, m_ViewPoint.y, m_ViewPoint.z);

  vp = rot_Matrix * vp;

  m_ViewPoint.x = vp.x();
  m_ViewPoint.y = vp.y();
  m_ViewPoint.z = vp.z();

  update();
}


void RenderWidget::changeProjection(int prjtype)
{

  if (prjtype == 2)
    m_ProjectionType = Ortho;
  else
    m_ProjectionType = Perspective;

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


void RenderWidget::drawCubeWithLighting(void)
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

  GLfloat light_position[] = { 100.0, 100.0, 100.0, 0.0 };
  GLfloat light_ambient[] = { 0.15, 0.15, 0.15, 1.0 };
  GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glLineWidth(3);

  glBegin(GL_QUADS);
    // brass
    GLfloat mat_ambient[] = { 0.329412f, 0.223529f, 0.027451f, 1.0f };
    GLfloat mat_diffuse[] = { 0.780392f, 0.568627f, 0.113725f, 1.0f };
    GLfloat mat_specular[] = { 0.992157f, 0.941176f, 0.807843f, 1.0f };
    GLfloat mat_shininess[] = { 27.8974f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glNormal3fv(cubeCorner[3]);
    glVertex3fv(cubeCorner[3]);
    glNormal3fv(cubeCorner[2]);
    glVertex3fv(cubeCorner[2]);
    glNormal3fv(cubeCorner[1]);
    glVertex3fv(cubeCorner[1]);
    glNormal3fv(cubeCorner[0]);
    glVertex3fv(cubeCorner[0]);

    glNormal3fv(cubeCorner[1]);
    glVertex3fv(cubeCorner[1]);
    glNormal3fv(cubeCorner[5]);
    glVertex3fv(cubeCorner[5]);
    glNormal3fv(cubeCorner[4]);
    glVertex3fv(cubeCorner[4]);
    glNormal3fv(cubeCorner[0]);
    glVertex3fv(cubeCorner[0]);

    glNormal3fv(cubeCorner[3]);
    glVertex3fv(cubeCorner[3]);
    glNormal3fv(cubeCorner[7]);
    glVertex3fv(cubeCorner[7]);
    glNormal3fv(cubeCorner[6]);
    glVertex3fv(cubeCorner[6]);
    glNormal3fv(cubeCorner[2]);
    glVertex3fv(cubeCorner[2]);

    glNormal3fv(cubeCorner[4]);
    glVertex3fv(cubeCorner[4]);
    glNormal3fv(cubeCorner[5]);
    glVertex3fv(cubeCorner[5]);
    glNormal3fv(cubeCorner[6]);
    glVertex3fv(cubeCorner[6]);
    glNormal3fv(cubeCorner[7]);
    glVertex3fv(cubeCorner[7]);

    glNormal3fv(cubeCorner[4]);
    glVertex3fv(cubeCorner[4]);
    glNormal3fv(cubeCorner[7]);
    glVertex3fv(cubeCorner[7]);
    glNormal3fv(cubeCorner[3]);
    glVertex3fv(cubeCorner[3]);
    glNormal3fv(cubeCorner[0]);
    glVertex3fv(cubeCorner[0]);

    glNormal3fv(cubeCorner[2]);
    glVertex3fv(cubeCorner[2]);
    glNormal3fv(cubeCorner[6]);
    glVertex3fv(cubeCorner[6]);
    glNormal3fv(cubeCorner[5]);
    glVertex3fv(cubeCorner[5]);
    glNormal3fv(cubeCorner[1]);
    glVertex3fv(cubeCorner[1]);
  glEnd();

  glFlush();
}


void RenderWidget::drawRGBCube(void)
{
  GLfloat cubeCorner[8][3];
  GLfloat cubeCornerColor[8][3];

  cubeCorner[0][0] = -0.5;  cubeCorner[0][1] = -0.5;  cubeCorner[0][2] = -0.5;
  cubeCorner[1][0] = 0.5;   cubeCorner[1][1] = -0.5;  cubeCorner[1][2] = -0.5;
  cubeCorner[2][0] = 0.5;   cubeCorner[2][1] = 0.5;   cubeCorner[2][2] = -0.5;
  cubeCorner[3][0] = -0.5;  cubeCorner[3][1] = 0.5;   cubeCorner[3][2] = -0.5;
  cubeCorner[4][0] = -0.5;  cubeCorner[4][1] = -0.5;  cubeCorner[4][2] = 0.5;
  cubeCorner[5][0] = 0.5;   cubeCorner[5][1] = -0.5;  cubeCorner[5][2] = 0.5;
  cubeCorner[6][0] = 0.5;   cubeCorner[6][1] = 0.5;   cubeCorner[6][2] = 0.5;
  cubeCorner[7][0] = -0.5;  cubeCorner[7][1] = 0.5;   cubeCorner[7][2] = 0.5;

  cubeCornerColor[0][0] = 0.0;  cubeCornerColor[0][1] = 0.0;  cubeCornerColor[0][2] = 0.0;  //black
  cubeCornerColor[1][0] = 0.0;  cubeCornerColor[1][1] = 1.0;  cubeCornerColor[1][2] = 0.0;  //green
  cubeCornerColor[2][0] = 0.0;  cubeCornerColor[2][1] = 1.0;  cubeCornerColor[2][2] = 1.0;  //cyan
  cubeCornerColor[3][0] = 0.0;  cubeCornerColor[3][1] = 0.0;  cubeCornerColor[3][2] = 1.0;  //blue
  cubeCornerColor[4][0] = 1.0;  cubeCornerColor[4][1] = 0.0;  cubeCornerColor[4][2] = 0.0;  //red
  cubeCornerColor[5][0] = 1.0;  cubeCornerColor[5][1] = 1.0;  cubeCornerColor[5][2] = 0.0;  //yellow
  cubeCornerColor[6][0] = 1.0;  cubeCornerColor[6][1] = 1.0;  cubeCornerColor[6][2] = 1.0;  //white
  cubeCornerColor[7][0] = 1.0;  cubeCornerColor[7][1] = 0.0;  cubeCornerColor[7][2] = 1.0;  //magenta

  glLineWidth(3);
  glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3fv(cubeCorner[0]);
    glVertex3f(-0.5, -0.5, 1.0);

    glVertex3fv(cubeCorner[0]);
    glVertex3f(-0.5, 1.0, -0.5);

    glVertex3fv(cubeCorner[0]);
    glVertex3f(1.0, -0.5, -0.5);
  glEnd();

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glLineWidth(3);
  glBegin(GL_QUADS);

  glColor3fv(cubeCornerColor[3]);
  glVertex3fv(cubeCorner[3]);
  glColor3fv(cubeCornerColor[2]);
  glVertex3fv(cubeCorner[2]);
  glColor3fv(cubeCornerColor[1]);
  glVertex3fv(cubeCorner[1]);
  glColor3fv(cubeCornerColor[0]);
  glVertex3fv(cubeCorner[0]);

  glColor3fv(cubeCornerColor[1]);
  glVertex3fv(cubeCorner[1]);
  glColor3fv(cubeCornerColor[5]);
  glVertex3fv(cubeCorner[5]);
  glColor3fv(cubeCornerColor[4]);
  glVertex3fv(cubeCorner[4]);
  glColor3fv(cubeCornerColor[0]);
  glVertex3fv(cubeCorner[0]);

  glColor3fv(cubeCornerColor[3]);
  glVertex3fv(cubeCorner[3]);
  glColor3fv(cubeCornerColor[7]);
  glVertex3fv(cubeCorner[7]);
  glColor3fv(cubeCornerColor[6]);
  glVertex3fv(cubeCorner[6]);
  glColor3fv(cubeCornerColor[2]);
  glVertex3fv(cubeCorner[2]);

  glColor3fv(cubeCornerColor[4]);
  glVertex3fv(cubeCorner[4]);
  glColor3fv(cubeCornerColor[5]);
  glVertex3fv(cubeCorner[5]);
  glColor3fv(cubeCornerColor[6]);
  glVertex3fv(cubeCorner[6]);
  glColor3fv(cubeCornerColor[7]);
  glVertex3fv(cubeCorner[7]);

  glColor3fv(cubeCornerColor[4]);
  glVertex3fv(cubeCorner[4]);
  glColor3fv(cubeCornerColor[7]);
  glVertex3fv(cubeCorner[7]);
  glColor3fv(cubeCornerColor[3]);
  glVertex3fv(cubeCorner[3]);
  glColor3fv(cubeCornerColor[0]);
  glVertex3fv(cubeCorner[0]);

  glColor3fv(cubeCornerColor[2]);
  glVertex3fv(cubeCorner[2]);
  glColor3fv(cubeCornerColor[6]);
  glVertex3fv(cubeCorner[6]);
  glColor3fv(cubeCornerColor[5]);
  glVertex3fv(cubeCorner[5]);
  glColor3fv(cubeCornerColor[1]);
  glVertex3fv(cubeCorner[1]);
  glEnd();

  glFlush();
}


void RenderWidget::renderMesh(MeshModel* mshModel)
{
  glEnable(GL_DEPTH_TEST);

  GLfloat light_position[] = { 100.0, 100.0, 100.0, 0.0 };
  GLfloat light_ambient[] = { 0.15, 0.15, 0.15, 1.0 };
  GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

  //// messing
  //GLfloat mat_ambient[] = { 0.33, 0.22, 0.03, 1.0 };
  //GLfloat mat_diffuse[] = { 0.78, 0.57, 0.11, 1.0 };
  //GLfloat mat_specular[] = { 0.99, 0.94, 0.81, 1.0 };
  //GLfloat mat_shininess[] = { 28.0 };

  //// gold
  //GLfloat mat_ambient[] = { 0.24725f, 0.1995f, 0.0745f, 1.0f };
  //GLfloat mat_diffuse[] = { 0.75164f, 0.60648f, 0.22648f, 1.0f };
  //GLfloat mat_specular[] = { 0.628281f, 0.555802f, 0.366065f, 1.0f };
  //GLfloat mat_shininess[] = { 51.2 };

  // brass
  GLfloat mat_ambient[] = { 0.329412f, 0.223529f, 0.027451f, 1.0f };
  GLfloat mat_diffuse[] = { 0.780392f, 0.568627f, 0.113725f, 1.0f };
  GLfloat mat_specular[] = { 0.992157f, 0.941176f, 0.807843f, 1.0f };
  GLfloat mat_shininess[] = { 27.8974f };

  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

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

    glColor3f(1.0, 0.0, 0.0);
    glNormal3f(mshModel->GetNormal(v0).x(), mshModel->GetNormal(v0).y(), mshModel->GetNormal(v0).z());
    glVertex3f(mshModel->GetVertex(v0).x(), mshModel->GetVertex(v0).y(), mshModel->GetVertex(v0).z());


    glNormal3f(mshModel->GetNormal(v1).x(), mshModel->GetNormal(v1).y(), mshModel->GetNormal(v1).z());
    glVertex3f(mshModel->GetVertex(v1).x(), mshModel->GetVertex(v1).y(), mshModel->GetVertex(v1).z());

    glNormal3f(mshModel->GetNormal(v2).x(), mshModel->GetNormal(v2).y(), mshModel->GetNormal(v2).z());
    glVertex3f(mshModel->GetVertex(v2).x(), mshModel->GetVertex(v2).y(), mshModel->GetVertex(v2).z());
  }
  glEnd();

  glDisable(GL_BLEND);
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);


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
  //   std::cout << "Mouse pressed buttom is: " << event->button() << std::endl;

  if (event->button() == LeftButton)    IS_LeftButton = true;
  if (event->button() == MiddleButton)  IS_MiddleButton = true;
  if (event->button() == RightButton)   IS_RightButton = true;
};


void RenderWidget::mouseMoveEvent(QMouseEvent *event)
{
  int dx = event->x() - m_LastMouseX;
  int dy = event->y() - m_LastMouseY;
  double m_TranslateStep = 1;

  if (IS_LeftButton && !IS_MiddleButton)
  {
    rotateAboutY((double)dx / 2);
    rotateAboutX((double)dy / 2);
  }

  m_LastMouseX = event->x();
  m_LastMouseY = event->y();
};


void RenderWidget::wheelEvent(QWheelEvent * event)
{

};