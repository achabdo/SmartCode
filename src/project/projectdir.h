#ifndef PROJECTDIR_H
#define PROJECTDIR_H
#include "project_global.h"

#include <QWizardPage>

namespace Ui {
class ProjectDir;
}

class PROJECTSHARED_EXPORT ProjectDir : public QWizardPage
{
    Q_OBJECT
    
public:
    enum Message{error,warning};
    explicit ProjectDir(QWidget *parent = 0);

    ~ProjectDir();
    void showError(const QString &text, Message msgType);
    void hideError();
    void setProjectDir(const QString &dir);

private:
    Ui::ProjectDir *ui;
    bool projectAlreadyExsits(const QString &dir, const QString &projectName);
public slots:
void checkProjectDir(const QString &projectName);
void hasError(const QString &dir);
private slots:
    void on_pushButton_clicked();
};

#endif // PROJECTDIR_H
