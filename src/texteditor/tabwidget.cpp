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

#include "tabwidget.h"
#include "texteditarea.h"
#include "textedit.h"
#include <QFileDialog>
#include <bases.h>
#include "texteditmanager.h"
#include "classparser.h"
#include <versioncontrol.h>
#include <git.h>

TabBar::TabBar(QWidget *parent)
  : QTabBar(parent)
{
  setContextMenuPolicy(Qt::CustomContextMenu);
  setAcceptDrops(true);

  connect(this, SIGNAL(customContextMenuRequested(QPoint)),
          this, SLOT(contextMenuRequested(QPoint)));

  QString ctrl = QLatin1String("Ctrl+%1");

  for (int i = 1; i <= 10; ++i) {

      int key = i;

      if (key == 10)
        key = 0;

      QShortcut * shortCut = new QShortcut(ctrl.arg(key), this);
      m_tabShortcuts.append(shortCut);
      connect(shortCut, SIGNAL(activated()), this, SLOT(selectTabAction()));
    }

  setTabsClosable(true);

  connect(this, SIGNAL(tabCloseRequested(int)),
          this, SIGNAL(closeTab(int)));

  setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);

  setMovable(true);


}

void TabBar::selectTabAction()
{
  if (QShortcut *shortCut = qobject_cast<QShortcut*>(sender())) {
      int index = m_tabShortcuts.indexOf(shortCut);
      if (index == 0)
        index = 10;
      setCurrentIndex(index);
    }

}

void TabBar::contextMenuRequested(const QPoint &position)
{
  QMenu menu;

  menu.addAction(tr("New &Tab"), this, SIGNAL(newTab(QString,bool)), QKeySequence::AddTab);

  int index = tabAt(position);

  if (-1 != index) {
      QAction *action = menu.addAction(tr("Clone Tab"),
                                       this, SLOT(cloneTab()));
      action->setData(index);

      menu.addSeparator();

      action = menu.addAction(tr("&Close Tab"),
                              this, SLOT(closeTab()), QKeySequence::Close);
      action->setData(index);

      action = menu.addAction(tr("Close &Other Tabs"),
                              this, SLOT(closeOtherTabs()));
      action->setData(index);

      menu.addSeparator();

    }
  else {
      menu.addSeparator();
    }
  menu.exec(QCursor::pos());
}

void TabBar::cloneTab()
{
  if (QAction *action = qobject_cast<QAction*>(sender())) {
      int index = action->data().toInt();
      emit cloneTab(index);
    }
}

void TabBar::closeTab()
{
  if (QAction *action = qobject_cast<QAction*>(sender())) {
      int index = action->data().toInt();
      emit closeTab(index);
    }
}

void TabBar::closeOtherTabs()
{
  if (QAction *action = qobject_cast<QAction*>(sender())) {
      int index = action->data().toInt();
      emit closeOtherTabs(index);
    }
}

void TabWidget::cloneTab(int index)
{
  if (index < 0)
    index = currentIndex();
  if (index < 0 || index >= count())
    return;

  TextEdit  *tab = newTab(tabBar()->tabText(index),false);
  tab->setText(textEdit(index)->text());
}

void TabWidget::closeTab(int index)
{
  if (index < 0)
    index = currentIndex();
  if (index < 0 || index >= count())
    return;

  bool hasFocus = false;

  if ( TextEdit *tab = textEdit(index)) {
      if(tab->isModified())
        {
          int exec = QMessageBox::warning(this, tr("Application"),
                                          tr("The document has been modified.\n"
                                             "Do you want to save your changes?"),
                                          QMessageBox::Yes | QMessageBox::Default,
                                          QMessageBox::No,
                                          QMessageBox::Cancel | QMessageBox::Escape);
          if (exec == QMessageBox::Yes)
            save(index);
          else if (exec == QMessageBox::Cancel)
            return ;
        }

      hasFocus = tab->hasFocus();

    }

  QWidget * curEdit = widget(index);
  removeTab(index);

  curEdit->deleteLater();
}

void TabWidget::closeOtherTabs(int index)
{
  if (-1 == index)
    return;
  for (int i = count() - 1; i > index; --i)
    closeTab(i);
  for (int i = index - 1; i >= 0; --i)
    closeTab(i);
}


TabWidget::TabWidget(QWidget *parent) :
  QTabWidget(parent), m_tabBar(new TabBar(this))
{
  setElideMode(Qt::ElideRight);


  connect(m_tabBar, SIGNAL(newTab(QString,bool)), this, SLOT(newTab(QString,bool)));
  connect(m_tabBar, SIGNAL(closeTab(int)), this, SLOT(closeTab(int)));
  connect(m_tabBar, SIGNAL(cloneTab(int)), this, SLOT(cloneTab(int)));
  connect(m_tabBar, SIGNAL(closeOtherTabs(int)), this, SLOT(closeOtherTabs(int)));

  connect(this,SIGNAL(currentChanged(int)),this,SLOT(setEditorToClParser()));

  setTabBar(m_tabBar);

  TextEditManager * textEditManager = new TextEditManager(this);

  setVersionControl(new Git);

}

TextEdit * TabWidget::currentTextEdit() const
{
    return textEdit(currentIndex());
}

