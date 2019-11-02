#ifndef PROJECTSETTING_H
#define PROJECTSETTING_H

#include "project_global.h"

#include <QDialog>


class Project;
class QLineEdit;
class QTreeWidget;

class TabSettingManager;
class Project;
class CompilerOptionsCategory;
class Config;
class QTreeWidgetItem;
class CompilerOptionsWidget;

namespace Ui {
class ProjectSetting;

}


class PROJECTSHARED_EXPORT ProjectSetting : public QDialog
{
  Q_OBJECT

public:
  enum ActionType{add,remove};
  enum List {ExecutablesDir,IncludePaths,IncludeLibs,ResourcesCompiler};

  explicit ProjectSetting(Project *project,QWidget *parent=0);

  ~ProjectSetting();

  void updateCompilerOptions(const QStringList &flags);
  void setupCustomVariables();

  void getProjectsList(QStringList projects);
public slots:
  void accept();

  void addRunConfiguration();
  void cloneRunConfiguration();
  void renameRunConfiguration();
  void removeRunConfiguration();

  void addConfiguration();
  void cloneConfiguration();
  void renameConfiguration();
  void removeConfiguration();

private slots:

  void setCurrentPageTitle(QTreeWidgetItem *item, int);
  void setCurrentPage(const QModelIndex &index);

  void updateRunConfiguration(int index);
  void setCurrentConfiguration(int index);

  void on_toolButton_clicked();
  void on_getIconButton_clicked();

  void enableRemoveConfigButton(int);
  void setRunInTerminal(int state);
private:

  Ui::ProjectSetting *ui;
  Project * pro;

  ActionType actionType;
  TabSettingManager *tabSettingManager;
  CompilerOptionsWidget * compilerOptionsWidget;

  void setup();

  void applyConfiguration(Config * config);
  void loadConfiguration(int index);

  void setupConfiguration();
  void setupRunConfiguration();
  Config* configurationChanged();
};



#endif // PROJECTSETTING_H
