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

#include "configwizard.h"
#include "ui_configwizard.h"

#include <QDir>

#include "configmanager.h"
#include "config.h"

ConfigWizard::ConfigWizard(ConfigManager *cManager, QWidget *parent) :
  QWizardPage(parent),
  ui(new Ui::ConfigWizard)
{
  ui->setupUi(this);

  configManager = cManager;
}

ConfigWizard::~ConfigWizard()
{
  delete ui;
}

void  ConfigWizard::initializePage()
{
  const QString projectPath = field("ProjectDir").toString() + "/" + field("ProjectName").toString() + "/";

  ui->debugOutputDir->setText( projectPath  + "debug");
  ui->releaseOutputdir->setText( projectPath + "release");

  ui->debugObjOutputdir->setText( projectPath   + "debug/obj");
  ui->releaseObjOutputdir->setText( projectPath + "release/obj");
}

bool ConfigWizard::validatePage()
{
  return ui->debugConfig->isChecked() || ui->releaseConfig->isChecked();
}

QList<Config *> ConfigWizard::configs()
{
  QList<Config *> _configs;

  if(ui->debugConfig->isChecked())
    {
      Config * debug = configManager->addDebugConfig();
      _configs << debug;
    }

  if(ui->releaseConfig->isChecked())
    {
      Config * release = configManager->addReleaseConfig();
      _configs <<release;
    }

  return _configs;
}

