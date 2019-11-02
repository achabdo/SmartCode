#ifndef PROJECTWIZARD_H
#define PROJECTWIZARD_H

#include "project_global.h"

#include <QWizard>

class ProjectTemplate;
class Project;
class ProjectDir;
class ConfigWizard;
class Wizard;
class ProjectExplorer;

class PROJECTSHARED_EXPORT ProjectWizard : public QWizard
{
    Q_OBJECT
public:
    explicit ProjectWizard(ProjectExplorer *projectManager, QWidget *parent  = 0);

    QString projectPath();

signals:
    
public slots:
     void addProject();
    void setTemplate(const QString &templat);

private:

    ProjectTemplate * projectTemplate;
    ProjectExplorer * projectExplorer;

    QString templateDir ;
    QStringList projects;
};


#endif // PROJECTWIZARD_H
