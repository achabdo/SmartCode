#ifndef BOOKMARKS_H
#define BOOKMARKS_H

#include "texteditor_global.h"

#include <QObject>
#include <QList>

class TabWidget;

class TEXTEDITORSHARED_EXPORT Bookmarks : public QObject
{
  Q_OBJECT
public:
  explicit Bookmarks(TabWidget *_editorManager, QObject *parent = 0);
  ~Bookmarks();

  void toggleBookmark(bool toggle);

signals:

public slots:

  void toggleBookmark(const QString &fileName, int line,bool isToggled);

  void nextBookmark();
  void prevBookmark();
private:

  struct Bookmark
  {
    QString fileName;
    int line;

  };

  QList<Bookmark> bookmarksList;

  TabWidget * editorManager;
  void prevNextBookmar(bool next);



  QList<Bookmark>::iterator currentBookmark;
};

#endif // BOOKMARKS_H
