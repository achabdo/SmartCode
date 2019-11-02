#ifndef CLASSPARSERMANAGER_H
#define CLASSPARSERMANAGER_H

#include "project_global.h"

#include <QObject>
#include <QDomDocument>

class ClassParser;
class ProjectExplorer;
class QStandardItem;
class QDomElement;

class PROJECTSHARED_EXPORT  ClassParserManager : public QObject
{
    Q_OBJECT
public:
    explicit ClassParserManager(ProjectExplorer * explorer ,QObject *parent = 0);
    
    void setClassParser(ClassParser *parser);



signals:

public slots:
    void load();
      void save();
    void setupClassModel(const QString &fileName);
    void updateClassModel(const QString &var);

    void parse();
private:
    ClassParser * classParserModel;
    ProjectExplorer * pExplorer;
    void parItem(QDomElement xmlParent, QStandardItem *item);
    void parItemSave(QDomElement xmlParent, QStandardItem *item);

    QDomDocument doc;
};

#endif // CLASSPARSERMANAGER_H
