#ifndef COMPILERSETTINGWIDGET_H
#define COMPILERSETTINGWIDGET_H

#include "BUILD_global.h"

#include <QDialog>
#include <QDir>
#include <QHash>

class CompilerSetting;
class TabSettingManager;
class QListWidgetItem;
class QTreeWidgetItem ;

namespace Ui {
  class CompilerSettingWidget;
}

class BUILDSHARED_EXPORT CompilerSettingWidget : public QWidget
{
  Q_OBJECT

public:
  explicit CompilerSettingWidget(CompilerSetting *compilerSetting,QWidget *parent = 0);

  ~CompilerSettingWidget();

  QStringList Libs();
  void setSetting(CompilerSetting*s);
  void setupCompilerOptions(QWidget * widget);
signals:

private slots:
  //    void on_autoDetecte_clicked();

  void saveSetting();
  void setProgramPath();

  void addCompiler(QAction *action);

  void cloneCompiler();
  void removeCompiler();

  void updateCurrentCompilerName(const QString &compilerName);
  void activeCompiler(QTreeWidgetItem * compilerItem, int col);

  void on_cloneCompilerButton_clicked();

  void on_removeCompilerButton_clicked();

private:

  int currentButtonClicked;

  void setup();
  void loadSetting();

  Ui::CompilerSettingWidget *ui;
  CompilerSetting *compilerSetting;
  TabSettingManager *tabSettingManager;

  void autoDetecteCompilers();
};

#endif // COMPILERSETTINGWIDGET_H
