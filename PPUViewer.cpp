//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as 
// this commented part is listed
//
// Last modified by: Zein Salah, on 23.02.2024
//

#include <QtWidgets>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QLabel>

#include "PPUViewer.h"
#include "RenderWidget.h"


PPUViewer::PPUViewer()
{
  QVBoxLayout *vLayout = new QVBoxLayout();

  m_RenderWidget = new RenderWidget;

//  QGridLayout* mainLayout = new QGridLayout;
//  mainLayout->addWidget(m_RenderWidget, 0, 0, 1, 4);
//  setLayout(mainLayout);

  
  setLayout(vLayout);

  QHBoxLayout *hLayout1 = new QHBoxLayout();
  hLayout1->addWidget(m_RenderWidget);
  vLayout->addLayout(hLayout1);

  setWindowTitle(tr("PPUViewer"));

  QHBoxLayout *hLayout2 = new QHBoxLayout();
  vLayout->addLayout(hLayout2);

  QVBoxLayout *vLayout20 = new QVBoxLayout();
  hLayout2->addLayout(vLayout20, 1);


  m_ZoomInButton = new QPushButton("Zoom In");
  m_ZoomInButton->setObjectName(QStringLiteral("ZoomInButton"));
  vLayout20->addWidget(m_ZoomInButton);
  connect(m_ZoomInButton, SIGNAL(pressed()), m_RenderWidget, SLOT(zoomIn()));

  m_ZoomOutButton = new QPushButton("Zoom Out");
  m_ZoomOutButton->setObjectName(QStringLiteral("ZoomOutButton"));
  vLayout20->addWidget(m_ZoomOutButton);
  connect(m_ZoomOutButton, SIGNAL(pressed()), m_RenderWidget, SLOT(zoomOut()));

  m_RotateButton = new QPushButton("Rotate");
  m_RotateButton->setObjectName(QStringLiteral("RotateButton"));
//  hLayout2->addWidget(m_RotateButton);
  connect(m_RotateButton, SIGNAL(pressed()), m_RenderWidget, SLOT(rotateAboutY()));

  QGridLayout* comboLayout = new QGridLayout;

  QVBoxLayout *vLayout21 = new QVBoxLayout();
  hLayout2->addLayout(comboLayout, 3);

  QLabel *selectionLabel = new QLabel("Projection Mode");

  QComboBox *projectionModeComboBox = new QComboBox();
  projectionModeComboBox->addItem("Perspective");
  projectionModeComboBox->addItem("Orthogonal");
  vLayout21->addWidget(projectionModeComboBox);

  comboLayout->addWidget(selectionLabel, 0, 0, 1, 4);
  comboLayout->addWidget(projectionModeComboBox, 0, 1, 1, 4);


  QLabel *selectionLabel2 = new QLabel("Rendering Mode");

  QComboBox *renderingModeComboBox = new QComboBox();
  renderingModeComboBox->addItem("Wire Frame");
  renderingModeComboBox->addItem("Flat Shading");
  renderingModeComboBox->addItem("Lighting");
  renderingModeComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

  comboLayout->addWidget(selectionLabel2, 1, 0, 1, 4);
  comboLayout->addWidget(renderingModeComboBox, 1, 1, 1, 4);

}
