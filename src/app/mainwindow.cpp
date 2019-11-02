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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_About.h"

#include <QtWidgets/QComboBox>
#include <QFileDialog>
#include <QPrintDialog>

#include <projectexplorer.h>
#include <classparsermanager.h>
#include <tabwidget.h>
#include <classgenerator.h>

#include <compiler/buildmanager.h>
#include <compiler/compilersetting.h>

#include <logs/problems.h>
#include <logs/log.h>

#include <debugger/debugger.h>
#include <debugger/gdb.h>
#include <debugger/debuggerclientwidget.h>
#include <debugger/breakpointsmanager.h>
#include <debugger/breakpoint.h>

#include <recents.h>
#include <project.h>
#include <startpage.h>
#include <options.h>
#include <projectdialog.h>
#include <projectwizard.h>
#include <textfinder.h>
#include <advancedsearch.h>
#include <projectsetting.h>

#include <project/devcpp.h>
#include <qtapp.h>
#include <bases.h>
#include <textedit.h>

#include <Qsci/qsciprinter.h>

#include <makefilegenerator.h>
#include <buildvariables.h>

#include <texteditmanager.h>
#include <setting.h>
#include <logs/logs.h>

#include <dialog.h>

#include <QVBoxLayout>
#include <QCheckBox>

#include <bookmarks.h>
#include <configmanager.h>

#include <compiler/compileroptionswidget.h>
#include <runconfig.h>

#include "core_constants.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),newCount(0)

{
  ui->setupUi(this);

  setupBuild();
  setupCore();

  setupProject();
  setupMake();

  addConfigBox();
  setupRegistry();

  connects();
  menuConnects();

  addStartPage();
}

void MainWindow::connects()
{
  connect(ui->actionStart_Page,SIGNAL(triggered()),this,SLOT(addStartPage()));
  connect(logs->problems(),SIGNAL(openFile(QString,int,int)),editor,SLOT(openFileAt(QString,int,int)));

  //Compiler and Run signals
  connect(buildManager,SIGNAL(newStandardError(QString)),logs->compileOutput(),SLOT(showError(QString)));
  connect(buildManager,SIGNAL(newStandardOutput(QString)),logs->compileOutput(),SLOT(showMessage(QString)));
  connect(buildManager,SIGNAL(newRunStandardError(QString)),logs->appOutput(),SLOT(showError(QString)));
  connect(buildManager,SIGNAL(newRunStandardOutput(QString)),logs->appOutput(),SLOT(showMessage(QString)));
  //Compiler and Run signals
  connect(editor,SIGNAL(currentChanged(int)),this,SLOT(enableEdit(int)));
  connect(editor,SIGNAL(currentChanged(int)),this,SLOT(updateFunctionsBox(int)));

  connect(projectExplorer,SIGNAL(projectCountChanged(int)),this,SLOT(enableProject(int)));
  connect(editor,SIGNAL(currentChanged(int)),this,SLOT(enableBuildToolBar(int)));

  connect(projectExplorer,SIGNAL(build(QString)),this,SLOT(build(QString)));
  connect(projectExplorer,SIGNAL(rebuild(QString)),this,SLOT(rebuild(QString)));
  connect(projectExplorer,SIGNAL(run(QString)),this,SLOT(run(QString)));
  connect(projectExplorer,SIGNAL(clean(QString)),this,SLOT(clean(QString)));

  connect(projectDock,SIGNAL(visibilityChanged(bool)),ui->actionProject_manager,SLOT(setChecked(bool)));
  connect(ui->actionProject_manager,SIGNAL(toggled(bool)),projectDock,SLOT(setVisible(bool)));

  connect(logsDock,SIGNAL(visibilityChanged(bool)),ui->actionLogs,SLOT(setChecked(bool)));
  connect(ui->actionLogs,SIGNAL(toggled(bool)),logsDock,SLOT(setVisible(bool)));

  connect(ui->actionMainToolBar,SIGNAL(toggled(bool)),ui->mainToolBar,SLOT(setVisible(bool)));
  connect(ui->actionCompilerToolBar,SIGNAL(toggled(bool)),ui->compileToolBar,SLOT(setVisible(bool)));
  connect(ui->actionDebuggerToolBar,SIGNAL(toggled(bool)),ui->debugToolBar,SLOT(setVisible(bool)));
  connect(buildManager,SIGNAL(programFinished(QString)),logs->appOutput(),SLOT(showMessage(QString)));


  connect(projectExplorer,SIGNAL(projectCountChanged(int)),this,SLOT(updateProjectConfigurations(int)));
  connect(this,SIGNAL(destroyed()),this,SLOT(saveSettings()));

  QSettings settings;

  const QStringList startupProjects = settings.value("StartupProjects").toStringList();

  foreach(QString project,startupProjects )
    projectExplorer->addProject(project);

  updateActionStartupProjectText(projectExplorer->currentProjectName());

  connect(projectExplorer,SIGNAL(currentProjectChanged(QString)),this,SLOT(updateActionStartupProjectText(QString)));
}

