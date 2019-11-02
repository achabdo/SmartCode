// Copyright (C) 2014 Achrouf corporation <achroufabdenour@gmail.com>
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

#include "projectexplorer.h"
#include "project.h"

#include <tabwidget.h>
#include <textedit.h>
#include <bases.h>
#include <dialog.h>
#include <texteditmanager.h>
#include <texteditarea.h>

#include <QFileDialog>
#include <QTreeWidget>
#include <QFileIconProvider>
#include <QDesktopServices>
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QDebug>

#include "projectwizard.h"
#include "projectdir.h"
#include "projectsetting.h"

#include "core_constants.h"
StandardItem::StandardItem():
  QStandardItem()
{
  setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
}

bool StandardItem::operator<(const QStandardItem &other) const
{
  if(type() >= QStandardItem::UserType && type() != other.type())
    return type() < other.type();

  return QStandardItem::operator <(other);
}

int StandardItem::type() const
{
  const QString userType = text().toUpper();

  if(userType == Core::Project::SOURCES)
    return Sources;
  else if(userType == Core::Project::HEADERS)
    return Headers;
  else if(userType == Core::Project::RESOURCES)
    return Resources;
  else if(userType == Core::Project::OTHERFILES)
    return OtherFiles;
  else if(QFileInfo(userType).isDir())
    return DirType;
  else if(QFileInfo(userType).isFile())
    return FileType;

  return Type;
}

ProjectExplorer::ProjectExplorer(QWidget *parent) :
  QTreeView(parent)
{

  QStandardItemModel * mod = new QStandardItemModel;

  setModel(mod);

  setHeaderHidden(true);
  setContextMenuPolicy(Qt::CustomContextMenu);
  setAcceptDrops(true);

  connect(this, SIGNAL(customContextMenuRequested(QPoint)),
          this, SLOT(showMenu()));
}


void ProjectExplorer::printFiles(const QString &filter,
                                 const QStringList &files )
{
  QString fileName;

  QDir dir(filterPath(filter));

  QStandardItem * itemFilter = itemFromName(filter);

  foreach(QString file,files)
    {
      const QString relative = dir.relativeFilePath(file);

      if(dir.isRelativePath(relative) && !relative.startsWith("../"))
        {
          file = relative;
        }

      QStringList list = file.split("/");

      for(int i = 0 ; i < list.count() ; i++)
        {
          QString sec = list[i];

          const QString fileSection = file.section("/",0,i);

          var = filter + "/" + fileSection;

          fileName = dir.absoluteFilePath(fileSection);

          QString name;

          if(var.contains("/"))
            name = var.left(var.lastIndexOf("/"));

          QStandardItem *parent,*item;

          parent = items.key(name);

          if(!items.values().contains(var))
            {
              if(parent)
                item = createItem(var,parent);
              else
                item = createItem(var,itemFilter);

              fileNames.insert(item,fileName);

              QFileInfo info(sec);

              item->setText(sec);
              item->setToolTip(fileName);


              if(info.suffix()!= NULL && !info.isDir())
                item->setIcon(fileIcon());
              else
                item->setIcon(folderIcon());
            }
        }

      emit fileAdded(fileName);
    }
}

void ProjectExplorer::newProject(const QString &projectName,const QString &parent)
{
  QList<QStandardItem *> parents;

  QStandardItemModel * mod = qobject_cast<QStandardItemModel *>(model());

  if(parent.isNull())
    parents << mod->invisibleRootItem();
  else
    {
      parents << items.key(projectPath(parent));
    }

  QFileInfo f(projectName);

  QStandardItem *project;

  project = new StandardItem;

  project->setText(f.baseName());
  project->setIcon(QIcon(Core::Icon::PROJECT));
  project->setToolTip(projectName);

  parents[0]->appendRow(project);

  items.insert(project,projectPath(projectName));
  fileNames.insert(project,projectName);

  foreach (QString filesSetting, Project::filesSettings())
    addParentItem(projectName,filesSetting);

  model()->sort(0);
}

QRegExp ProjectExplorer::filterFromName(const QString &name)
{
  if(name == Core::Project::SOURCES)
    return Bases::sourceFilesReg();
  else if(name == Core::Project::HEADERS)
    return Bases::headerFilesReg();
  else if(name == Core::Project::RESOURCES)
    return Bases::resourceFilesReg();
  else
    return Bases::otherFilesReg();
}

QString ProjectExplorer::projectPath(const QString &project) const
{
  return Bases::path(project);
}

