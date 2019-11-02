#ifndef CLASSPARSERMODEL_H
#define CLASSPARSERMODEL_H

#include "classparser_global.h"
#include <QAbstractItemModel>

class ClassParserItem;

class CLASSPARSERSHARED_EXPORT ClassParserModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit ClassParserModel(QObject *parent = 0);
public:
    ClassParserModel(const QString &data, QObject *parent = 0);
    ~ClassParserModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

private:
    void setupModelData(const QStringList &data, ClassParserItem *parent);

    ClassParserItem *rootItem;
signals:
    
public slots:
    
};

#endif // CLASSPARSERMODEL_H