void MainWindow::saveSettings()
{

}

void MainWindow::menuConnects()
{
  connect(ui->actionClose_Project,SIGNAL(triggered()),projectExplorer,SLOT(closeCurrentProject()));
  connect(ui->actionClose_All_Projects,SIGNAL(triggered()),projectExplorer,SLOT(closeAllProject()));
  connect(ui->menuAdvanced_Find,SIGNAL(triggered(QAction*)),this,SLOT(openAdvancedFind(QAction*)));
}

void MainWindow::enableEdit(int index)
{
  if(editor->textEdit(index))
    {
      connect(editor->currentTextEdit(),SIGNAL(copyAvailable(bool)),ui->actionCopy,SLOT(setEnabled(bool)));
      connect(editor->currentTextEdit(),SIGNAL(copyAvailable(bool)),ui->actionCut,SLOT(setEnabled(bool)));
      connect(editor->currentTextEdit(),SIGNAL(modificationChanged(bool)),ui->actionUndo,SLOT(setEnabled(bool)));
      connect(editor->currentTextEdit(),SIGNAL(modificationChanged(bool)),ui->actionRedo,SLOT(setDisabled(bool)));
      //        connect(debugger,SIGNAL(variablesChanged(QStringList)),logs->watches(),SLOT(updateWatch(QStringList)));
      connect(debugger,SIGNAL(currentLineChanged(int)),editor->currentTextEdit(),SLOT(setDebuggerLine(int)));
      connect(editor->currentTextEdit(),SIGNAL(modificationChanged(bool)),ui->actionSave,SLOT(setEnabled(bool)));
      //status bar col && line
      connect(editor->currentTextEdit(),SIGNAL(cursorPositionChanged(int,int)),this,SLOT(updateStatusBarLineCol(int,int)));
      connect(editor->currentTextEdit(),SIGNAL(bookmarkToggled(QString,int,bool)),bookmarks,SLOT(toggleBookmark(QString,int,bool)));
      connect(editor->currentTextEdit(),SIGNAL(breakPointToggled(QString,int,bool)),breakPointsManager,SLOT(toggleBreakPoint(QString,int,bool)));
      connect(editor->currentTextEdit(),SIGNAL(breakPointEdited(QString,int)),breakPointsManager,SLOT(editBreakPoint(QString,int)));
      connect(editor->currentTextEdit(),SIGNAL(switchSourceHeader()),this,SLOT(switchSourceHeader()));
    }

  bool hasTab = editor->count() > 0;

  ui->actionFind->setEnabled(hasTab);
  ui->actionPrint->setEnabled(hasTab);
  ui->actionSave_All->setEnabled(hasTab);

}

void MainWindow::switchSourceHeader()
{
  const QString fileName = editor->currentTabFileName();

  foreach(QString file,projectExplorer->allProjectsFiles())
    {
      if(Bases::baseName(file) == Bases::baseName(fileName))
        {
          if(fileName.contains(Bases::sourceFilesReg()) && file.contains(Bases::headerFilesReg())){
              editor->openFile(file);
              break;
            }
          else if(fileName.contains(Bases::headerFilesReg()) && file.contains(Bases::sourceFilesReg())){
              editor->openFile(file);
              break;
            }
        }
    }
}

void MainWindow::setCurrentConfiguration(int index)
{
  projectExplorer->currentProject()->addSetting(Core::Project::CURRENT_CONFIG,index);
}

