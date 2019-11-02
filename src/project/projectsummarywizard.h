#ifndef PROJECTSUMMARYWIZARD_H
#define PROJECTSUMMARYWIZARD_H

#include <QWizardPage>

namespace Ui {
class ProjectSummaryWizard;
}

class ProjectSummaryWizard : public QWizardPage
{
    Q_OBJECT
    
public:
    explicit ProjectSummaryWizard(QWidget *parent = 0);
    ~ProjectSummaryWizard();

    void setupProjects(const QStringList & projects, bool templateIsProject);
    void selectProject(const QString &project);
    
private:
    Ui::ProjectSummaryWizard *ui;
};

#endif // PROJECTSUMMARYWIZARD_H
