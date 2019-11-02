#include "debuggerclient.h"
#include <QDebug>
DebuggerClient::DebuggerClient(QWidget *parent) : QTreeWidget(parent)
{

}

DebuggerClient::~DebuggerClient()
{

}

QStringList DebuggerClient::headers() const
{
  return QStringList();
}

QString DebuggerClient::cmd() const
{
  return QString();
}

int DebuggerClient::linesToBeRemoved() const
{
  return NoTakeLine;
}

void DebuggerClient::updateClient(const QString &output)
{
  clear();

  int pos = 0;

  QRegExp outputReg(outputFormat());

  while((pos = outputReg.indexIn(output,pos)) != -1 )
    {
      QStringList strings = outputReg.capturedTexts();

      strings.removeFirst();

      QTreeWidgetItem * item = new QTreeWidgetItem(strings);
      addTopLevelItem(item);

      pos += outputReg.matchedLength();
    }


  int takeLines = linesToBeRemoved();

  if (takeLines & TakeFirstLine ) {
      takeTopLevelItem(0);
    }

  if ( takeLines & TakeFirstLine) {
      takeTopLevelItem(topLevelItemCount() - 1);
    }

}

QString DebuggerClient::outputFormat() const
{
  return QString();
}

