//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as 
// this commented part is listed
//
// Last modified by: Zein Salah, on 26.02.2022
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
}