void MainWindow::enableBuildToolBar(int index)
{
  if(projectExplorer->projectsCount() > 0)
    return;

  bool hasSourceFile = false;

  if(editor->count() > 0)
    {
      if(editor->tabFilePath(index).contains(Bases::sourceFilesReg()))
        hasSourceFile = true;
    }

  ui->actionCompile->setEnabled(hasSourceFile);
  ui->actionCompiler_and_Debugger->setEnabled(hasSourceFile);
  ui->actionCompile_and_run->setEnabled(hasSourceFile);
  ui->actionRun->setEnabled(hasSourceFile);

}

void MainWindow::enableProject(int count)
{

  bool enableCompiler = count >= 1;

  ui->actionCompile->setEnabled(enableCompiler);
  ui->actionCompiler_and_Debugger->setEnabled(enableCompiler);
  ui->actionCompile_and_run->setEnabled(enableCompiler);
  ui->actionRun->setEnabled(enableCompiler);

  ui->actionSetting->setEnabled(count);
  ui->actionClose_Project->setEnabled(count);
  ui->actionClose_All_Projects->setEnabled(count);

  ui->actionStartup_project->setEnabled(count);
}

void MainWindow::addStartPage()
{
  auto page = new StartPage;
  editor->addTab(page,"Welcome");

  connect(page,SIGNAL(recentClicked(QString)),projectExplorer,SLOT(addProject(QString)));
  connect(page,SIGNAL(newProject()),this,SLOT(on_actionNewProject_triggered()));
  connect(page,SIGNAL(openProject()),this,SLOT(on_actionOpen_triggered()));

  //page->setupRecentProjectList(rProjects->recent());

}

void MainWindow::updateFunctionsBox(int index)
{
  //  QStringList list = classView->parser()->parseSourceFile(editor->tabFilePath(index));
  //  QString _class=classView->parser()->curClass();
  //  foreach(QString str,list)
  //  FuncsBox->insertItem(FuncsBox->count(),str);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::setupBuild()
{
  compilerSetting = new CompilerSetting("config/compilers.xml");
  compilerSetting->load();

  buildManager = new BuildManager(compilerSetting,this);
  buildManager->setObjectName("BuildManager");

  setDebugger(compilerSetting->string(Core::Compiler::DBG));
  breakPointsManager = new BreakPointsManager(this);
}

void MainWindow::setupCore()
{
  editor = new TabWidget;
  setCentralWidget(editor);

  bookmarks = new Bookmarks(editor);

  logsDock = new QDockWidget(tr("Logs"));
  addDockWidget(Qt::BottomDockWidgetArea, logsDock);

  logs = new Logs(this);

  //logs->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Ignored);
  //logs->setMaximumHeight(100);

  logsDock->setWidget(logs);

  // logsDock->setSizePolicy();

  auto debuggerClientWidget = new DebuggerClientWidget(tr("Debugger"),debugger);
  addDockWidget(Qt::BottomDockWidgetArea, debuggerClientWidget);

  tabifyDockWidget(debuggerClientWidget,logsDock);

  setupStatusBar();
}

void MainWindow::setupProject()
{
  projectExplorer = new ProjectExplorer;
  projectExplorer->setEditor(editor);

  auto configManager = new ConfigManager(compilerSetting,this);
  configManager->setObjectName("ConfigManager");

  auto manager = new ClassParserManager(projectExplorer);

  auto model = qobject_cast<QStandardItemModel*>(projectExplorer->model());
  TextEditManager::setTopLevelItem(model->invisibleRootItem());

  manager->setClassParser(TextEditManager::classParer());

  manager->parse();

  QRect rect = projectExplorer->geometry();
  rect.setWidth(100);

  projectExplorer->setGeometry(rect);

  projectDock = new QDockWidget(tr("Project"));
  projectDock->setWidget(projectExplorer);

  addDockWidget(Qt::LeftDockWidgetArea, projectDock);
}

void MainWindow::setupMake()
{
  make = new MakeFileGenerator(this);
  globalVars = new BuildVariables();
  //globalVars->setObjectName("BuildVariables");

  make->setSetting(compilerSetting);
  make->setGlobalVariables(globalVars);
}

void MainWindow::addConfigBox()
{
  configBox = new QComboBox;
  configBox->setMinimumWidth(100);
  ui->compileToolBar->addWidget(configBox);
}

void MainWindow::updateProjectConfigurations(int projectCount)
{
  if(projectCount > 0)
    {
      configBox->clear();
      foreach(Config * config,projectExplorer->currentProject()->configs())
        configBox ->addItem(config->name());

      configBox->setCurrentIndex(projectExplorer->currentProject()->toInt(Core::Project::CURRENT_CONFIG));

      connect(configBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setCurrentConfiguration(int)));
    }
  else
    {
      //configBox->clear();
      disconnect(configBox,SIGNAL(currentIndexChanged(int)),0,0);
    }

  configBox->setEnabled(projectCount);
}

