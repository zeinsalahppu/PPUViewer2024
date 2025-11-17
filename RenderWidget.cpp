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

#include <iostream>

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
  gluOrtho2D(0.0, 600.0, 0.0, 600.0);
  // glOrtho(-2.0, 2.0, -2.0, 2.0, -100, 100);

}


void RenderWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();


  glBegin(GL_LINES);
 //   glColor3f(r, g, b);
    glVertex2i(0, 300);
    glVertex2i(600, 300);
    glVertex2i(300, 0);
    glVertex2i(300, 600);
  glEnd();

  #define PI 3.14159 
 
  float dt = 2 * PI / 12;
  float r = 200;

  for (float t = 0; t < PI; t += dt)
  {
    float x = 300 + r*cos(t);
    float y = 300 + r*sin(t);
    std::cout << t << ":" << x << ", " << y << std::endl;
   
    glPushMatrix();
    glTranslatef(x, y, 0.0);
//    glTranslatef(75.0, 75.0, 0.0);
    glRotatef(t*180/PI- 90, 0.0, 0.0, 1.0);
//    glTranslatef(-75.0, -75.0, 0.0);

    drawHouse(t/6, 0, 0);
    glPopMatrix();
  }

  //for (float t = 0; t < 500; t += 150)
  //{
  //  std::cout << t << std::endl;

  //  glPushMatrix();
  //  glTranslatef(t, t, 0.0);
  //  drawHouse(1, 0, 0);
  //  glPopMatrix();
  //}

  //drawHouse(1, 1, 0); // yellow

  //glPushMatrix();
  //glTranslatef(60.0, 30.0, 0.0);
  //drawHouse(1, 0, 1); // magenta
  //glPopMatrix();

  //glPushMatrix();
  //glTranslatef(10.0, 50.0, 0.0);
  //drawHouse(1, 0, 0);
  //glPopMatrix();

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
      glColor3f(r, g, b);
      glVertex2i(0, 0);
      glVertex2i(50, 0);
      glVertex2i(50, 30);
      glVertex2i(25, 50);
      glVertex2i(0, 30);
	glEnd();

	glBegin(GL_QUADS);
      glColor3f(0, 0, 0); 
      glVertex2i(20, 2);
      glVertex2i(30, 2);
      glVertex2i(30, 25);
      glVertex2i(20, 25);
	glEnd();
	
}


void RenderWidget::resizeGL(int width, int height)
{
  int side = qMin(width, height);
  glViewport((width - side) / 2, (height - side) / 2, side, side);

  //    glViewport(0, 0, width, height);
}
