#ifndef PROJECTTEMPLATE_H
#define PROJECTTEMPLATE_H
#include "project_global.h"

#include <QObject>
#include <QtXml>

class PROJECTSHARED_EXPORT ProjectTemplate : public QObject
{
    Q_OBJECT
public:
    explicit ProjectTemplate(QObject *parent = 0);

    void readTemplate(const QString &templateName);

    QStringList toSourceFiles() const;
    QStringList toWizardPages() const;

    QString toTemplate() const;

    QString path() const  ;

    QString templateType() const ;

    QString pageOption(const QString &page) const;
signals:
    
public slots:
private:

    QString pro;

    QString tmpType,tpl ;

    QStringList pages;

    QHash<QString ,QString> options;

    QStringList files;
};

#endif // TEMPLATE_H