QStandardItem * ProjectExplorer::addParentItem(const QString &projectName ,const QString &itemName , QStringList parentFiles, bool addEmptyParent)
{
  if(parentFiles.isEmpty())
    parentFiles = project(projectName)->stringList(itemName);

  QStandardItem * item;

  if(!parentFiles.isEmpty() || addEmptyParent)
    {
      item = new StandardItem;

      QString itemText = itemName;
      item->setText(itemName[0] + itemText.remove(0,1).toLower());
      item->setIcon(folderIcon());

      const QString proPath = projectPath(projectName);
      const QString itemPath = proPath + "/" + itemName;

      items.insert(item,itemPath);
      fileNames.insert(item,itemPath);

      printFiles(itemPath,parentFiles);

      itemFromName(proPath)->appendRow(item);

    }

  return item;
}


QStandardItem *ProjectExplorer::createItem(QString data,QStandardItem *parent)
{
  QStandardItemModel * mod = qobject_cast<QStandardItemModel *>(model());

  QStandardItem *item;

  if (parent)
    {
      item = new StandardItem;

      parent->appendRow(item);
    }
  else
    {
      item = new StandardItem;

      mod->appendRow(item);
    }

  items.insert(item,data);

  return item;
}

QString ProjectExplorer::toFileName(const QModelIndex &index) const
{
  return fileNames.value(itemFromIndex(index));
}

QStandardItem *ProjectExplorer::fileNameItem(const QString &fileName) const
{
  return fileNames.key(fileName);
}

QModelIndex ProjectExplorer::indexFromFileName(const QString &file) const
{
  return fileNameItem(file)->index();
}

bool ProjectExplorer::openProject(const QString &projectName)
{
  if(!projects.contains(projectName))
    {
      Project * p  = new Project(projectName);

      if(p->load())
        {
          projects.insert(projectName , p);

          QDir::setCurrent(p->path());

          if(!p->hasSubProjects())
            newProject(projectName);
          else
            {
              newProject(projectName);

              foreach(QString subProjectName,p->toSubProjects().keys())
                {
                  Project * subProject = p->subProject(subProjectName);

                  if(subProject->load())
                    newProject(subProjectName,projectName);

                }
            }

          //setCurrentProject(projectName);

        }
      else
        {
          showMessage(tr("Failed to open project"),tr("The File doesn't exists"));
        }
    }
  else
    showMessage(tr("Failed to open project"),tr("The Project is already open"));

  return true;
}

QStandardItem *ProjectExplorer::itemFromView()
{
  return items.key(projectPath(projectNameFromItem()));
}

QStandardItem *ProjectExplorer::itemFromName(const QString &itemName) const
{
  return items.key(itemName);
}

QStandardItem * ProjectExplorer::itemFromIndex(const QModelIndex &index) const
{
  QStandardItemModel * mod = qobject_cast<QStandardItemModel *>(model());

  return mod->itemFromIndex(index);
}

void ProjectExplorer::showMessage(const QString &title ,const QString &msg)
{
  QMessageBox box(this);

  box.setWindowFlags(Qt::Sheet);
  box.setWindowTitle(title);
  box.setInformativeText(msg);
  box.setIcon(QMessageBox::Critical);
  box.addButton(QMessageBox::Ok);

  if(box.exec()==QMessageBox::Ok)
    return ;
}


