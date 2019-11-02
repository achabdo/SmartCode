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

#include "compilersettingwidget.h"
#include "ui_compilersettingwidget.h"

#include <QMessageBox>
#include <QComboBox>
#include <QFileDialog>
#include <QMenu>
#include <QFormLayout>

#include <core_constants.h>
#include <tabsettingmanager.h>

#include "compiler/compilersetting.h"

using namespace Core::Compiler;

CompilerSettingWidget::CompilerSettingWidget(CompilerSetting *compilerSetting, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CompilerSettingWidget)
{
  ui->setupUi(this);
  this->compilerSetting = compilerSetting;
  setup();

  connect(ui->compilers,SIGNAL(itemPressed(QTreeWidgetItem*,int)),this,SLOT(activeCompiler(QTreeWidgetItem*,int)));
  ui->compilerProgramsGroup->setVisible(false);
}

CompilerSettingWidget::~CompilerSettingWidget()
{
  delete ui;
}

void CompilerSettingWidget::setSetting(CompilerSetting * s)
{
  compilerSetting = s;
  loadSetting();
}

void CompilerSettingWidget::setupCompilerOptions(QWidget *widget)
{
  ui->compilerOptionsLayout->addWidget(widget);
}

void CompilerSettingWidget::autoDetecteCompilers()
{
  //autoDetecteGCC();
}


void CompilerSettingWidget::setup()
{
  QList<QLineEdit *> compilerGroupEdits = ui->CompilersWidget->findChildren<QLineEdit *>();

//  for(int i = 0;i<compilerGroupEdits.count();i++)
//    compilerGroupEdits[i]->setObjectName(compilerSetting->allSettingsNames()[i]);

  QMenu * addCompilerButtonMenu = new QMenu;

  QList<QPushButton *> compilerGroupButtons = ui->CompilersWidget->findChildren<QPushButton *>(QRegExp("^pushButton"));

  foreach(QPushButton * button,compilerGroupButtons)
    connect(button,SIGNAL(clicked()),this,SLOT(setProgramPath()));

  addCompilerButtonMenu->addAction("GCC");

  connect(addCompilerButtonMenu,SIGNAL(triggered(QAction*)),this,SLOT(addCompiler(QAction*)));
  ui->addCompilerButton->setMenu(addCompilerButtonMenu);

  connect(ui->compilerName,SIGNAL(textChanged(QString)),this,SLOT(updateCurrentCompilerName(QString)));

  tabSettingManager = new TabSettingManager();

  ui->linkerLayout->addWidget(tabSettingManager->tabSetting(TabSettingManager::Linker));
  ui->searchPathsLayout->addWidget(tabSettingManager->tabSetting(TabSettingManager::SearchPaths));
  ui->macrosLayout->addWidget(tabSettingManager->tabSetting(TabSettingManager::BuildVariables));

  autoDetecteCompilers();
}

void CompilerSettingWidget::loadSetting()
{
  ui->cc->setText(compilerSetting->string(CC));
  ui->cxx->setText(compilerSetting->string(CXX));
  ui->make->setText(compilerSetting->string(MAKE));
  ui->dll->setText(compilerSetting->string(SHAREDLIB));
  ui->lib->setText(compilerSetting->string(LIB));
  ui->res->setText(compilerSetting->string(RES));
  ui->dbg->setText(compilerSetting->string(DBG));

  //tabSettingManager->load(this);
}

//void CompilerSettingWidget::on_Compiler_activated(const QString &arg1)
//{

//    compilerSetting->setCompiler( arg1 + ".xml");
//    compilerSetting->load();

//    loadSetting();

//}


void CompilerSettingWidget::saveSetting()
{
  QList<QVariant> settings;

  QList<QLineEdit *> compilerGroupEdits = ui->CompilersWidget->findChildren<QLineEdit *>(QRegExp("^lineEdit"));

  foreach(QLineEdit *edit,compilerGroupEdits)
    {
      settings.append(edit->text());
    }

}

void CompilerSettingWidget::setProgramPath()
{
  QString fileName = QFileDialog::getOpenFileName(this,
                                                  tr("Choose Executable"), QDir::currentPath(), tr("All files(*.*)"));

  QList<QLineEdit *> compilerGroupEdits = ui->CompilersWidget->findChildren<QLineEdit *>(QRegExp("^lineEdit"));

  QPushButton *button = (QPushButton *)sender();

  QString buttonName = button->objectName();
  int index = buttonName.at(buttonName.count() - 1).digitValue();

  for(int i = 0 ; i<compilerGroupEdits.count() ; i++)
    {
      const QString objectName= compilerGroupEdits[i]->objectName();
      int currentEditIndex = objectName.at(objectName.count() - 1).digitValue();

      if(currentEditIndex == index)
        {
          compilerGroupEdits[i]->setText(fileName);
          break;
        }
    }
}

void CompilerSettingWidget::addCompiler(QAction * action)
{
  QTreeWidgetItem *compilerItem  = new QTreeWidgetItem(QStringList()<<action->text()<<action->text());
  ui->compilers->addTopLevelItem(compilerItem);
}

void CompilerSettingWidget::cloneCompiler()
{

}

void CompilerSettingWidget::removeCompiler()
{

}

void CompilerSettingWidget::updateCurrentCompilerName(const QString &compilerName)
{
  ui->compilers->currentItem()->setText(0,compilerName);
}

void CompilerSettingWidget::activeCompiler(QTreeWidgetItem * compilerItem, int col)
{
  ui->compilerProgramsGroup->setVisible(true);
  ui->compilerName->setText(compilerItem->text(col));
}

void CompilerSettingWidget::on_cloneCompilerButton_clicked()
{

}

void CompilerSettingWidget::on_removeCompilerButton_clicked()
{

}
