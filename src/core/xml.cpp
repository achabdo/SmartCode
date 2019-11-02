#include "xml.h"

Xml::Xml(QObject *parent) :
    QObject(parent)
{

}

QDomElement Xml::createDoc(QDomDocument &doc,const QString &rootTagName)
{
    doc.createComment("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>");

    QDomElement root = doc.createElement(rootTagName);
    doc.appendChild(root);

    return root;
}
