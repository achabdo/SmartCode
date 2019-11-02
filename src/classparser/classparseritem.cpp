#include "classparseritem.h"

#include <QStringList>

#include "ClassParserItem.h"

ClassParserItem::ClassParserItem(const QStringList &data, ClassParserItem *parent)
{
    parentItem = parent;
    itemData = data;
}

ClassParserItem::~ClassParserItem()
{
    qDeleteAll(childItems);
}

void ClassParserItem::appendChild(ClassParserItem *item)
{
    childItems.append(item);
}

ClassParserItem *ClassParserItem::child(int row)
{
    return childItems.value(row);
}

int ClassParserItem::childCount() const
{
    return childItems.count();
}

int ClassParserItem::columnCount() const
{
    return itemData.count();
}

QString ClassParserItem::data(int column) const
{
    return itemData.value(column);
}

ClassParserItem *ClassParserItem::parent()
{
    return parentItem;
}

int ClassParserItem::row() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<ClassParserItem*>(this));

    return 0;
}