void ProjectExplorer::showMenu()
{
  QMenu menu;

  QAction *addFilesAction = new QAction(tr("Add Exsisting Filenames"),this);
  connect(addFilesAction,SIGNAL(triggered()),this,SLOT(addExstingFiles()));

  QAction *addNewFileAction = new QAction(tr("Add New..."),this);
  connect(addNewFileAction,SIGNAL(triggered()),this,SLOT(addNewFile()));

  QString path = currentFileName();

  if(path.endsWith(".smc"))
    {
      menu.addAction(tr("Active Project"),this,SLOT(activeProject()));

      menu.addAction(tr("Run"),this,SLOT(run()));
      menu.addAction(tr("build"),this,SLOT(build()));
      menu.addAction(tr("Rebuild"),this,SLOT(rebuild()));
      menu.addAction(tr("clean"),this,SLOT(clean()));

      menu.addSeparator();

      menu.addAction(addFilesAction);
      menu.addAction(addNewFileAction);
      menu.addAction(tr("Add a directory"),this,SLOT(addDirectory()));
      menu.addAction(tr("Remove Files"),this,SLOT(removeFiles()));

      menu.addSeparator();

      if(projectHasParent())
        menu.addAction(tr("Remove Project"),this,SLOT(removeSubProject()));
      else
        menu.addAction(tr("Close"),this,SLOT(closeProject()));

      menu.addAction(tr("Add Subproject"),this,SLOT(addSubProject()));

    }

  else if(QFileInfo(path).suffix().isNull())
    {
      menu.addAction(addFilesAction);
      menu.addAction("Open in Explorer",this,SLOT(openExplorer()));
      //menu.addAction("reduire",this,SLOT(deleteFile()));
      menu.addAction(addNewFileAction);
    }
  else
    {
      menu.addAction(tr("open"),this,SLOT(close()));
      menu.addAction(tr("delete"),this,SLOT(removeCurrentFile()));
      menu.addAction(tr("rename"),this,SLOT(renameFile()));

      QMenu * git = menu.addMenu(tr("git"));

      git->addAction(tr("blame"),this,SLOT(blame()));
      git->addAction(tr("diff"),this,SLOT(diff()));
      git->addAction(tr("log"),this,SLOT(log()));

    }

  menu.exec(QCursor::pos());
}


void ProjectExplorer::removeCurrentFile()
{
  QCheckBox * check = new QCheckBox;

  check->setText(tr("Remove the file in system files"));

  if (Dialog::exec(this,tr("Delete File"),QString(tr("delete") + " %1").arg(currentFileName()),check) == QDialog::Accepted )
    {
      removeFile(currentIndex(),check->isChecked());
    }

  delete check;
}

void ProjectExplorer::removeFile(const QModelIndex &index , bool removeFromFileSystem)
{
  QString path = projectPath(projectNameFromItem());

  QDir dir(path);

  QString name = toFileName(index);

  if(removeFromFileSystem)
    {
      if( !dir.remove(name))
        showMessage(tr("Error"),tr("Cannot remove the file from the FileSystem"));
    }

  QString file = dir.relativeFilePath(name);

  if(projectHasParent())
    project(projectNameFromItem(),projectParentFromItem())->deleteFile(file,fileType(file));
  else
    project(projectNameFromItem())->deleteFile(file,fileType(file));

  for (QModelIndex i = index; i.isValid(); i = i.parent())
    {
      if(i.parent().isValid() && !toFileName(i).endsWith(".smc"))
        {
          QStandardItem * item = itemFromIndex(i.parent());

          if(item->rowCount() > 1)
            {
              removeItem(i);
              break;
            }
          else
            removeItem(i);

        }
    }
}

void ProjectExplorer::removeItem(const QModelIndex &i)
{
  QStandardItem * itemToRemove = itemFromIndex(i);

  items.remove(itemToRemove);
  fileNames.remove(itemToRemove);

  model()->removeRow(i.row(),i.parent());

}

void ProjectExplorer::closeProject()
{
  removeProject(currentIndex());
  emit projectClosed();
}

void ProjectExplorer::closeCurrentProject()
{
  removeProject(indexFromFileName(curProject));
}

void ProjectExplorer::closeAllProject()
{
  for(int i = 0; i < model()->rowCount();i++)
    {
      removeProject(model()->index(i,0));
    }
}


void ProjectExplorer::removeProject(const QModelIndex &index)
{
  projects.remove(toFileName(index));

  QString itemName = items.value(itemFromIndex(index));

  foreach (QStandardItem * i , items.keys())
    {
      if(items.value(i).startsWith(itemName))
        {
          items.remove(i);
          fileNames.remove(i);
        }
    }

  model()->removeRow(index.row(),index.parent());

  if(currentIndex().isValid())
    setCurrentProject(toFileName(currentIndex()));
  else
    curProject = QString();

  emit projectCountChanged(projectsCount());
}

void ProjectExplorer::removeSubProject()
{
  removeProject(currentIndex());

  project(projectParentFromItem())->removeSubProject(projectNameFromItem());
}

void ProjectExplorer::addSubProject()
{
  addNewItem(ProjectDialog::NewProject,true);
}

void ProjectExplorer::showProjectWizard(const QString &templat)
{
  ProjectWizard * projectWizard = new ProjectWizard(this,parentWidget()->parentWidget());

  projectWizard->setTemplate(templat);

  projectWizard->exec();

  delete projectWizard;
}

