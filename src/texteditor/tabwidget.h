#ifndef TABWIDGET_H
#define TABWIDGET_H

#include "texteditor_global.h"

#include <QTabWidget>
#include <QTabBar>
#include <QShortcut>
#include <QClipboard>
#include <QListView>
#include <QMenu>
#include <QMessageBox>
#include <QMouseEvent>
#include <QStackedWidget>
#include <QStyle>
#include <QToolButton>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>

class TextEditManager;
class VersionControl;
class ClassParser;
class TextEdit;
class TextEditArea;

namespace TextEditor
{
class LexerCPP;
}

class TabBar : public QTabBar
{
    Q_OBJECT

signals:
    void tabsChanged();
    void newTab(const QString &name,bool makeCurrent);
    void cloneTab(int index);
    void closeTab(int index);
    void closeOtherTabs(int index);

public:
    TabBar(QWidget *parent = 0);


protected:


private slots:
    void selectTabAction();
    void cloneTab();
    void closeTab();
    void closeOtherTabs();
    void contextMenuRequested(const QPoint &position);

private:
    QList<QShortcut*> m_tabShortcuts;
    friend class TabWidget;

    QPoint m_dragStartPos;
    int m_dragCurrentIndex;
};

class TEXTEDITORSHARED_EXPORT TabWidget : public QTabWidget
{
    Q_OBJECT
public:

    struct FileInfo
    {
        QString fileName;
        QDateTime lastModified;
    };

    explicit TabWidget(QWidget *parent = 0);

    TextEdit *currentTextEdit() const;
    bool fileIsOpen(const QString &fileName);

    QString tabFilePath(int index);
    int toTabIndex(const QString &fileName);
    FileInfo tabFileInfo(int index);

    QDateTime tabFileLastModified(int index);

    bool saveFile(const QString &fileName);

    TextEdit *textEdit(int index) const;

      TextEditArea *textEditArea(int index) const;
      TextEditArea * currentTextEditArea() const;

    void out(const QString &fileName,const QString text);

    QString currentTabFileName();
    QString currentTabFilePath();
    QString currentTabPath();

    void setFileLastModified(int index , const QDateTime &lastModified );


signals:
    //void tabCountChanged(bool isEmpty);

public slots:

    TextEdit * newTab(const QString &tabName,bool makeCurrent = true );

    void cloneTab(int index = -1);
    void closeTab(int index = -1);
    void closeOtherTabs(int index);

    bool openFile(const QString &fileName);
    void openFileAt(const QString &fileName , int line, int index);

    bool save(int index);
    bool saveAs();

    //git part
    void blame(const QString &fileName);
    void diff(const QString &fileName);
    void log(const QString &fileName);

    void setVersionControl(VersionControl * verControl);
private slots:

    void setEditorToClParser();

private:
    QHash<int, FileInfo > tabInfo;
    QHash<QString,int> bookmarks;

    TabBar * m_tabBar;

    VersionControl * versionControl;
};

#endif // TABWIDGET_H
