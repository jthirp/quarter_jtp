/**************************************************************************\
 *
 *  This file is part of the SIM Quarter extension library for Coin.
 *  Copyright (C) 1998-2007 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License ("GPL") version 2
 *  as published by the Free Software Foundation.  See the file COPYING
 *  at the root directory of this source distribution for additional
 *  information about the GNU GPL.
 *
 *  For using SIM Quarter with software that can not be combined with
 *  the GNU GPL, and for taking advantage of the additional benefits of
 *  our support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion AS, Bygd�y all� 5, N-0257 Oslo, NORWAY. (www.sim.no)
 *
\**************************************************************************/

#include "MdiMainWindow.h"
#include "MdiQuarterWidget.h"

#include <QtGui>
#include <QAction>
#include <QDropEvent>
#include <QCloseEvent>
#include <QDragEnterEvent>

using namespace SIM::Coin3D::Quarter;

MdiMainWindow::MdiMainWindow(void)
{
  this->firstwidget = 0;
  this->workspace = new QWorkspace;
  this->setCentralWidget(this->workspace);
  this->setAcceptDrops(true);
  this->setWindowTitle(tr("Quarter MDI example"));
  
  QMenu * filemenu = this->menuBar()->addMenu(tr("&File"));
  QMenu * windowmenu = this->menuBar()->addMenu(tr("&Windows"));

  QAction * fileopenaction = new QAction(tr("&Open"), this);
  QAction * fileexitaction = new QAction(tr("E&xit"), this);
  QAction * tileaction = new QAction(tr("Tile"), this);
  QAction * cascadeaction = new QAction(tr("Cascade"), this);

  filemenu->addAction(fileopenaction);
  filemenu->addAction(fileexitaction);
  windowmenu->addAction(tileaction);
  windowmenu->addAction(cascadeaction);

  this->connect(fileopenaction, SIGNAL(triggered()), this, SLOT(open()));
  this->connect(fileexitaction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
  this->connect(tileaction, SIGNAL(triggered()), this->workspace, SLOT(tile()));
  this->connect(cascadeaction, SIGNAL(triggered()), this->workspace, SLOT(cascade()));

  QSignalMapper * windowmapper = new QSignalMapper(this);
  this->connect(windowmapper, SIGNAL(mapped(QWidget *)),
                this->workspace, SLOT(setActiveWindow(QWidget *)));
}

MdiMainWindow::~MdiMainWindow()
{
  
}

void 
MdiMainWindow::dragEnterEvent(QDragEnterEvent * event)
{
  // just accept anything...
  event->acceptProposedAction();
}

void 
MdiMainWindow::dropEvent(QDropEvent * event)
{
  const QMimeData * mimedata = event->mimeData();
  if (mimedata->hasUrls()) { 
    QString path = mimedata->urls().takeFirst().path();
    this->open(path);
  }
}

void 
MdiMainWindow::closeEvent(QCloseEvent * event)
{
  this->workspace->closeAllWindows();
}

void 
MdiMainWindow::open(void)
{
  this->open(QFileDialog::getOpenFileName(this));
}

void 
MdiMainWindow::open(const QString & filename)
{
  if (!filename.isEmpty()) {
    MdiQuarterWidget * existing = this->findMdiChild(filename);
    if (existing) {
      this->workspace->setActiveWindow(existing);
      return;
    }  
    MdiQuarterWidget * child = this->createMdiChild();
    if (child->loadFile(filename)) {
      this->statusBar()->showMessage(tr("File loaded"), 2000);
      child->show();
    } else {
      child->close();
    }
  }
}

MdiQuarterWidget * 
MdiMainWindow::findMdiChild(const QString & filename)
{
  QString canonicalpath = QFileInfo(filename).canonicalFilePath();
  foreach(QWidget * window, this->workspace->windowList()) {
    MdiQuarterWidget * mdiwidget = (MdiQuarterWidget *) window;
    if (mdiwidget->currentFile() == canonicalpath) {
      return mdiwidget;
    }
  }
  return 0;
}

MdiQuarterWidget * 
MdiMainWindow::createMdiChild(void)
{
  MdiQuarterWidget * widget = new MdiQuarterWidget(NULL, this->firstwidget);
  this->workspace->addWindow(widget);
  
  if (this->firstwidget = 0) {
    this->firstwidget = widget;
  }
  
  return widget;
}