void ProjectExplorer::showSubProjectWizard(const QString &templat)
{
  ProjectWizard * projectWizard = new ProjectWizard(this,parentWidget()->parentWidget());

  projectWizard->setTemplate(templat);

  ProjectDir * projectDir = qobject_cast<ProjectDir*>(projectWizard->page(0));

  if(projectDir)
    projectDir->setProjectDir(projectPathFromItem());

  projectWizard->exec();

  delete projectWizard;
}

void ProjectExplorer::setCurrentProject(const QString &project)
{
  curProject = project;

  QFont font;
  font.setBold(true);

  QFont f;
  f.setBold(false);

  QStandardItemModel * mod = qobject_cast<QStandardItemModel *>(model());

  for(int row = 0 ; row < mod->rowCount(); row++)
    {
      QStandardItem * item = mod->item(row);

      if(fileNames.value(item) == curProject)
        item->setFont(font);
      else
        item->setFont(f);
    }

  emit currentProjectChanged(project);
}

void ProjectExplorer::activeProject()
{
  setCurrentProject(toFileName(currentIndex()));
}

Project *ProjectExplorer::project(const QString &projectName ,const QString &projectParent) const
{
  if(projectParent.isNull())
    return projects.value(projectName);
  else
    return project(projectParent)->subProject(projectName);
}

Project *ProjectExplorer::currentProject() const
{
  return projects.value(curProject);
}

QString ProjectExplorer::currentProjectName() const
{
  return curProject;
}

QString ProjectExplorer::currentProjectPath() const
{
  return projectPath(curProject);
}

QString ProjectExplorer::currentProjectFilter(const QString &filterName) const
{
  return filter(curProject,filterName);
}


void ProjectExplorer::renameFile()
{
  const QString oldName = currentFileName();
  const QString oldNameBase = Bases::fileName(currentFileName());

  const QString newNameBase = Dialog::stringFromMessageBox(this,tr("RenameFile"),
                                                           tr("Enter the name of the new file"),oldNameBase);

  if(!newNameBase.isNull())
    {
      const QString newName = Bases::path(oldName) + "/" + newNameBase;

      QDir dir(projectPathFromItem());

      if(dir.rename(oldName,newName))
        {
          QStandardItem * renamedItem = itemFromIndex(currentIndex());

          projectFromItem()->renameFile(fileType(oldNameBase),dir.relativeFilePath(oldName),dir.relativeFilePath(newName));
          renamedItem->setText(newNameBase);
          fileNames.insert(renamedItem,newName);
        }
      else
        showMessage(tr("Error"),tr("Cannot rename the file"));

    }
}


void ProjectExplorer::addExstingFiles()
{
  QStringList names = QFileDialog::getOpenFileNames(this,
                                                    tr("Add Exsiting files"), QDir::currentPath(), tr("all Files (*.*)"));
  if(names.isEmpty())
    return;

  addFiles(names);

  model()->sort(0);
}

void ProjectExplorer::addNewFile()
{
  addNewItem(ProjectDialog::NewFile);
}

void ProjectExplorer::addNewItem(ProjectDialog::NewType newType,bool isSubProject)
{
  ProjectDialog * proDialog = new ProjectDialog(this);

  proDialog->setItems(newType);

  if(isSubProject)
    connect(proDialog,SIGNAL(templateSelected(QString)),this,SLOT(showSubProjectWizard(QString)));
  else
    connect(proDialog,SIGNAL(templateSelected(QString)),this,SLOT(showProjectWizard(QString)));

  proDialog->exec();

  delete proDialog;
}

void ProjectExplorer::addFiles(const QStringList &fileNames)
{
  const QString proName = projectNameFromItem();

  const QString path = projectPath(proName);

  foreach(QString fileName,fileNames)
    {
      fileName.replace("\\","/");

      QDir dir(path);

      QString file = dir.relativeFilePath(fileName);

      const QString myFilter = fileType(file);

      project(proName)->addPath(file,myFilter);

      QStandardItem * parentItem = checkParentItemExsits(myFilter);

      if(parentItem)
        printFiles(filter(path,myFilter) ,QStringList()<<fileName);

    }
}

//check if parent item exists "ex: Sources" and add it if he not exists
QStandardItem * ProjectExplorer::checkParentItemExsits(const QString &parentName)
{
  const QString proName = projectNameFromItem();

  QStandardItem *item;

  item = items.key(projectPath(proName) + "/" + parentName);

  if(!items.contains(item))
    {
      item = addParentItem(proName,parentName);
    }

  return item;
}

