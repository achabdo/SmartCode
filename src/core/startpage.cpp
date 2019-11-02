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

#include "startpage.h"
#include "ui_startpage.h"

#include <QSettings>
StartPage::StartPage(QWidget *parent) :
  QScrollArea(parent),
  ui(new Ui::StartPage)
{

  ui->setupUi(this);

  connect(ui->newproject,SIGNAL(clicked()),this,SIGNAL(newProject()));
  connect(ui->openproject,SIGNAL(clicked()),this,SIGNAL(openProject()));

  setupRecentProjectList();
}

StartPage::~StartPage()
{
  delete ui;
}

QListWidget *StartPage::list() const
{
  return ui->listWidget;
}

void StartPage::setupRecentProjectList()
{
  QSettings settings;


  addItems(ui->listWidget,settings.value("Recents projects").toStringList());

}

void StartPage::addItems(QListWidget *listWidget,QStringList texts)
{
  QListWidgetItem *listWidgetItem;

  foreach(QString text,texts)
    {
      listWidgetItem = new QListWidgetItem;

      listWidgetItem->setText(QFileInfo(text).baseName());
      listWidgetItem->setToolTip(text);

      listWidget->addItem(listWidgetItem);
    }
}


void StartPage::on_listWidget_itemClicked(QListWidgetItem *item)
{
  recentClicked(item->toolTip());
}
