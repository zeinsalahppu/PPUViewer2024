//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as 
// this commented part is listed
//
// Last modified by: Zein Salah, on 26.02.2022
//


#include "RenderWidget.h"
#include <glut.h>
#include <QPainter>

RenderWidget::RenderWidget(QWidget* parent) : QOpenGLWidget(parent)
{

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
  gluOrtho2D(0.0, 200.0, 0.0, 200.0);
  // glOrtho(-2.0, 2.0, -2.0, 2.0, -100, 100);

}


void RenderWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  drawHouse(1, 1, 0);

  glPushMatrix();
  glTranslatef(60.0, 30.0, 0.0);
  drawHouse(1, 0, 1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(10.0, 50.0, 0.0);
  drawHouse(1, 0, 0);
  glPopMatrix();



  // ******************************************************************************

  //glRotatef(30.0, 0.0, 0.0, 1.0);
  //drawHouse(0, 1, 0);


  //glTranslatef(75.0, 75.0, 0.0);
  //glRotatef(30.0, 0.0, 0.0, 1.0);
  //glTranslatef(-75.0, -75.0, 0.0);
  //drawHouse(0, 1, 0);

}


void RenderWidget::drawHouse(float r, float g, float b)
{	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_POLYGON);
      glColor3f(r, g, b); // yellow
      glVertex2i(50, 50);
      glVertex2i(100, 50);
      glVertex2i(100, 80);
      glVertex2i(75, 100);
      glVertex2i(50, 80);
	glEnd();

	glBegin(GL_QUADS);
      glColor3f(0, 0, 0); 
      glVertex2i(70, 52);
      glVertex2i(80, 52);
      glVertex2i(80, 75);
      glVertex2i(70, 75);
	glEnd();
	
}


void RenderWidget::resizeGL(int width, int height)
{
  int side = qMin(width, height);
  glViewport((width - side) / 2, (height - side) / 2, side, side);

  //    glViewport(0, 0, width, height);
}
