#ifndef CLASSPARSERITEM_H
#define CLASSPARSERITEM_H

#include  <QStringList>

class ClassParserItem
{
public:
    ClassParserItem(const QStringList &data, ClassParserItem *parent = 0);
    ~ClassParserItem();

    void appendChild(ClassParserItem *child);

    ClassParserItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QString data(int column) const;
    int row() const;
    ClassParserItem *parent();

private:
    QList<ClassParserItem*> childItems;
    QStringList itemData;
    ClassParserItem *parentItem;
};

#endif // CLASSPARSERITEM_H