void MainWindow::setupRegistry()
{
  //    setting = new Setting;
  //    QList<int> settings = setting->load();

  //    projectDock->resize(ProjectManager->height(),settings[Setting::Explorer]);
  //    logsDock->resize(logsDock->height(),);

  connect(ui->menuRecent_Projects,SIGNAL(triggered(QAction*)),this,SLOT(openRecent(QAction*)));

  /*  if(settings.value("Sessions/"+session->cu).toStringList().isEmpty())
    {
        ui->menuRecent_Projects->setDisabled(true);
    }
    else
        ui->menuRecent_Projects->setDisabled(false);*/

  recentFiles = new Recents;

  recentFiles->setKey("Recents files");
  recentFiles->set(ui->menuRecent_Files);

  recentProjects = new Recents;

  recentProjects ->setKey("Recents projects");
  recentProjects ->set(ui->menuRecent_Projects);

  connect(ui->menuRecent_Files,SIGNAL(triggered(QAction*)),this,SLOT(openRecent(QAction*)));
}

void MainWindow::updateStatusBarLineCol(int line,int col)
{
  statusLine->setText(QString::number(line));
  statusCol->setText(QString::number(col));
}

void MainWindow::setupStatusBar()
{
  statusMsg = new QLabel("Ready");

  statusLineText = new QLabel("Line");
  statusLine = new QLabel;
  statusColText = new QLabel("Col");
  statusCol = new QLabel;

  ui->statusBar->addPermanentWidget(statusMsg,73);
  ui->statusBar->addPermanentWidget(statusLineText,7);
  ui->statusBar->addPermanentWidget(statusLine,7);
  ui->statusBar->addPermanentWidget(statusColText,7);
  ui->statusBar->addPermanentWidget(statusCol,7);
}

void MainWindow::on_actionSave_triggered()
{
  editor->save(editor->currentIndex());
}

void MainWindow::on_actionNewProject_triggered()
{
  projectExplorer->addNewItem(ProjectDialog::AllTypes);
}

void MainWindow::open(const QString &file)
{
  if(file.endsWith(".smc"))
    {
      if(QFileInfo(file).exists() && openProject(file))
        recentProjects->setCurrentRecent(file);
      else
        recentProjects->remove(file);
    }

  else
    {
      if(editor->openFile(file))
        {
          //connect(editor->currentTextEdit(),SIGNAL(variableAdded(QString)),ProjectManager,SLOT(updateClassModel(QString)));
          recentFiles->setCurrentRecent(file);
        }
      else
        recentFiles->remove(file);
    }
}

bool MainWindow::openProject(const QString &fileName)
{
  if(fileName == NULL)
    return false;

  return projectExplorer->addProject(fileName);
}

bool MainWindow::buildSuccess()
{
  bool build_success = buildManager->build();

  if(build_success)
    statusMsg->setText(tr("Build Success"));
  else
    statusMsg->setText(tr("Build Failed"));

  return build_success;
}

bool MainWindow::build(const QString &projectName)
{
  logs->compileOutput()->clear();
  logs->problems()->clear();

  if(editor->currentTextEdit())
    saveAll();

  if(projectExplorer->projectsCount() == 0 )
    {
      buildManager->setSourceFile(editor->currentTabFilePath());
      return buildSuccess();
    }
  else
    return buildProject(projectName);
}

bool MainWindow::buildProject(const QString &projectName)
{
  Project * project = projectExplorer->project(projectName);

  foreach(QString dependency,project->stringList(Core::Project::DEPENDENCIES))
    {
      if(projectExplorer->projectIsOpen(dependency))
        buildProject(dependency);
    }

  QDir::setCurrent(project->path());

  make->setProject(project);
  make->generateMakeFile();

  QString makeFile = project->makeFile();

  buildManager->setMakeFile(makeFile);
  buildManager->setWorkingDir(project->path());

  return buildSuccess();
}