TextEdit * TabWidget::textEdit(int index) const
{ 
  TextEditArea * edit = textEditArea(index);

  if(edit)
    return edit->textEdit;

  return 0;
}

TextEditArea *TabWidget::textEditArea(int index) const
{
  QWidget *widget = this->widget(index);

  return qobject_cast<TextEditArea*>(widget);
}

TextEditArea *TabWidget::currentTextEditArea() const
{
  return textEditArea(currentIndex());
}

TextEdit *TabWidget::newTab(const QString &tabName,bool makeCurrent)
{
  TextEditArea * textEditArea = new TextEditArea(tabName);

  connect(textEditArea->textEdit,SIGNAL(openFile(QString,int,int)),this,SLOT(openFileAt(QString,int,int)));

  QFileInfo fileInfo(tabName);

  addTab(textEditArea,fileInfo.fileName());

  if (makeCurrent)
    setCurrentWidget(textEditArea);

  if (count() == 1)
    currentChanged(currentIndex());

  FileInfo info;

  info.fileName = tabName;
  info.lastModified = fileInfo.lastModified();

  tabInfo.insert(currentIndex(),info);

  return textEditArea->textEdit;
}

void TabWidget::setEditorToClParser()
{
  if(currentTextEdit())
    TextEditManager::classParer()->setEditor(currentTextEdit());
}

bool TabWidget::openFile(const QString &fileName)
{
  if(!fileIsOpen(fileName))
    {
      QFile file(fileName);

      if (!file.open(QFile::ReadOnly ))
        {
          QMessageBox::warning(this,"SmartCode",tr("File not exsists"),QMessageBox::Ok);
          return false;
        }

      TextEdit * editor = newTab(fileName);

      editor->setClassParser(TextEditManager::classParer());
      editor->setText(file.readAll());
      //editor->updateClasses(TextEditManager::classParer()->getOnlyFileIncludes());
      editor->setModified(false);

      file.close();

      return true;
    }
  else{
     setCurrentIndex(toTabIndex(fileName));
     return true;
    }

}

bool TabWidget::save(int index)
{
  QString file = tabInfo.value(currentIndex()).fileName;

  if (QFileInfo(file).exists())
    return saveFile(file);
  else
    return saveAs();
}

bool TabWidget::saveAs()
{

  QString fileName = QFileDialog::getSaveFileName(this,tr("export"), QString()
                                                  ,"SmartCode Project (*.xml *.smc );;CPP source files(*.cpp *.cxx *.cc )"
                                                   ";;CPP header files(*.h *.hh *.hxx *.h++ *.hpp);;"
                                                   "C source files(*.c);;C header files(*.h);;All Files(*.*);;");

  currentTextEdit()->setFileName(fileName);

  //tabInfo.insert(fileName,currentIndex());

  setTabText(currentIndex(),QFileInfo(fileName).fileName());

  return saveFile(fileName);
}

bool TabWidget::saveFile(const QString &fileName)
{

  currentTextEdit()->setModified(false);

  if(Bases::out(fileName, currentTextEdit()->text()))
    return false;

  setFileLastModified(toTabIndex(fileName),QFileInfo(fileName).lastModified());

  return true;
}

bool TabWidget::fileIsOpen(const QString &fileName)
{
  for(int i = 0 ; i < tabBar()->count();i++)
    {
      if(tabFilePath(i) == fileName)
        return true;
    }

  return false;
}

void TabWidget::openFileAt(const QString &fileName,int line,int index)
{
  if(openFile(fileName))
    {
      int pos = currentTextEdit()->positionFromLineIndex(line,index);

      currentTextEdit()->goToPosition(pos);
      currentTextEdit()->setFocus();
    }
}

QString TabWidget::tabFilePath(int index)
{
  return tabFileInfo(index).fileName;
}

int TabWidget::toTabIndex(const QString &fileName)
{
  for(int i = 0; i < count() ; i++)
    {
      if(fileName == tabFilePath(i))
        return i;

    }

  return -1;
}

TabWidget::FileInfo TabWidget::tabFileInfo(int index)
{
  return tabInfo.value(index);
}

void TabWidget::setFileLastModified(int index , const QDateTime &lastModified )
{
  FileInfo fileInfo = tabFileInfo(index);

  fileInfo.lastModified = lastModified;
  tabInfo.insert(index,fileInfo);
}

QDateTime TabWidget::tabFileLastModified(int index)
{
  return tabFileInfo(index).lastModified;
}

QString TabWidget::currentTabFileName()
{
  return  QFileInfo(tabFilePath(currentIndex())).fileName();
}

QString TabWidget::currentTabFilePath()
{
  return tabFilePath(currentIndex());
}

QString TabWidget::currentTabPath()
{
  return QFileInfo(currentTabFilePath()).path();
}

void TabWidget::blame(const QString &fileName)
{

}

void TabWidget::diff(const QString &fileName)
{
  newTab(Bases::baseNamePath(fileName) + ".git");

  currentTextEdit()->setText(versionControl->diff(fileName));
}

void TabWidget::log(const QString &fileName)
{
  newTab(fileName);
  //currentTextEdit()->setText(versionControl->log());
}

void TabWidget::setVersionControl(VersionControl * verControl)
{
  versionControl = verControl;
}



