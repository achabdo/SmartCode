#ifndef COMPILEROPTIONSWIDGET_H
#define COMPILEROPTIONSWIDGET_H

#include <QWidget>
#include "build_global.h"

class QListWidget;
class QTreeWidget;
class QTextEdit;

class CompilerOptionsCategory;

typedef QList<CompilerOptionsCategory *> CompilerOptionsCategories;

class BUILDSHARED_EXPORT CompilerOptionsWidget : public QWidget
{
  Q_OBJECT
public:
  explicit CompilerOptionsWidget(QWidget *parent = 0);

  void setCompilerOptionsCategories(const CompilerOptionsCategories &categories);
  void setActivatedFlags(const QStringList &activatedFlags);

  ~CompilerOptionsWidget();

  bool flagsChanged();
  QStringList flags();

signals:

public slots:
private slots:
  void showOptions(int row);
private:
  QListWidget* categoriesWidget;
  QTreeWidget *  optionsWidget;
  QTextEdit* addFlagsEdit;

  CompilerOptionsCategories _categories;

  QStringList actFlags;


};

#endif // COMPILEROPTIONSWIDGET_H