void MainWindow::rebuild(const QString &projectName)
{
  clean(projectName);
  build(projectName);
}

void MainWindow::run(const QString &projectName)
{
  RunConfig *runConfig = projectExplorer->project(projectName)->currentRunConfig();

  logs->appOutput()->clear();
  if(!buildManager->executeProgram(runConfig->string(
                                 Core::Project::RUNEXEC),runConfig->string(
                                 Core::Project::RUNARGS),runConfig->string(Core::Project::WORKINGDIR)
                                ,runConfig->toBool(Core::Project::RUNINTERMINAL))){
    logs->appOutput()->showMessage(runConfig->string(
                                     Core::Project::RUNEXEC) + "do not exsists");
    }
}


void MainWindow::clean(const QString &projectName)
{
  QDir dir;

  Project * project = projectExplorer->project(projectName);
  dir.setCurrent(project->path());

  buildManager->setMakeFile(project->makeFile());
  buildManager->clean();
}

void MainWindow::on_actionFullScreen_triggered()
{
  if(!isFullScreen())
    showFullScreen();
  else
    showMaximized();
}

void MainWindow::on_actionUndo_triggered()
{
  editor->currentTextEdit()->undo();
}

void MainWindow::on_actionRedo_triggered()
{
  editor->currentTextEdit()->redo();
}

void MainWindow::on_actionCut_triggered()
{
  editor->currentTextEdit()->cut();
}

void MainWindow::on_actionCopy_triggered()
{
  editor->currentTextEdit()->copy();
}

void MainWindow::on_actionPaste_triggered()
{
  editor->currentTextEdit()->paste();
}

void MainWindow::on_actionAbout_triggered()
{
  Ui::About *about = new Ui::About;

  auto dialog =new QDialog(this);
  about->setupUi(dialog);
  dialog->exec();

  delete about;

}

void MainWindow::on_actionOpen_triggered()
{
  QString name = QFileDialog::getOpenFileName(this,
                                              tr("Open Project"), QDir::currentPath(), tr("All files(*.*);;SmartCode Project (*.xml *.smc );;CPP source files(*.cpp *.cxx *.cc );;C source files(*.c);;Header files(*.h)"));
  open(name);
}

void MainWindow::on_actionFile_triggered()
{
  editor->newTab(QString("Uninted%1").arg(newCount));
  newCount++;
}

void MainWindow::on_actionFind_triggered()
{
  TextFinder *textFinder;

  textFinder = findChild<TextFinder *>("TextFinder");

  if(!textFinder)
    {
      textFinder = new TextFinder(editor);
      textFinder->setObjectName("TextFinder");
      connect(textFinder,SIGNAL(advandeSearch()),this,SLOT(openAdvancedFind(QAction*)));

      addDockWidget(Qt::BottomDockWidgetArea,textFinder);
      tabifyDockWidget(logsDock,textFinder);

      textFinder->setVisible(true);
      connect(textFinder,SIGNAL(visibilityChanged(bool)),textFinder,SLOT(deleteLater()));
    }
}

void MainWindow::compileAndRun()
{
  const QString projectName = projectExplorer->currentProjectName();

  if(build(projectExplorer->currentProjectName()))
    run(projectName);
}

void MainWindow::on_actionRun_triggered()
{
  run(projectExplorer->currentProjectName());
}

void MainWindow::on_actionCompile_and_run_triggered()
{
  compileAndRun();
}

void MainWindow::on_actionSetting_triggered()
{
  Project * curProject = projectExplorer->currentProject();
  ProjectSetting *proSetting = new ProjectSetting(curProject,this);
  proSetting->getProjectsList(projectExplorer->toProjects());

  proSetting->exec();

  delete proSetting;
}

void MainWindow::on_actionOptions_triggered()
{
  auto options = new Options(this);

  options->setupCompilerSetting(compilerSetting);
  options->exec();

  delete options;
}

void MainWindow::setDebugger(const QString& debuggerName)
{
  if(debuggerName == "gdb")
    debugger = new GDB;
  else
    debugger = new Debugger;
}

void MainWindow::on_actionDevCpp_triggered()
{
  QString fileName = QFileDialog::getOpenFileName(this,
                                                  tr("Import DevCpp Project"), QDir::currentPath(), tr("DevCpp Project (*.dev);;All files(*.*)"));
  if(fileName.isEmpty())
    return;

  auto dev = new DevCpp;

  dev->import(fileName);
  openProject(fileName.replace(".dev",".smc"));

  delete dev;
}

