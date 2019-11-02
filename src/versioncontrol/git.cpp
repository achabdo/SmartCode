#include "git.h"


Git::Git(QObject *parent) :
    VersionControl(parent)
{
}

QString Git::name() const
{
    return "git";
}

QString Git::blameCommand() const
{
    return "blame";
}

QString Git::diffCommand() const
{
    return "diff";
}

QString Git::logCommand() const
{
    return "log";
}

QString Git::addCommand() const
{
    return "add";
}

QString Git::addRepositoryCommand() const
{
    return "init";
}


QString Git::cloneRepositoryCommand() const
{
    return "clone";
}


