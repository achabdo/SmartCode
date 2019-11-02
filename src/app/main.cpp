// Copyright (C) 2014  by Achrouf Abdeour <achroufabdenour@gmail.com>
// Auteur Achrouf Abdenour

// This File is part of SmartCode

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program. If not, see http://www.gnu.org/licenses/.

#include <QApplication>
#include <QSettings>
#include <QtWidgets/QSplashScreen>
#include <QTranslator>
#include <QDebug>

#include <QStyleFactory>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
  Q_INIT_RESOURCE(resource);

  QString arg;
  bool open = false;

  QApplication a(argc, argv);
  a.setOrganizationName("Achrouf");
  a.setApplicationName("SmartCode");

  QPixmap pixmap(":/images/splash.png");
  QSplashScreen splash(pixmap);
  splash.show();

  a.processEvents();

  QSettings setting;
  QString lang = setting.value("local").toString();

  QApplication::setStyle(QStyleFactory::create("Fusion"));

//      QPalette p = qApp->palette();
//      p.setColor(QPalette::Window, QColor(53,53,53));
//      p.setColor(QPalette::Window, QColor(4, 14, 59));
//      p.setColor(QPalette::Button, QColor(4, 14, 59));
//      p.setColor(QPalette::Highlight, QColor(142,45,197));
//      p.setColor(QPalette::ButtonText, QColor(255,255,255));
//      p.setColor(QPalette::WindowText, QColor(255,255,255));
//      qApp->setPalette(p);

  QTranslator translator;
  translator.load("local_" + lang,"local");
  a.installTranslator(&translator);

  //
  MainWindow w;
  w.showMaximized();
  w.show();
  splash.finish(&w);
  //

  for (int i = 1; i < argc; ++i) {

      if (!strcmp(argv[i], "-open")) {
          open = true;
        }
      else
        arg = argv[i];
    }

  if(open == true)
    w.open(arg);

  return a.exec();
}