void MainWindow::on_actionCompile_triggered()
{
  build(projectExplorer->currentProjectName());
}

void MainWindow::runDebugger()
{
 // QString program = projectExplorer->currentProject()->currentConfiguration()->destDirTarget();

  QString program = "C:/Users/DELL_PC/Documents/Untitled/Untitled.exe";
//  if(QFileInfo(program).exists())
//    {
      debugger->setProgram(program);
      BreakPoint *breakPoint = new BreakPoint(editor->currentTabFileName(),true);
      breakPoint->setType(BreakPoint::FileNameAndLineNumber);
      debugger->setBreakPoint(breakPoint,true);
      debugger->load();
//    }
//  else
//    {
//      int exec = QMessageBox::information(this,"SmartCode","The program was not compiled yet Compile it");

//      if(exec == QMessageBox::Ok)
//        build(projectExplorer->currentProjectName());
//      else
//        return;
//    }
}

void MainWindow::on_actionDbgNext_Line_triggered()
{
  debugger->step(Debugger::NextLine);
}

void MainWindow::on_actionDbgRun_to_cursor_triggered()
{
  int line,index;

  editor->currentTextEdit()->getCursorPosition(&line,&index);

  BreakPoint * breakPoint = breakPointsManager->addBreakPoint(editor->currentTabFileName(),line);

  runDebugger();

  debugger->setBreakPoint(breakPoint,true);
  debugger->run();
}

void MainWindow::on_actionDbgStart_triggered()
{
  runDebugger();

  foreach(BreakPoint * breakPoint,breakPointsManager->toBreakPoints())
    {
      debugger->setBreakPoint(breakPoint,true);
    }

  debugger->run();
}

void MainWindow::on_actionDbgContinue_triggered()
{
  debugger->Continue();
}

void MainWindow::on_actionDbgStep_into_triggered()
{
  debugger->step(Debugger::StepIn);
}

void MainWindow::on_actionDbgStop_triggered()
{
  debugger->stop();
  editor->currentTextEdit()->markerDeleteAll(1);
}

void MainWindow::on_actionDbgStep_out_triggered()
{
  debugger->step(Debugger::StepOut);
}

void MainWindow::on_actionDbgNext_Instruction_triggered()
{
  debugger->step(Debugger::NextInstruction);
}


void MainWindow::on_actionClean_triggered()
{
  clean(projectExplorer->currentProjectName());
}

void MainWindow::on_actionStopProgram_triggered()
{
  buildManager->abort(projectExplorer->currentProject()->currentConfiguration()->destDirTarget());
}

void MainWindow::openAdvancedFind(QAction *action)
{
  auto advancedSearch = new AdvancedSearch(projectExplorer);

  auto act = ui->menuAdvanced_Find->actions();

  for (int index = 0 ; index < act.count() ; index++)
    {
      if(act.at(index) == action)
        {
          advancedSearch->setFindMode(index);
        }
    }

  addDockWidget(Qt::BottomDockWidgetArea,advancedSearch);
}

void MainWindow::openRecent(QAction *action)
{
  open(action->text());
}

void MainWindow::on_actionPrint_triggered()
{
  QsciPrinter printer ;

  auto dlg = new QPrintDialog(&printer, this);

  if (dlg->exec() == QDialog::Accepted)
    printer.printRange(editor->currentTextEdit());

  delete dlg;
}

bool MainWindow::event(QEvent *e)
{
//  if(editor)
//    {
//      if(e->type() == QEvent::WindowActivate && editor->currentTextEdit())
//        {
//          int count = editor->count();

//          if(count > 0 )
//            {
//              for(int i =0; i<count; i++)
//                {
//                  const QString fileName = editor->tabFilePath(i);

//                  QDateTime fileLastModified = QFileInfo(fileName).lastModified();

//                  if(editor->tabFileLastModified(i) != fileLastModified)
//                    {
//                      editor->setFileLastModified(i,fileLastModified);

//                      int ret = QMessageBox::information(this,"Information",
//                                                         tr("File %1 is modified by external editor reload it")
//                                                         .arg(fileName),QMessageBox::Yes|QMessageBox::YesAll|
//                                                         QMessageBox::No|QMessageBox::NoAll);

//                      if(ret == QMessageBox::Yes)
//                        {
//                          QFile file(fileName);

//                          file.open(QFile::ReadOnly);
//                          editor->currentTextEdit()->setText(file.readAll());

//                        }
//                    }
//                }
//            }
//        }

//    }
  return QMainWindow::event(e);

}

