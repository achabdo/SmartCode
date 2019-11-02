#ifndef TABSETTING_H
#define TABSETTING_H

#include "core_global.h"

#include <QWidget>

class QTreeWidget;
class QTreeWidgetItem;
class QTabWidget;
class QLineEdit;
class QMenu;

namespace Ui {

  class TabSetting;
}

class SettingsManager;

class CORESHARED_EXPORT TabSetting : public QWidget
{
  Q_OBJECT

public:

  explicit TabSetting(QWidget *parent = 0);
  ~TabSetting();

  QTreeWidget *addContent(const QString &name, const QString &element, bool itemHasIcon = true);
  QTreeWidget * currentList() const;
  QTreeWidget  * list(int index) const;

  QString itemText(int row, int column, int index = 0) const ;
  QStringList itemsText(int index, int column = 0);

  void addTab();

  void addItem(const QStringList &labels, int index = 0);
  void addItems(const QStringList &labels, int index =0);

  void clear(int mode = 0);
  QString tabElement(int index) const ;

  QTabWidget * tabWidget() const ;

  int listCount(int index) const ;

  void setCurrentListHeaderLabels(const QStringList &labels);

  void createAddButtonMenu();

  void clearAll();


private slots:

  void getPath_clicked();

  void editItem(QTreeWidgetItem* item,int column);

  void on_add_clicked();

  void on_del_clicked();

  void on_clear_clicked();

  void setItemText();
  void addCustomVariable();
private:

  Ui::TabSetting *ui;

  int itemIndex(QTreeWidgetItem * item) const;
  int currentItemIndex() const;

  QHash<int,QString> mode;

  QTabWidget * tab;
  QTreeWidgetItem *currentListItem() const;
  QLineEdit *currentlineEdit() const;

  int currentListColumn() const;
};

#endif // TABSETTING_H
