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

#include "tabsetting.h"
#include "ui_tabsetting.h"

#include <QTabWidget>
#include <QTreeWidget>
#include <QFileDialog>

#include <QDebug>
#include <QLineEdit>
#include <QToolButton>
#include <QMenu>
#include <QDialogButtonBox>
#include <QFormLayout>

#include "settingsmanager.h"
#include "core_constants.h"

TabSetting::TabSetting(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TabSetting)
{
  ui->setupUi(this);

  addTab();
}

void TabSetting::addTab()
{
  tab = new QTabWidget;
  tab->setTabBarAutoHide(true);
  ui->TabLayout->addWidget(tab);
}

void TabSetting::addItem(const QStringList &labels, int index)
{
  auto item = new QTreeWidgetItem(labels);
  item->setFlags(item->flags()|Qt::ItemIsEditable);
  list(index)->addTopLevelItem(item);
}

void TabSetting::addItems(const QStringList &labels,int index)
{
  foreach(QString label,labels)
    {
     addItem(QStringList()<<label,index);
    }
}

void TabSetting::clear(int mode)
{
  list(mode)->clear();
}

void TabSetting::clearAll()
{
  for(int i = 0 ;i< tab->count();i++)
    {
      clear(i);
  }
}

QTreeWidget* TabSetting::addContent(const QString &name, const QString &element,bool itemHasIcon)

{
  QTreeWidget * listWidget = new QTreeWidget;

  if(itemHasIcon)
  connect(listWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(editItem(QTreeWidgetItem*,int)));

  listWidget->setHeaderHidden(true);

  listWidget->setObjectName("ListWidget");

  int index = tab->addTab(listWidget,name);
  mode.insert(index,element);

  return listWidget;
}

void TabSetting::setCurrentListHeaderLabels(const QStringList &labels)
{
  currentList()->setHeaderHidden(false);
  currentList()->setHeaderLabels(labels);

}

void TabSetting::createAddButtonMenu()
{
  QMenu *menu = new QMenu;

  menu->addAction("Expression",this,SLOT(addCustomVariable()));
  menu->addAction("Greather");
  menu->addAction("Less");
  menu->addAction("Equal");

  ui->add->setMenu(menu);
}

void TabSetting::addCustomVariable()
{
  QDialog dialog;

  auto layout = new QFormLayout;

  auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                        | QDialogButtonBox::Cancel) ;
  QLineEdit varEdit;
  QLineEdit valueEdit;

  layout->insertRow(0,tr("Name"),&varEdit);
  layout->insertRow(1,tr("Value"),&valueEdit);
  layout->insertRow(2,buttonBox);

  connect(buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

  dialog.setLayout(layout);

  dialog.setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

  dialog.exec();
}

QString TabSetting::tabElement(int index) const
{
  return mode.value(index);
}

TabSetting::~TabSetting()
{
  delete ui;
}

QTabWidget * TabSetting::tabWidget() const
{
  return tab;
}

QTreeWidget * TabSetting::currentList() const
{
  return list(tab->currentIndex());
}

QTreeWidget  * TabSetting::list(int index) const
{
  QWidget * widget = tab->widget(index);

  if (QTreeWidget *list = qobject_cast<QTreeWidget*>(widget)) {
      return list;
    }

  return 0;
}

QString TabSetting::itemText(int row,int column,int index) const
{
  return list(index)->topLevelItem(row)->text(column);
}

int TabSetting::listCount(int index) const
{
  return list(index)->topLevelItemCount();
}

QStringList TabSetting::itemsText(int index,int column)
{
  QStringList items;

  for(int row = 0 ; row <  listCount(index) ; row++)
    items << itemText(row,column,index);

  return items;
}


void TabSetting::getPath_clicked()
{
  disconnect(currentlineEdit(),SIGNAL(editingFinished()),0,0);

  QString dir = QFileDialog::getOpenFileName(this,
                                             tr("Open"), QDir::currentPath());

  currentlineEdit()->setText(dir);

  connect(currentlineEdit(),SIGNAL(editingFinished()),this,SLOT(setItemText()));
}

QTreeWidgetItem * TabSetting::currentListItem() const
{
  return currentList()->currentItem();
}

QLineEdit * TabSetting::currentlineEdit()const
{
  QLineEdit * edit = qobject_cast<QLineEdit*>(currentList()->itemWidget(currentListItem(),currentListColumn()));
  return edit;
}

int TabSetting::currentListColumn() const
{
  return currentList()->currentColumn();
}

void TabSetting::setItemText()
{
  currentList()->currentItem()->setText(currentListColumn(),currentlineEdit()->text());
  currentList()->setItemWidget(currentListItem(),currentListColumn(),0);
  currentList()->reset();
}

void TabSetting::editItem(QTreeWidgetItem *item, int column)
{
  QLineEdit *lineEdit;

  lineEdit = new QLineEdit;

  QAction * action = lineEdit->addAction(QIcon(Core::Icon::FOLDER),QLineEdit::TrailingPosition);
  connect(action,SIGNAL(triggered()),this,SLOT(getPath_clicked()));

  lineEdit->setText(item->text(column));
  lineEdit->setSelection(0,item->text(column).length());

  currentList()->setItemWidget(item,column,lineEdit);

  connect(lineEdit,SIGNAL(editingFinished()),this,SLOT(setItemText()));

}

void TabSetting::on_add_clicked()
{
  QTreeWidgetItem * item = new QTreeWidgetItem;
  item->setFlags(item->flags()|Qt::ItemIsEditable);

  item->setText(0,"New Item");

  currentList()->addTopLevelItem(item);

}

void TabSetting::on_del_clicked()
{
  currentList()->takeTopLevelItem(currentItemIndex());
}

void TabSetting::on_clear_clicked()
{
  currentList()->clear();
}

int TabSetting::itemIndex(QTreeWidgetItem *item) const
{
  return currentList()->indexOfTopLevelItem(item);
}

int TabSetting::currentItemIndex() const
{
  return itemIndex(currentList()->currentItem());
}




