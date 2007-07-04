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

/*!
  \page inheritui Single Inheritance
  
  This example demonstrate how to create a simple viewer by
  subclassing a generated class form an ui file
*/

#include <Quarter/QuarterWidget.h>
#include <Quarter/QuarterApplication.h>

#include "QuarterViewer.h"

using namespace SIM::Coin3D::Quarter;

int
main(int argc, char ** argv)
{
  // Initializes Quarter (and implicitly also Coin and Qt
  QuarterApplication app(argc, argv);

  QuarterViewer * viewer = new QuarterViewer;
  // Pop up the viewer
  viewer->show();
  // Loop until exit.
  app.exec();
  // Clean up resources.
  delete viewer;
  return 0;
}