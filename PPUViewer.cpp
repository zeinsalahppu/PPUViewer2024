//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as 
// this commented part is listed
//
// Last modified by: Zein Salah, on 23.02.2024
//


#include "PPUViewer.h"
#include "RenderWidget.h"

#include <QtWidgets>

PPUViewer::PPUViewer()
{
  m_RenderWidget = new RenderWidget;

  QGridLayout* mainLayout = new QGridLayout;
  mainLayout->addWidget(m_RenderWidget, 0, 0, 1, 4);
  setLayout(mainLayout);

  setWindowTitle(tr("PPUViewer"));

  m_ZoomInButton = new QPushButton("Zoom In");
  m_ZoomInButton->setObjectName(QStringLiteral("ZoomInButton"));
  mainLayout->addWidget(m_ZoomInButton);
  connect(m_ZoomInButton, SIGNAL(pressed()), m_RenderWidget, SLOT(zoomIn()));

  m_ZoomOutButton = new QPushButton("Zoom Out");
  m_ZoomOutButton->setObjectName(QStringLiteral("ZoomOutButton"));
  mainLayout->addWidget(m_ZoomOutButton);
  connect(m_ZoomOutButton, SIGNAL(pressed()), m_RenderWidget, SLOT(zoomOut()));

  m_RotateButton = new QPushButton("Rotate");
  m_RotateButton->setObjectName(QStringLiteral("RotateButton"));
  mainLayout->addWidget(m_RotateButton);
  connect(m_RotateButton, SIGNAL(pressed()), m_RenderWidget, SLOT(rotateAboutY()));
}
