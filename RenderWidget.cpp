//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as 
// this commented part is listed
//
// Last modified by: Zein Salah, on 20.03.2024
//


#include "RenderWidget.h"
#include <glut.h>

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

  //glOrtho(-2.0, 2.0, -2.0, 2.0, -100, 100);
  //gluPerspective(25.0, 1.0, 1.0, 100.0);

}


void RenderWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //glPointSize(10.0);
  //glBegin(GL_POINTS);
  //  glColor3f(1, 0, 0);
  //  glVertex2i(80, 15);
  //  glColor3f(0, 0, 1);
  //  glVertex2i(10, 145);
  //glEnd();

  //glColor3f(0.0, 0.9, 0.2);
  //glBegin(GL_LINES);
  //  glVertex2i(80, 15);
  //  glVertex2i(10, 145);
  //glEnd();

//  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//  glLineWidth(3);

  //glBegin(GL_TRIANGLES);
  //  glColor3f(0.0, 0.0, 1.0);   // green
  //  glVertex2f(100, 200);
  //  glVertex2f(200, 400);
  //  glVertex2f(500, 300);
  //glEnd();


  glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0);   // blue
    glVertex2f(100, 200);
    glColor3f(1.0, 0.0, 0.0);   // red
    glVertex2f(200, 400);
    glColor3f(0.0, 1.0, 0.0);   // green
    glVertex2f(500, 300);
  glEnd();


    glFlush();
}


void RenderWidget::resizeGL(int width, int height)
{
  int side = qMin(width, height);
  glViewport((width - side) / 2, (height - side) / 2, side, side);

//  glViewport(0, 0, width, height);
}


