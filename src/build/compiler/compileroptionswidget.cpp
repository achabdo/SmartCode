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

#include <QHBoxLayout>
#include <QListWidget>
#include <QTreeWidget>
#include <QComboBox>
#include <QLabel>
#include <QTextEdit>

#include "compileroptionswidget.h"
#include "compileroptionscategory.h"
#include "compileroption.h"

CompilerOptionsWidget::CompilerOptionsWidget(QWidget *parent) : QWidget(parent)

{
  QVBoxLayout * layout = new QVBoxLayout;
  QHBoxLayout * flagslayout = new QHBoxLayout;

  categoriesWidget = new QListWidget;
  optionsWidget = new QTreeWidget;
  QLabel * label = new QLabel(tr("Additional flags"));
  addFlagsEdit = new QTextEdit;

  optionsWidget->setHeaderLabels(QStringList()<<"Text"<<"Flags");
  optionsWidget->setHeaderHidden(true);

  flagslayout->addWidget(categoriesWidget);
  flagslayout->addWidget(optionsWidget);

  layout->addLayout(flagslayout);
  layout->addWidget(label);
  layout->addWidget(addFlagsEdit);

  setLayout(layout);

  connect(categoriesWidget,SIGNAL(currentRowChanged(int)),this,SLOT(showOptions(int)));
}


QStringList CompilerOptionsWidget::flags()
{
//  QStringList _flags;

//  for(int row = 0; row < _categories.count();row++)
//    {
//      foreach(CompilerOption *option,_categories.at(row)->toCompilerOptions())

//        {
//          int currentFlag = option->currentFlag();

//          if(option->defaultFlag() != currentFlag)
//            _flags << option->flags()[currentFlag];
//        }
//    }

//  _flags << addFlagsEdit->toPlainText().split(QLatin1Char(" "),QString::SkipEmptyParts);
//  return _flags;
}

bool CompilerOptionsWidget::flagsChanged()
{
  foreach(QString actFlag,actFlags)
    {
      for(int row = 0; row < _categories.count();row++)
        {
          foreach(CompilerOption *option,_categories.at(row)->toCompilerOptions())

            {
              QList<Flag*> optFlags = option->flags();

              for(int i = 0; i< optFlags.count();i++)
                {
                  Flag *flag = optFlags.at(i);

                  if(flag->arg() == actFlag && option->currentFlag() != i)
                    return true;
                }
            }
        }
    }

  return false;
}

void CompilerOptionsWidget::setCompilerOptionsCategories(const CompilerOptionsCategories &categories)
{
  categoriesWidget->clear();

  _categories = categories;

  foreach(CompilerOptionsCategory *category,_categories)
    {
      categoriesWidget->addItem(category->name());
    }
}

void CompilerOptionsWidget::setActivatedFlags(const QStringList &activatedFlags)
{
//  actFlags = activatedFlags;

//  QStringList baseFlags;

//  foreach(CompilerOptionsCategory* category ,_categories)
//    {
//      foreach(CompilerOption* option ,category)
//        {
//          foreach(Flag * flag,option->flags())
//            {
//              QString flagText = flag->arg();

//              if(!flagText.isNull())
//                baseFlags<<flagText;
//            }
//        }
//    }

//  QStringList additionalFlags;

//  foreach(QString flag,actFlags)
//    {
//      if(!baseFlags.contains(flag))
//        {
//          additionalFlags << flag;
//        }
//    }

//  addFlagsEdit->setText(additionalFlags.join(QLatin1Char("")));
}

CompilerOptionsWidget::~CompilerOptionsWidget()
{

}

void CompilerOptionsWidget::showOptions(int row)
{
//  optionsWidget->clear();

//  foreach(CompilerOption *option,_categories.at(row)->toCompilerOptions())

//    {
//      QTreeWidgetItem * item = new QTreeWidgetItem;

//      QComboBox * flagsBox = new QComboBox;

//      //      connect(flagsBox,SIGNAL(currentIndexChanged(int)),this,SLOT(saveCompilerOption()));

//      QList<Flag*> optFlags = option->flags();

//      for(int i = 0; i< optFlags.count();i++)
//        {
//          Flag *flag = optFlags.at(i);

//          QString text;

//          text += flag->description();
//          if(!flag->arg().isNull())
//            text += "(" + flag->arg() + ")";

//          flagsBox->addItem(text);

//        }

//      flagsBox->setCurrentIndex(option->defaultFlag());
//      connect(flagsBox,SIGNAL(currentIndexChanged(int)),option,SLOT(setCurrentFlag(int)));

//      for(int i = 0; i< optFlags.count();i++)
//        {
//          if(actFlags.contains(flag->arg()))
//            flagsBox->setCurrentIndex(i);
//        }

//      item->setText(0,option->text());

//      optionsWidget->addTopLevelItem(item);
//      optionsWidget->setItemWidget(item,1,flagsBox);
//    }
}


