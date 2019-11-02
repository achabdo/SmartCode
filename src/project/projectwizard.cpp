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

#include "projectwizard.h"

#include "projectdir.h"
#include "configwizard.h"

#include "classgenerator.h"
#include "newfilewizard.h"

#include "projectsummarywizard.h"

#include "project.h"
#include "projectexplorer.h"
#include "projecttemplate.h"

#include <QApplication>
#include <configmanager.h>
#include "runconfig.h"

#include "core_constants.h"
ProjectWizard::ProjectWizard(ProjectExplorer * projectManager,QWidget *parent) :
  QWizard(parent),projectExplorer(projectManager)
{
  connect(this,SIGNAL(accepted()),SLOT(addProject()));

  setWizardStyle(QWizard::ModernStyle);
  //setPixmap(QWizard::BannerPixmap,QPixmap(":/images/intro.png"));
}

QString ProjectWizard::projectPath()
{
  const QString projectName = field("ProjectName").toString();
  return field("ProjectDir").toString()+"/"+ projectName + "/" + projectName+ ".smc";
}

void ProjectWizard::addProject()
{
  if(projectTemplate->templateType() == "project"){
  QStringList srcFiles = projectTemplate->toSourceFiles();

  const QString projectName = field("ProjectName").toString();

  QString projectDir = field("ProjectDir").toString() + "/" + projectName;

  QDir dir;
  dir.mkdir(projectDir);

  QString proPath = projectPath() ;

  Project * project = new Project(proPath);

  project->addSetting(Core::Project::CURRENT_CONFIG,0);
  project->addSetting(Core::Project::CURRENT_RUNCONFIG,0);
  project->addSetting(Core::Project::SOURCES,srcFiles);

  project->write();
  project->load();

  ConfigWizard * projectConfg = qobject_cast<ConfigWizard*>(page(1));
  project->addConfigs(projectConfg->configs());

  RunConfig *runConfig = new RunConfig(projectName);

  QFileInfo fileInfo(project->path());
  QString exeFile = fileInfo.baseName() + ".exe";
  runConfig->addSetting(Core::Project::RUNEXEC,exeFile);
  runConfig->addSetting(Core::Project::RUNARGS,"");
  runConfig->addSetting(Core::Project::WORKINGDIR,projectDir);
  runConfig->addSetting(Core::Project::RUNINTERMINAL,false);

  project->addRunConfig(runConfig);

  int projectParentIndex = field("projects").toInt();

  QString projectParent;

  if(projectParentIndex > 0)
    projectParent = projects[projectParentIndex - 1];

  if(projectParent.isNull())
    projectExplorer->addProject(proPath);
  else
    {
      projectExplorer->newProject(proPath,projectParent);

      Project * parent = projectExplorer->project(projectParent);
      parent->addSubProject(proPath);
    }

  QDir::setCurrent(QApplication::applicationDirPath());

  QFile f;

  foreach(QString file,srcFiles)
    f.copy(templateDir + file, projectDir + "/" + file);

    }

}

void ProjectWizard::setTemplate(const QString &templat)
{
  templateDir = QFileInfo(templat).path() + "/";

  //const QString banner = templateDir + "/banner.png";

  projectTemplate = new ProjectTemplate;

  projectTemplate->readTemplate(templat);

  QStringList pages = projectTemplate->toWizardPages();

  if(pages.contains("ProjectDir"))
    {
      ProjectDir  * projectDir = new ProjectDir;
      addPage(projectDir);
    }

  if(pages.contains("ProjectConfg"))
    {
      ConfigManager * configManager = parentWidget()->findChild<ConfigManager*>("ConfigManager");
      ConfigWizard * projectConfg  = new ConfigWizard(configManager);
      addPage(projectConfg);
    }

  if(pages.contains("ClassGenerator"))
    {
      ClassGenerator * classG = new ClassGenerator;

      classG->setClassPath(projectExplorer->projectPathFromItem());

      addPage(classG);

      connect(this,SIGNAL(accepted()),classG,SLOT(OnAccept()));
      connect(classG,SIGNAL(newClass(QStringList)),projectExplorer,SLOT(addFiles(QStringList)));
    }

  if(pages.contains("NewFile"))
    {
      const QString option = projectTemplate->pageOption("NewFile");

      NewFileWizard::FileType fileType =  NewFileWizard::TextFile;

      if(option == "SourceFile")
        fileType = NewFileWizard::SourceFile;
      else if(option == "HeaderFile")
        fileType = NewFileWizard::HeaderFile;
      else if(option == "TextFile")
        fileType = NewFileWizard::TextFile;
      else if(option == "XMLFile")
        fileType = NewFileWizard::XMLFile;

      NewFileWizard * newFileWizard = new NewFileWizard(fileType , projectExplorer->projectPathFromItem());

      connect(newFileWizard,SIGNAL(newFileAdded(QStringList)),projectExplorer,SLOT(addFiles(QStringList)));

      addPage(newFileWizard);
    }

  ProjectSummaryWizard * summary = new ProjectSummaryWizard;

  foreach(QString projectName , projectExplorer->Projects())
    {
      if(projectTemplate->templateType() == "project")
        {
          if(projectExplorer->project(projectName)->hasSubProjects())
            projects << projectName;

          summary->setupProjects(projects,true);

        }
      else if(projectTemplate->templateType() == "file")
        {
          if(!projectExplorer->project(projectName)->hasSubProjects())
            projects << projectName;

          summary->setupProjects(projects,false);
        }

    }

  summary->selectProject(projectExplorer->projectNameFromItem());

  addPage(summary);

}