QString ProjectExplorer::projectNameFromItem() const
{
  for (QModelIndex i = currentIndex(); i.isValid(); i = i.parent())
    {
      if(toFileName(i).endsWith(".smc"))
        return toFileName(i);
    }

  return curProject;
}

QString ProjectExplorer::projectPathFromItem() const
{
  return Bases::path(projectNameFromItem());
}

QString ProjectExplorer::projectParentFromItem() const
{
  for (QModelIndex i = currentIndex(); i.isValid(); i = i.parent())
    {
      if(toFileName(i).endsWith(".smc") && !i.parent().isValid())
        return toFileName(i);
    }

  return QString() ;
}

bool ProjectExplorer::projectHasParent()
{
  return (projectNameFromItem() != projectParentFromItem());
}

Project * ProjectExplorer::projectFromItem()
{
  return project(projectNameFromItem());
}


bool ProjectExplorer::addProject(const QString &name)
{
  if(openProject(name))
    {
      setCurrentProject(name);

      emit projectAdded();

      emit projectCountChanged(projectsCount());

      return true;
    }

  return false;
}

int ProjectExplorer::projectsCount() const
{
  return projects.count();
}

//for find a text in editor(tabWidget) or open file in it
void ProjectExplorer::getFile(const QModelIndex &index)
{
  QString fileName = toFileName(index);

  if(QFileInfo(fileName).isDir())
    return ;

  if(fileName.contains("/"))
    {
      if(Project::isSmcProject(fileName))
        {
          ProjectSetting * dialog = new ProjectSetting(project(fileName));
          dialog->exec();
        }
      else
        {
          if(editor->openFile(fileName))
            {
              editor->currentTextEditArea()->setFileItem(fileNameItem(fileName));
            }
          // emit fileOpened(fileName);

          //                                if(editor->openFile(fileName))
          //                                    connect(editor->currentTextEdit(),SIGNAL(variableAdded(QString)),this,SLOT(updateClassModel(QString)));
        }
    }
  else
    {
      findFunction(index);
    }

}

void ProjectExplorer::setEditor(TabWidget *Editor)
{
  editor = Editor;

  connect(this,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(getFile(QModelIndex)));
}


QString ProjectExplorer::fileType(const QString &file)
{
  if(file.contains(Bases::sourceFilesReg()))
    return Core::Project::SOURCES;
  else if(file.contains(Bases::headerFilesReg()))
    return Core::Project::HEADERS;
  else if(file.contains(Bases::resourceFilesReg()))
    return Core::Project::RESOURCES;
  else
    return Core::Project::OTHERFILES;
}


QStringList ProjectExplorer::Projects() const
{
  return projects.keys();
}


TabWidget *ProjectExplorer::Editor() const
{
  return editor;
}

QString ProjectExplorer::modelString(const QModelIndex &index)
{
  return model()->data(index).toString();
}

bool ProjectExplorer::itemIsFile(const QModelIndex &index)
{
  return !this->toFileName(index).isNull();
}

QString ProjectExplorer::attrFuncFileName(const QModelIndex &index)
{
  for (QModelIndex i = index; i.isValid(); i = i.parent())
    {
      if(itemIsFile(i))
        return toFileName(i);
    }

  return QString();
}

bool ProjectExplorer::isClass(const QString &data)
{
  return !QFileInfo(data).isFile();
}

void ProjectExplorer::findFunction(const QModelIndex &index)
{
  QString fileName;

  QString function = modelString(index);

  QRegExp rxFunc("(\\S+)(\\(([^\\t]*)\\))*\\s:\\s(\\w+)");

  rxFunc.indexIn(function);

  QString textToFind,type,funcName,arg;

  funcName = rxFunc.cap(1);
  arg = rxFunc.cap(2);
  type = rxFunc.cap(4);

  fileName = attrFuncFileName(index);

  editor->openFile(fileName);

  textToFind = type + "\\s*" + funcName;

  editor->currentTextEdit()->find(textToFind,true);

  editor->currentTextEdit()->setFocus();
}

QStringList ProjectExplorer::projectFiles(const QString &projectName,const QString &filter)
{
  QRegExp rx(filter);
  rx.setPatternSyntax(QRegExp::Wildcard);

  Project * pro = project(projectName);

  return pro->toFiles().filter(rx);
}

QStringList ProjectExplorer::allProjectsFiles(const QString &filter)
{
  QStringList files;

  foreach(QString projectName,toProjects())
    {
      files <<projectFiles(projectName,filter);
    }

  return files;
}


