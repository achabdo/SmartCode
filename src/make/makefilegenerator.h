#ifndef MAKEFILEGENERATOR_H
#define MAKEFILEGENERATOR_H

#include "make_global.h"

#include <QObject>

class CompilerSetting;
class Project;
class BuildVariables;

class MAKESHARED_EXPORT MakeFileGenerator : public QObject
{
    Q_OBJECT

public:

    explicit MakeFileGenerator(QObject *parent = 0);
    void setSetting(CompilerSetting*s);

    void generateMakeFile();
    void setProject(Project *pro);

    void setGlobalVariables(BuildVariables *globalVariables);

signals:
    
public slots:
private:
    QString language();
    QString insertLib(const QString &lib);
    CompilerSetting * setting;
    Project * project;
    BuildVariables * globalVars;
};

#endif // MAKEFILEGENERATOR_H
