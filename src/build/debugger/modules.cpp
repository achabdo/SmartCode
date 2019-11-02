#include "modules.h"

Modules::Modules(QWidget *parent) : DebuggerClient(parent)
{

}

Modules::~Modules()
{

}

QStringList Modules::headers() const
{
    return QStringList()<<"Start Address"<<"To"<<"Symbols Read"<<"Module";
}

QString Modules::cmd() const
{
    return "info sharedlibrary";
}

int Modules::linesToBeRemoved() const
{
   return TakeFirstLine;
}

QString Modules::outputFormat() const
{
    return "(\\S+)\\s+(\\S+)\\s+(\\w+)\\s+\\W+\\s+(\\S+)";
}



