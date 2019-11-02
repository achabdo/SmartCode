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

#include "projectsetting.h"
#include "ui_projectsetting.h"
#include <QLineEdit>
#include <QTreeWidget>
#include <tabsettingmanager.h>
#include <bases.h>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenu>
#include <dialog.h>

#include "project.h"
#include "runconfig.h"
#include "configmanager.h"
#include <compiler/compileroptionswidget.h>

#include "core_constants.h"

using namespace Core::Project;
using namespace Core::Compiler;

ProjectSetting::ProjectSetting(Project * project,QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ProjectSetting),
  pro(project)
{
  ui->setupUi(this);

  connect(ui->settingsList,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(setCurrentPageTitle(QTreeWidgetItem*,int)));
  connect(ui->settingsList,SIGNAL(clicked(QModelIndex)),this,SLOT(setCurrentPage(QModelIndex)));

  connect(ui->removeConfigButton,SIGNAL(clicked()),this,SLOT(removeConfiguration()));
  connect(ui->renameConfigButton,SIGNAL(clicked()),this,SLOT(renameConfiguration()));

  connect(ui->removeRunConfigButton,SIGNAL(clicked()),this,SLOT(removeRunConfiguration()));
  connect(ui->renameRunConfigButton,SIGNAL(clicked()),this,SLOT(renameRunConfiguration()));

  setup();
}

void ProjectSetting::setupCustomVariables()
{
//  SettingsManager * buildVariables = pro->buildVariables();

//  foreach (QString var, buildVariables->allSettingsNames()) {
//      customVars->addItem(QStringList()<<var<<buildVariables->string(var),0);
//    }
}

void ProjectSetting::accept()
{
  //  pro->saveFromWidget(this);
  QDialog::accept();
}

void ProjectSetting::addRunConfiguration()
{
  const QString configName = Dialog::stringFromMessageBox(
        this,tr("Create Run configuration"),tr("Configutation name"));

  if(!configName.isNull())
    {
      RunConfig * rConfig = new RunConfig(configName);
      pro->addRunConfig(rConfig);

      ui->runConfigsBox->addItem(configName);
      ui->runConfigsBox->setCurrentIndex(ui->runConfigsBox->count() - 1);
    }
}

void ProjectSetting::cloneRunConfiguration()
{
  const QString configName = Dialog::stringFromMessageBox(
        this,tr("Create Run Configuration"),tr("Configutation name"));

  if(!configName.isNull())
    {
      pro->cloneRunConfig(ui->runConfigsBox->currentIndex(),configName);
      ui->runConfigsBox->addItem(configName);
    }
}

void ProjectSetting::renameRunConfiguration()
{
  const QString configName = Dialog::stringFromMessageBox(
        this,tr("Create configuration"),tr("Configutation name"));

  if(!configName.isNull())
    {
      int index = ui->runConfigsBox->currentIndex();

      ui->runConfigsBox->setItemText(index,configName);
      pro->renameRunConfig(index,configName);
    }
}

void ProjectSetting::removeRunConfiguration()
{
  int index = ui->runConfigsBox->currentIndex();

  ui->runConfigsBox->removeItem(index);
  pro->removeRunConfig(index);

}

void ProjectSetting::addConfiguration()
{
  const QString configName = Dialog::stringFromMessageBox(
        this,tr("Create configuration"),tr("Configutation name"));

  if(!configName.isNull())
    {
      ConfigManager *configManager = parentWidget()->findChild<ConfigManager*>("ConfigManager");

      pro->addConfig(configManager->addDebugConfig(configName));

      ui->editConfigsBox->addItem(configName);
      ui->configsBox->insertItem(ui->configsBox->count() -1,configName);

      ui->editConfigsBox->setCurrentIndex(ui->editConfigsBox->count() - 1);

    }
}

void ProjectSetting::cloneConfiguration()
{
  const QString configName = Dialog::stringFromMessageBox(
        this,tr("Create configuration"),tr("Configutation name"));

  if(!configName.isNull())
    {
      pro->cloneConfig(ui->editConfigsBox->currentIndex(),configName);
      ui->editConfigsBox->addItem(configName);
    }
}

void ProjectSetting::renameConfiguration()
{
  const QString configName = Dialog::stringFromMessageBox(
        this,tr("Create configuration"),tr("Configutation name"));

  if(!configName.isNull())
    {
      int index = ui->editConfigsBox->currentIndex();

      ui->editConfigsBox->setItemText(index,configName);
      pro->renameConfig(index,configName);
    }
}

