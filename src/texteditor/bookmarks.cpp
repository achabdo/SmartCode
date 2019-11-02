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

#include "bookmarks.h"
#include <QMultiMap>
#include <tabwidget.h>

Bookmarks::Bookmarks(TabWidget * _editorManager,QObject *parent) : QObject(parent)
{
  editorManager = _editorManager;
}

Bookmarks::~Bookmarks()
{

}

void Bookmarks::toggleBookmark(const QString &fileName , int line, bool isToggled)
{
  if(isToggled)
    {
      Bookmark bookmark;

      bookmark.fileName = fileName;
      bookmark.line = line;

      bookmarksList.append(bookmark);
      currentBookmark = --bookmarksList.end();

    }
  else
    {
      if(bookmarksList.count() == 1)
        {
          bookmarksList.removeFirst();
        }
      else
        {
          QList<Bookmark>::iterator i;

          for (i = bookmarksList.begin(); i != bookmarksList.end(); ++i)
            {
              Bookmark bookmark = *i;

              if(bookmark.fileName == fileName && bookmark.line == line)
                {
                  if(i == --bookmarksList.end())
                    {
                      bookmarksList.erase(i);
                      currentBookmark = i - 1;
                    }
                  else
                    currentBookmark = bookmarksList.erase(i);
                }
            }
        }
    }
}

void Bookmarks::nextBookmark()
{
  prevNextBookmar(true);
}

void Bookmarks::prevBookmark()
{
  prevNextBookmar(false);
}

void Bookmarks::prevNextBookmar(bool next)
{
  if(next)
    {
      if(currentBookmark != bookmarksList.constEnd() - 1)
        currentBookmark += 1;
      else
        return;
    }
  else
    {
      if(currentBookmark != bookmarksList.constBegin())
        currentBookmark -= 1;
      else
        return;
    }

  Bookmark bookmark = *currentBookmark;

  editorManager->openFileAt(bookmark.fileName,bookmark.line,0);


}

