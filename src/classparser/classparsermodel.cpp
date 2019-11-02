#include "classparsermodel.h"
#include "classparseritem.h"

ClassParserModel::ClassParserModel(const QString &data, QObject *parent)
    : QAbstractItemModel(parent)
{
    rootItem = new ClassParserItem(rootData);
    setupModelData(data.split(QString("\n")), rootItem);
}

ClassParserModel::~ClassParserModel()
{
    delete rootItem;
}

int ClassParserModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<ClassParserItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

QVariant ClassParserModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    ClassParserItem *item = static_cast<ClassParserItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags ClassParserModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant ClassParserModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex ClassParserModel::index(int row, int column, const QModelIndex &parent)
const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    ClassParserItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<ClassParserItem*>(parent.internalPointer());

    ClassParserItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex ClassParserModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    ClassParserItem *childItem = static_cast<ClassParserItem*>(index.internalPointer());
    ClassParserItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int ClassParserModel::rowCount(const QModelIndex &parent) const
{
    ClassParserItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<ClassParserItem*>(parent.internalPointer());

    return parentItem->childCount();
}

void ClassParserModel::setupModelData(const QStringList &data, ClassParserItem *parent)
{

}
