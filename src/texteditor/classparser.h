#ifndef CLASSPARSER_H
#define CLASSPARSER_H

#include "texteditor_global.h"

#include  <QObject>
#include  <QIcon>
#include  <QHash>
#include  <QStandardItem>

class TextEditBase;

class TEXTEDITORSHARED_EXPORT ClassParser : public QObject
{
    Q_OBJECT
public:

    enum roleType {IdentifierRole = 1000, ArgumentsRole = 1001,SeperatorRole = 1002,
                   TypeRole = 1003};

    enum AccessType {
        access_public,
        access_protected,
        access_private,

    };

    enum Type {
        method,
        var
    };

    enum IconType
    {
        no_icon,
        icon_namespace,
        icon_class,
        icon_struct,
        icon_union,
        icon_template,
        icon_method_public,
        icon_method_private,
        icon_method_protected,
        icon_var_public,
        icon_var_private,
        icon_var_protected,
        icon_enum,
        icon_enum_public,
        icon_enum_protected,
        icon_enum_private
    };

    explicit ClassParser(QObject * parent = 0);

    QString type(const QStringList &context, int pos, bool addIdentifier = false);
    QString typeBase(const QStringList &context,int pos,bool addIdentifier = false);
    QString toTypeFile() const;

    static QString swapHeaderSource(QString fileName);
    bool isHeaderFile(const QString &file);

    QStringList searchDirs() const;
    QStringList filePaths() const;

    QString findFilePath(const QString &file);
    QString findVarClass(int pos);

    QString correctType(QString &type);

    static QString argument(const QString &text);
    static QString funcName(const QString &text);
    static QString funcType(const QString &text);

    QString regularFunction(const QString &formatedFunc, const QString &className=QString());

    void parseFile(const QString &fileName ,QStandardItem *parent );

    QIcon itemIcon(int type);

    int foundLine() const;
    int foundIndex() const;

    int findMatchingBrace(const QString &text, int pos);

    QStringList itemVals(QStandardItem * item);
    QStringList findTypeItems(const QStringList &context,QStandardItem * item);

    QString findType(const QString &context, QStandardItem *&item);
    bool itemExists(const QStringList &context,QStandardItem * item);
    QStringList findItems(const QStringList &context, QStandardItem *item);

    QStandardItem *  findClassFileItem(const QString &className) const;
    QStringList findFileClasses(const QString &header) const;

signals:


public slots:

    void addSearchDir(const QStringList &dir);
    void setEditor( TextEditBase * editor);

private:

    friend class TextEditManager;

    QStandardItem *findItem(const QString &text, QStandardItem *item);

    QStandardItem * addItem(IconType iconType,const QString &identifier,const QString &type = QString(),
                            const QString &args = QString());

    QStringList SearchDirs;

    QString typeFile;

    TextEditBase * curEditor;
    QStringList fileIncludes;

    QHash<QStandardItem *, QString> fileItemClass;

    bool showType;
    bool showArg;
    bool showArgTypeOnly;

    int fLine;
    int fIndex;

    IconType findIconType(AccessType acType, Type type);
    QStandardItem *findItemRef(const QString &text, QStandardItem *item);

    QStandardItem *topLevelItem;
};
#endif // CLASSPARSER_H
