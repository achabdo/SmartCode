#include "threads.h"

Threads::Threads(QWidget *parent)
    :DebuggerClient(parent)
{

}

Threads::~Threads()
{

}

QStringList Threads::headers() const
{
    return QStringList()<<tr("ID")<<tr("TargetID")<<tr("Function")<<tr("File") <<tr("Line");
}

QString Threads::outputFormat() const
{
    return "(\\d+)\\s+Thread\\s+(\\S+)\\s+([^\\t]+)at\\s+(\\S+):(\\d+)";
}

QString Threads::cmd() const
{
    return "info threads";
}