void ProjectSetting::removeConfiguration()
{
  int index = ui->editConfigsBox->currentIndex();

  ui->editConfigsBox->removeItem(index);
  pro->removeConfig(index);

}

void ProjectSetting::setCurrentPageTitle(QTreeWidgetItem * item,int)
{
  ui->titleLabel->setText(item->text(0));
}

void ProjectSetting::setCurrentPage(const QModelIndex &index)
{
  if(index.parent().isValid())
    {
      ui->settingsPages->setCurrentIndex(index.parent().row());
      ui->buildPages->setCurrentIndex(index.row());
    }
  else
    ui->settingsPages->setCurrentIndex(index.row());

}

ProjectSetting::~ProjectSetting()
{
  delete ui;
  //delete SearchPaths;
}

void ProjectSetting::setup()
{
  ui->configsBox->addItems(pro->configsNames());
  ui->configsBox->setCurrentIndex(pro->toInt(CURRENT_CONFIG));
  ui->configsBox->addItem("All Configurations");

  connect(ui->configsBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setCurrentConfiguration(int)));

  tabSettingManager = new TabSettingManager;

  ui->linkerLayout->addWidget(tabSettingManager->tabSetting(0));
  ui->searchPathsLayout->addWidget(tabSettingManager->tabSetting(1));
  ui->customVarsLayout->addWidget(tabSettingManager->tabSetting(2));

  compilerOptionsWidget = new CompilerOptionsWidget();
  ui->compilerOptionsLayout->addWidget(compilerOptionsWidget);

  setupConfiguration();
  setupRunConfiguration();

  loadConfiguration(pro->toInt(CURRENT_CONFIG));

  //setupCustomVariables();
}

void ProjectSetting::updateCompilerOptions(const QStringList &flags)
{

  //compilerOptionsWidget->setCompilerOptionsCategories();
 // compilerOptionsWidget->setActivatedFlags(config->stringList(CXXFLAGS));
}

void ProjectSetting::setupRunConfiguration()
{
  QMenu * menu = new QMenu;

  menu->addAction("Add",this,SLOT(addRunConfiguration()));
  menu->addAction("Duplicate",this,SLOT(cloneRunConfiguration()));

  ui->addRunConfigButton->setMenu(menu);

  foreach (RunConfig *rConfig,pro->runConfigurations())
    {
      ui->runConfigsBox->addItem(rConfig->name());
    }

  connect(ui->runInTerminalBox,SIGNAL(stateChanged(int)),this,SLOT(setRunInTerminal(int)));
  connect(ui->runConfigsBox,SIGNAL(currentIndexChanged(int)),this,SLOT(updateRunConfiguration(int)));
}

void ProjectSetting::setRunInTerminal(int state)
{
  pro->currentRunConfig()->addSetting(Core::Project::RUNINTERMINAL,state);
}

void ProjectSetting::updateRunConfiguration(int index)
{
  //  pro->setCurrentRunConfig(index);
  RunConfig *rConfig = pro->currentRunConfig();

  if(pro->currentConfiguration()->toInt(Core::Project::TEMPLATE) == Config::App && index == 0)
    {
      ui->runExecutable->setEnabled(false);
    }
  else
    ui->runExecutable->setText(rConfig->string(Core::Project::RUNEXEC));

  ui->runArgs->setText(rConfig->string(Core::Project::RUNARGS));
  ui->workingDirectory->setText(rConfig->string(Core::Project::WORKINGDIR));
  ui->runInTerminalBox->setChecked(rConfig->toBool(Core::Project::RUNINTERMINAL));
}

void ProjectSetting::setupConfiguration()
{
  QMenu * menu = new QMenu;

  menu->addAction("Add",this,SLOT(addConfiguration()));
  menu->addAction("Duplicate",this,SLOT(cloneConfiguration()));

  ui->editConfigsBox->addItems(pro->configsNames());
  ui->editConfigsBox->setCurrentIndex(pro->toInt(Core::Project::CURRENT_CONFIG));

  connect(ui->editConfigsBox,SIGNAL(currentIndexChanged(int)),this,SLOT(enableRemoveConfigButton(int)));
  connect(ui->editConfigsBox,SIGNAL(currentIndexChanged(int)),ui->configsBox,SLOT(setCurrentIndex(int)));

  ui->addConfigButton->setMenu(menu);
}

