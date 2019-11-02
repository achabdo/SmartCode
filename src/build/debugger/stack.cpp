#include "stack.h"

Stack::Stack(QWidget *parent) : DebuggerClient(parent)
{

}

Stack::~Stack()
{

}

QString Stack::cmd() const
{
    return "bt";
}

QStringList Stack::headers() const
{
    return QStringList()<<tr("Level")<<tr("Function")<<tr("File")<<tr("Line");
}

QString Stack::outputFormat() const
{
  return ("#(\\d+)\\s+([^\\t]+)at\\s+(\\S+):(\\d+)");
}

