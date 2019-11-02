#ifndef TREE_H
#define TREE_H

#include "project_global.h"

#include <QStandardItem>
#include <QTreeView>

#include "projectdialog.h"

class Project;
class TabWidget;
class QTreeWidget;
class QTreeWidgetItem;

class StandardItem : public QStandardItem
{
public:
    enum myType{Sources = 1000, Headers = 1001,Resources = 1002,
                OtherFiles = 1003,DirType = 1004 ,
                FileType = 1005};
    StandardItem();
    int type() const ;
    bool operator<(const QStandardItem &other) const;
};

class PROJECTSHARED_EXPORT ProjectExplorer : public QTreeView
{
    Q_OBJECT
public:
    explicit ProjectExplorer(QWidget *parent = 0);

    QStandardItem *createItem(QString data, QStandardItem *parent=0);
    void setEditor(TabWidget *Editor);
    void setCurrentProject(const QString &project);

    QString toFileName(const QModelIndex &index) const;
    QStandardItem *fileNameItem(const QString &fileName) const;
    QModelIndex indexFromFileName(const QString &file) const;
    QString projectPath(const QString &project) const;

    Project * projectFromItem();

    QString projectNameFromItem()  const;
    QString projectPathFromItem() const;
    QString projectParentFromItem() const;

    Project *project(const QString &projectName, const QString &projectParent = QString()) const;
    Project *currentProject() const;

    bool projectHasParent();

    QString currentProjectName() const;
    QString currentProjectPath() const;
    QString currentProjectFilter(const QString &filterName) const;

    QStringList toProjects() const;
    int projectsCount() const;

    TabWidget *Editor() const;
    QStringList Projects() const;

    QStringList projectFiles(const QString &projectName, const QString &filter = "*.*");
    QStringList allProjectsFiles(const QString &filter = "*.*");
    QStringList currentProjectFiles(const QString &filter = "*.*");

    QRegExp filterFromName(const QString &name);

    void newProject(const QString &projectName,const QString &parent = QString());

    bool projectIsOpen(const QString &projectName);
    bool isClass(const QString &data);

    QString modelString(const QModelIndex &index);
    bool itemIsFile(const QModelIndex &index);
    QString attrFuncFileName(const QModelIndex &index);

    QStandardItem *addParentItem(const QString &projectName , const QString &itemName,
                                 QStringList parentFiles = QStringList(), bool addEmptyParent = false);

    void addNewItem(ProjectDialog::NewType newType, bool isSubProject = false);

     QString fileType(const QString &file);
signals:
    void projectCountChanged(int count);
    void currentProjectChanged(const QString &project);
    void projectAdded();
    void projectClosed();

    void rebuild(const QString &project);
    void build(const QString &project);
    void clean(const QString &project);
    void run(const QString &project);

    void fileAdded(const QString &file);
   // void fileOpened(const QString &file);

public slots:

    void showProjectWizard(const QString &templat);
    bool addProject(const QString &name);

    void closeProject();
    void closeCurrentProject();
    void closeAllProject();

    void activeProject();

    void getFile(const QModelIndex &index);
    void addExstingFiles();
    void addNewFile();
    void addFiles(const QStringList &fileNames);
    void removeCurrentFile();
    void renameFile();

    void showMenu();
private slots:

    void findFunction(const QModelIndex &index);

    void openExplorer();
    void addDirectory();
    void removeFiles();

    void removeSubProject();
    void addSubProject();


    void rebuild();
    void clean();
    void build();
    void run();

    void blame();
    void diff();
    void log();

    void showSubProjectWizard(const QString &templat);
private:

    inline QString filter(const QString &path , const QString &filter) const {return path + "/" + filter;}
    inline QString filterPath(const QString &filter) const{return filter.left(filter.lastIndexOf("/")) ;}

    QString currentFileName();

    QStringList projectParents();

    QIcon folderIcon() const;
    QIcon fileIcon() const;


    QStandardItem * checkParentItemExsits(const QString &parentName);
    void addFilesToRemove(QTreeWidget * treeWidget,const QString &projectName);

    bool openProject(const QString &projectName);
    void showMessage(const QString &title, const QString &msg);

    void printFiles(const QString &filter ,const QStringList &files);

    QStandardItem *itemFromView();
    QStandardItem *itemFromIndex(const QModelIndex &index) const;
    QStandardItem *itemFromName(const QString &itemName) const;

    void removeProject(const QModelIndex &index);

    void removeItem(const QModelIndex &i);
    void removeFile(const QModelIndex &index, bool removeFromFileSystem);

    QHash<QStandardItem *,QString> items;
    QHash<QStandardItem * , QString > fileNames;

    QHash<QString,Project * > projects;

    QString var;

    TabWidget * editor;

    QString curProject;

};

#endif // TREE_H
