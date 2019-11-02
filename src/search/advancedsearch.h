#ifndef ADVANCEDSEARCH_H
#define ADVANCEDSEARCH_H
#include "search_global.h"

#include <QDockWidget>
#include <QFile>
#include <QDir>
#include <QTreeWidget>
#include <QFileDialog>
#include <QLabel>
#include <QDebug>

class ProjectExplorer;

namespace Ui {
class AdvancedSearch;
}

class SEARCHSHARED_EXPORT AdvancedSearch : public QDockWidget
{
    Q_OBJECT
    
public:
    enum FindMode {CurrentFile,CurrentProject,AllProject,SystemFiles} ;

    explicit AdvancedSearch(ProjectExplorer * projectExplorer , QWidget *parent = 0);
    ~AdvancedSearch();

    void find(FindMode findMode);
    void openItem();

    void setFindMode(int index);

    QTreeWidget *findsList() const;
signals:

private slots:
    void on_pushButton_clicked();

    void openFile(QTreeWidgetItem* item,int col);
    void on_getDir_clicked();

    void showSearchDir(int index);
    void clearFinds();

private:
    void findText(QString text, const QStringList &files);

    Ui::AdvancedSearch *ui;
    QTreeWidget *finds;
    QLabel * findResult;

    ProjectExplorer * proExplorer ;
};

#endif // ADVANCEDSEARCH_H