void MainWindow::on_actionSave_All_triggered()
{
  saveAll();
}

void MainWindow::saveAll()
{
//  for (int i = 0; i < editor->count(); i++)
//    {
//      editor->saveFile(editor->tabFilePath(i));
//    }
}


void MainWindow::on_actionClose_Project_triggered()
{

}

void MainWindow::on_actionAdd_a_class_triggered()
{
  projectExplorer->showProjectWizard("core/files/C++ files/C++ Class/C++ Class.tpl");
}

void MainWindow::on_actionAdd_element_triggered()
{
  projectExplorer->addNewFile();
}

void MainWindow::updateActionStartupProjectText(const QString &project)
{
  QSettings settings;

  const QStringList startupProjects = settings.value("StartupProjects").toStringList();

  changeActionStartupProjectText(startupProjects.contains(project));


}

void MainWindow::changeActionStartupProjectText(bool projectExsists)
{
  if(projectExsists)
    {
      ui->actionStartup_project->setText(tr("Remove project from startup projects"));
    }
  else
    {
      ui->actionStartup_project->setText(tr("Add project to startup projects"));
    }
}

void MainWindow::on_actionStartup_project_triggered()
{
  if(ui->actionStartup_project->text().startsWith(tr("Add")))
    {
      QSettings settings;

      const QStringList startupProjects = settings.value("StartupProjects").toStringList();

      if(startupProjects.count() > 0)
        {
          QWidget * widget = new QWidget;

          QVBoxLayout * layout = new QVBoxLayout;

          QCheckBox addBox(tr("Add to startup projects"));
          QCheckBox setOnlyBox(tr("Set the only startup project"));

          addBox.setAutoExclusive(true);
          addBox.setChecked(true);
          setOnlyBox.setAutoExclusive(true);

          layout->addWidget(&addBox);
          layout->addWidget(&setOnlyBox);

          widget->setLayout(layout);

          if(Dialog::exec(this,"SmartCode",tr("What do you want to do"),widget))
            {
              setStartupProject(projectExplorer->currentProjectName(),addBox.isChecked());
              changeActionStartupProjectText(true);
            }
        }
      else
        {
          setStartupProject(projectExplorer->currentProjectName());
          changeActionStartupProjectText(true);

        }
    }
  else
    {
      removeStartupProject(projectExplorer->currentProjectName());
    }


}

void MainWindow::setStartupProject(const QString &project,bool addToStartupProjects)
{
  QSettings settings;
  QStringList startupProjects ;

  if(addToStartupProjects)
    {

      startupProjects = settings.value("StartupProjects").toStringList();
      startupProjects.append(project);
    }
  else
    startupProjects.append(project);

  settings.setValue("StartupProjects", startupProjects);
}

void MainWindow::removeStartupProject(const QString &project)
{
  QSettings settings;
  QStringList startupProjects ;

  startupProjects = settings.value("StartupProjects").toStringList();
  startupProjects.removeOne(project);

  settings.setValue("StartupProjects", startupProjects);
  changeActionStartupProjectText(false);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  //  QSettings settings;

  //  settings.setValue("ProjectExplorerWidth",ProjectManager->width());
  //  settings.setValue("LogsHeight",logs->height());

  event->accept();
}

void MainWindow::on_actionAStyle_triggered()
{
  int currentPos = editor->currentTextEdit()->curPos();
  QTimer::singleShot(1,editor->currentTextEdit(),SLOT(formatSourceCode()));
  editor->currentTextEdit()->setCurrentPos(currentPos);
}

void MainWindow::on_actionPrevBookmark_triggered()
{
  bookmarks->prevBookmark();
}

void MainWindow::on_actionNextBookmark_triggered()
{
  bookmarks->nextBookmark();
}

void MainWindow::on_actionRebuild_triggered()
{
  rebuild(projectExplorer->currentProjectName());
}

void MainWindow::on_actionExit_triggered()
{
  close();
}
