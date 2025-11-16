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
//  glEnable(GL_DEPTH_TEST);


  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_QUADS);
    glColor3f(1, 1, 0); // yellow
    glVertex2i(90, 60);
    glVertex2i(90, 80);
    glVertex2i(40, 80);
    glVertex2i(40, 60);
  glEnd();

  glPushMatrix();
  glTranslatef(50.0, 0.0, 0.0);
  glBegin(GL_QUADS);
    glColor3f(1, 0, 1);
    glVertex2i(90, 60);
    glVertex2i(90, 80);
    glVertex2i(40, 80);
    glVertex2i(40, 60);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glMatrixMode(GL_MODELVIEW);
  glTranslatef(50.0, 20.0, 0.0);
  glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex2i(90, 60);
    glVertex2i(90, 80);
    glVertex2i(40, 80);
    glVertex2i(40, 60);
  glEnd();
  glPopMatrix();


  ////******************************************************************************
  //glRotatef(30.0, 0.0, 0.0, 1.0);
  //glBegin(GL_QUADS);
  //glColor3f(0, 1, 0);
  //glVertex2i(40, 60);
  //glVertex2i(40, 80);
  //glVertex2i(90, 80);
  //glVertex2i(90, 60);
  //glEnd();


  //******************************************************************************
  glTranslatef(65.0, 70.0, 0.0);
  glRotatef(30.0, 0.0, 0.0, 1.0);
  glTranslatef(-65.0, -70.0, 0.0);
  glBegin(GL_QUADS);
  glColor3f(0, 1, 0); // green
    glVertex2i(90, 60);
    glVertex2i(90, 80);
    glVertex2i(40, 80);
    glVertex2i(40, 60);
  glEnd();

}


void RenderWidget::resizeGL(int width, int height)
{
  int side = qMin(width, height);
  glViewport((width - side) / 2, (height - side) / 2, side, side);

  //    glViewport(0, 0, width, height);
}
