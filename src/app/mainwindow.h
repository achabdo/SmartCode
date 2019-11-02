#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;

}

class Logs;
class Debugger;

class QComboBox;
class ProjectExplorer;
class TabWidget;
class ClassGenerator;

class BuildManager;
class CompilerSetting;

class Recents;

class MakeFileGenerator;
class QLabel;
class Setting;
class Bookmarks;
class BreakPointsManager;
class BuildVariables;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void open(const QString &file);
protected:
    bool event(QEvent *e);
    void closeEvent(QCloseEvent * event);
private slots:
    void setupStatusBar();
    void saveSettings();

    void updateProjectConfigurations(int projectCount);
    void updateStatusBarLineCol(int line , int message);

    bool openProject(const QString &fileName);

    void updateFunctionsBox(int index);

    void openRecent(QAction * action);

    void addStartPage();

    void runDebugger();

    void openAdvancedFind(QAction * action);

    bool build(const QString &projectName);
    bool buildProject(const QString &projectName);

    void rebuild(const QString &projectName);
    void run  (const QString &projectName);
    void clean (const QString &projectName);

    void on_actionSave_triggered();

    void on_actionNewProject_triggered();

    void on_actionUndo_triggered();

    void on_actionFullScreen_triggered();

    void on_actionRedo_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionAbout_triggered();

    void on_actionOpen_triggered();

    void on_actionFile_triggered();

    void on_actionFind_triggered();

    void on_actionRun_triggered();

    void on_actionCompile_and_run_triggered();

    void on_actionSetting_triggered();

    void on_actionOptions_triggered();


    void on_actionDevCpp_triggered();

    void on_actionCompile_triggered();

    void on_actionDbgRun_to_cursor_triggered();

    void on_actionDbgStart_triggered();

    void on_actionDbgStop_triggered();

    void on_actionDbgNext_Line_triggered();

    void on_actionDbgContinue_triggered();

    void on_actionDbgStep_into_triggered();

    void on_actionDbgStep_out_triggered();

    void on_actionDbgNext_Instruction_triggered();


    void enableEdit(int index);

    void enableProject(int count);

    void on_actionClean_triggered();

    void on_actionStopProgram_triggered();

    void on_actionPrint_triggered();

    void on_actionSave_All_triggered();

    void on_actionClose_Project_triggered();

    void on_actionAdd_a_class_triggered();

    void on_actionAdd_element_triggered();
    void on_actionStartup_project_triggered();

    void updateActionStartupProjectText(const QString &project);
    void on_actionAStyle_triggered();

    void on_actionPrevBookmark_triggered();

    void on_actionNextBookmark_triggered();

    void on_actionRebuild_triggered();

    void enableBuildToolBar(int index);
    void on_actionExit_triggered();

    void switchSourceHeader();
    void setCurrentConfiguration(int index);

private:
    Ui::MainWindow *ui;

    TabWidget * editor;
    ProjectExplorer *projectExplorer;
    MakeFileGenerator * make;
    BuildVariables * globalVars;

    void addConfigBox();
    void setupBuild();
    void setupProject();
    void setupMake();
    void setupRegistry();
    void setupCore();
    void connects();
    void menuConnects();

    void saveAll();
    void compileAndRun();

    int newCount;

    Recents *recentFiles;
    Recents *recentProjects;
    BuildManager *buildManager;

    CompilerSetting *compilerSetting;

    //QStatusBar Section

    QLabel *statusMsg;
    QLabel *statusLineText ;
    QLabel *statusLine;
    QLabel *statusColText;
    QLabel *statusCol;

    QDockWidget * logsDock;
    QDockWidget * projectDock;
    QComboBox * configBox;
    Setting * setting;
    Debugger * debugger;
    Logs * logs;
    Bookmarks * bookmarks;
    BreakPointsManager * breakPointsManager;

    void setStartupProject(const QString &project, bool addToStartupProjects = false);

    void removeStartupProject(const QString &project);
    void changeActionStartupProjectText(bool projectExsists);
    void setDebugger(const QString &debuggerName);
    bool buildSuccess();
};

#endif // MAINWINDOW_H
