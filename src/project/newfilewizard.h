#ifndef NEWFILEWIZARD_H
#define NEWFILEWIZARD_H

#include <QWizardPage>

namespace Ui {
class NewFileWizard;
}

class NewFileWizard : public QWizardPage
{
    Q_OBJECT
    
public:
    enum FileType {SourceFile ,HeaderFile,TextFile,XMLFile};
    explicit NewFileWizard(FileType fileType , const QString &path
                           , QWidget *parent  = 0);
    ~NewFileWizard();
    
signals:
    void newFileAdded(const QStringList &fileName);
public slots:
    void onAccept();

private:
    Ui::NewFileWizard * ui;

    bool hasNotSuffix(const QString &fileName);

    FileType fileType;
};

#endif // NEWFILEWIZARD_H
