#include "problems.h"

#include <QMenu>
#include <QApplication>
#include <QClipboard>
#include <QTextEdit>

#include "compiler/buildmanager.h"
#include "compiler/compiler.h"
#include "compiler/compilersetting.h"
#include "compiler/message.h"

#define MSG 0
#define LINE 1
#define FILE 2
#define LOGTAB 1

Problems::Problems(BuildManager *buildManager, QWidget *parent) :
  QTreeWidget(parent)
{
  setRootIsDecorated(false);
  setColumnWidth(0, width() * 3/4);

  _buildManager = buildManager;
  compiler = _buildManager->Setting()->compiler();

  QStringList labels;
  labels<<tr("Message")<<tr("Line")<<tr("File");
  setHeaderLabels(labels);

  QFont f = font();
  f.setPointSize(9);
  setFont(f);

  setContextMenuPolicy(Qt::CustomContextMenu);
  setAcceptDrops(true);

  connect(this,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(findErrorLineNumber(QTreeWidgetItem*,int)));
  connect(_buildManager,SIGNAL(newStandardError(QString)),this,SLOT(addError(QString)));
  connect(compiler,SIGNAL(addMessage(Message)),this,SLOT(addItemMessage(Message)));
  connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showMenu()));
}


void Problems::addError(const QString &data)
{
  QStringList errors = data.split("\n");

  foreach(QString error,errors)
    {
      compiler->parse(error);
    }
}

void Problems::addItemMessage(const Message &msg)
{
  if(msg.type == Message::Unknown)
    return;
  QTreeWidgetItem *item = new QTreeWidgetItem(this);

  item->setIcon(0,msg.icon);

  item->setText(0,msg.info);

  if(msg.line != -1)
    item->setText(1,QString::number(msg.line));
  if(!msg.file.isEmpty())
    item->setText(2,msg.file);

}

void Problems::findErrorLineNumber(QTreeWidgetItem*item,int)
{
  QString file = item->text(2);

  if(!file.isEmpty())
    {
      if(item->text(1).isEmpty())
        return;
      int lineNumber = item->text(1).toInt()-1;

      emit openFile(getFileAbsolutePath(file),lineNumber,0);
    }
}

void Problems::showMessage(const QString &text,const QIcon &icon)
{

}

void Problems::showMenu()
{
  QMenu menu;

  if(topLevelItemCount() > 0)
    {
      menu.addAction("&copy",this,SLOT(copy()));
      menu.addAction("show Output",this,SLOT(showOutput()));
    }

  menu.exec(QCursor::pos());
}

void Problems::copy()
{
  QApplication::clipboard()->setText(currentItem()->text(MSG).trimmed());
}

void Problems::showOutput()
{
  QTabWidget *tab = qobject_cast<QTabWidget*>(parentWidget()->parentWidget());

  QTextEdit * edit = qobject_cast<QTextEdit*>(tab->widget(LOGTAB));

  QString text = currentItem()->text(MSG).trimmed();
  if(edit->find(text))
    tab->setCurrentIndex(LOGTAB);

}

QString Problems::getFileAbsolutePath(const QString &fileName) const{
      QFileInfo info(fileName);
      QDir dir(this->_buildManager->getWorkingDir());
      if(info.isAbsolute())
        return fileName;
      else
        return dir.absoluteFilePath(fileName);
}

