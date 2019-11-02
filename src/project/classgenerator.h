#ifndef CLASSGENERATOR_H
#define CLASSGENERATOR_H

#include "project_global.h"

#include <QWizardPage>

namespace Ui {
class  ClassGenerator;
}

class PROJECTSHARED_EXPORT ClassGenerator : public QWizardPage
{
    Q_OBJECT
    
public:

    explicit ClassGenerator(QWidget *parent = 0);
    ~ClassGenerator();
    bool validatePage();
    void setClassPath(const QString &path);

signals:
    void newClass(const QStringList &files);

private slots:
    void update();
    void on_toolButton_clicked();
public slots:
    void OnAccept();
private:

    bool classNameIsValid();
    Ui::ClassGenerator *ui;
};

#endif // CLASSGENERATOR_H