QStringList ProjectExplorer::currentProjectFiles(const QString &filter)
{
  return projectFiles(curProject,filter);
}

QStringList ProjectExplorer::toProjects() const
{
  return  projects.keys();
}

QString ProjectExplorer::currentFileName()
{
  return toFileName(currentIndex());

}

void ProjectExplorer::openExplorer()
{
  QString path = currentFileName();

  if(!QFileInfo(path).exists())
    path = Bases::path(toFileName(currentIndex().parent()));

  QDesktopServices::openUrl(QUrl("file:///" + path));

}

void ProjectExplorer::rebuild()
{
  emit rebuild(currentFileName());
}

void ProjectExplorer::clean()
{
  emit clean(currentFileName());
}

void ProjectExplorer::build()
{
  emit build(currentFileName());
}

void ProjectExplorer::run()
{
  emit run(currentFileName());
}

QIcon ProjectExplorer::folderIcon() const
{
  return QIcon(Core::Icon::FOLDER);
}

QIcon ProjectExplorer::fileIcon() const
{
  return QFileIconProvider().icon(QFileIconProvider::File);
}

void ProjectExplorer::addDirectory()
{
  const QString dirName = Dialog::stringFromMessageBox(this,tr("Add Directory"),tr("Enter the name of the directory"));

  if(!dirName.isNull())
    {
      QDir dir;
      QDir::setCurrent(projectPathFromItem());
      dir.mkdir(dirName);
    }

}

void ProjectExplorer::removeFiles()
{
  QDialog dialog;

  QTreeWidget * treeWidget = new QTreeWidget;

  QCheckBox  * checkBox = new QCheckBox(tr("Remove files from the File System"));

  QVBoxLayout * layout = new QVBoxLayout;

  QDialogButtonBox buttonBox;
  buttonBox.setStandardButtons(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);

  connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
  connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

  dialog.setLayout(layout);

  layout->addWidget(treeWidget);
  layout->addWidget(checkBox);
  layout->addWidget(&buttonBox);

  const QString projectName = projectNameFromItem();

  addFilesToRemove(treeWidget,projectName);

  treeWidget->expandAll();

  if(dialog.exec())
    {
      for(int i = 0 ;i < treeWidget->topLevelItemCount();i++)
        {
          QTreeWidgetItem * topLevelItem = treeWidget->topLevelItem(i);

          for(int j = 0 ;j < topLevelItem->childCount() ;j++)
            {
              QTreeWidgetItem * item = topLevelItem->child(j);

              if(item->checkState(0) == Qt::Checked)
                removeFile(indexFromFileName(QDir(projectPathFromItem()).
                                             absoluteFilePath(item->text(0)))
                           ,checkBox->isChecked());

            }
        }

    }
}

void ProjectExplorer::addFilesToRemove(QTreeWidget * treeWidget ,const QString &projectName)
{
  QTreeWidgetItem * projectItem =  treeWidget->invisibleRootItem();

  foreach(const QString parent,projectParents())
    {
      Project * project = this->project(projectName);

      if(!project->stringList(parent).isEmpty())
        {
          QTreeWidgetItem* item = new QTreeWidgetItem(projectItem);

          item->setText(0,parent);

          foreach(QString file ,project->stringList(parent))
            {
              QTreeWidgetItem * fileItem = new QTreeWidgetItem(item);

              fileItem->setFlags(Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
              fileItem->setCheckState(0,Qt::Unchecked);

              fileItem->setText(0,file);
            }
        }
    }
}

QStringList ProjectExplorer::projectParents()
{
  return QStringList() <<Core::Project::SOURCES
                      <<Core::Project::HEADERS
                     <<Core::Project::RESOURCES
                    <<Core::Project::OTHERFILES;
}

void ProjectExplorer::blame()
{
  QDir::setCurrent(projectPathFromItem());
  editor->blame(QFileInfo(currentFileName()).fileName());
}

void ProjectExplorer::diff()
{
  QDir::setCurrent(projectPathFromItem());
  editor->diff(QFileInfo(currentFileName()).fileName());
}

void ProjectExplorer::log()
{
  QDir::setCurrent(projectPathFromItem());
  editor->log(QFileInfo(currentFileName()).fileName());
}

bool ProjectExplorer::projectIsOpen(const QString &projectName)
{
  return Projects().contains(projectName);
}