void ProjectSetting::enableRemoveConfigButton(int)
{
  ui->removeConfigButton->setEnabled(ui->editConfigsBox->count() > 1);
}

Config *ProjectSetting::configurationChanged()
{
  Config * oldConfig = pro->currentConfiguration();
  Config * newConfig = (oldConfig);

  newConfig->addSetting(TARGET,ui->targetEdit->text());
  newConfig->addSetting(DESTDIR,ui->destDirEdit->text());
  newConfig->addSetting(OBJECTSDIR,ui->objectsDirEdit->text());
  newConfig->addSetting(TEMPLATE,ui->templateBox->currentIndex());

  tabSettingManager->save(newConfig);

  foreach(QString settingName ,oldConfig->allSettingsNames())
    {
      if(newConfig->setting(settingName) != oldConfig->setting(settingName))
        return 0;
    }

  return newConfig;
}

void ProjectSetting::applyConfiguration(Config *config)
{
  ui->targetEdit->setText(config->string(TARGET));
  ui->destDirEdit->setText(config->string(DESTDIR));
  ui->objectsDirEdit->setText(config->string(OBJECTSDIR));
  ui->templateBox->setCurrentIndex(config->toInt(TEMPLATE));

  tabSettingManager->load(config);
  updateCompilerOptions(config->stringList(CXXFLAGS));
}

void ProjectSetting::loadConfiguration(int index)
{
 applyConfiguration(pro->config(index));
}

void ProjectSetting::setCurrentConfiguration(int index)
{
  if(Config * newConfig = configurationChanged())
    {
      if(QMessageBox::information(this,"SmartCode",
                                  tr("Configuration changed , do you want to save")
                                  ,QMessageBox::Ok|QMessageBox::No) == QMessageBox::Ok)
        pro->updateSettings(pro->currentConfiguration(),newConfig);

    }

  int lastItemIndex =  ui->configsBox->count() -1 ;


  if(index == lastItemIndex)
    {
      Config * allConfigs = new Config("All");

      foreach(QString settingName,pro->config(0)->allSettingsNames())
        {
          bool sameSetting;

          for(int i = 0; i< pro->configs().count() - 1;i++)
            {
              if(pro->config(i)->setting(settingName) ==
                 pro->config(i+1)->setting(settingName))
                sameSetting = true;
              else
                sameSetting = false;

            }

          if(sameSetting)
            allConfigs->addSetting(settingName,pro->config(0)->setting(settingName));
          else
            allConfigs->addSetting(settingName,QVariant());

        }

      applyConfiguration(allConfigs);
    }
  else
    {
     // must handle that abdo : how to save this pro->addSetting(CURRENT_CONFIG,index);
      loadConfiguration(index);
    }
}

void ProjectSetting::on_toolButton_clicked()
{
  const QString MakeFileName = QFileDialog::getOpenFileName(this,tr("choose icon"),QDir::currentPath(),"Icons (*.ico);;All Files (*.*)");
  //pro->renameFile(Core::Project,MakeFileName);
}

void ProjectSetting::on_getIconButton_clicked()
{
  const QString iconFileName = QFileDialog::getOpenFileName(
        this,tr("choose icon"),QDir::currentPath(),"Icons (*.ico);;All Files (*.*)");

  ui->iconButton->setIcon(QIcon(iconFileName));
}

void ProjectSetting::getProjectsList(QStringList projects)
{
  projects.removeOne(pro->name());

  foreach(QString project,projects)
    {
      QListWidgetItem *item = new QListWidgetItem;

      item->setText(Bases::baseName(project));
      item->setFlags(Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
      item->setCheckState(pro->stringList(Core::Project::DEPENDENCIES).contains(project) ? Qt::Checked : Qt::Unchecked);

      ui->dependenciesList->addItem(item);
    }

  //  if(dialog->exec())
  //    {
  //      for(int i = 0; i <depends->DependenciesList->count() ; i++)
  //        {
  //          QString dependency = depends->DependenciesList->item(i)->text();

  //          if(!pro->dependencies().contains(dependency))
  //            pro->addPath(dependency,Core::Project::DEPENDENCIES);
  //        }
  //    }
}
