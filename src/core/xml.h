#ifndef XML_H
#define XML_H

#include "core_global.h"

#include <QObject>
#include <QDomElement>

class CORESHARED_EXPORT Xml : public QObject
{
    Q_OBJECT
public:
    explicit Xml(QObject *parent = 0);

    QDomElement createDoc(QDomDocument &doc, const QString &rootTagName);
signals:
    
public slots:
    
};


#endif // XML_H
