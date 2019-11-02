// Copyright (C) 2014  by Achrouf Abdeour <achroufabdenour@gmail.com>
// Auteur Achrouf Abdenour

// This File is part of SmartCode

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program. If not, see http://www.gnu.org/licenses/.

#include "texteditbase.h"
#include "classparser.h"

#include <core_constants.h>
#include <bases.h>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>

static QRegExp funcModel("(\\w+)\\(?([^\\)]*)\\)?\\s(\\w+)");

ClassParser::ClassParser(QObject *parent) :
    QObject(parent)
{

    SearchDirs<<"C:/smart"<<"C:/mingw/include";

}


void ClassParser::addSearchDir(const QStringList &dir)
{
    SearchDirs<<dir;
}

QStringList ClassParser::searchDirs() const
{
    return  SearchDirs;
}

void ClassParser::setEditor(TextEditBase * editor)
{
    curEditor = editor;
}

QStandardItem * ClassParser::findClassFileItem(const QString &className) const
{
    return fileItemClass.key(className);
}

QStringList ClassParser::findFileClasses(const QString &header) const
{
    return QStringList();
}

QString ClassParser::findVarClass(int pos)
{
//    QRegExp classFunc("(\\w+W*)\\s+(\\w+)::(\\w+)\\(([^\\)]*)\\)");

//    if(classFunc.indexIn(curEditor->text(),pos - curEditor->length() -1) != -1)
//        return classFunc.cap(2);

    return QString();
}

int ClassParser::foundLine() const
{
    return fLine;
}

int ClassParser::foundIndex() const
{
    return fIndex;
}

QString ClassParser::findFilePath(const QString &file)
{
    foreach(QString dir,SearchDirs)
    {
        QString filePath = dir + "/" + file;

        if(QFileInfo(filePath).exists())
            return filePath;
    }

    return QString();
}

QString ClassParser::type(const QStringList &context, int pos, bool addIdentifier)
{
return "int";
}

QString ClassParser::toTypeFile() const
{
    return typeFile;
}

QStringList ClassParser::filePaths() const
{
    QStringList files;

    foreach(const QString &dir,searchDirs())
    {
        QDirIterator it(dir,QStringList()<<"*.h" ,QDir::Files,QDirIterator::Subdirectories);
        while (it.hasNext())
            files << QDir(dir).relativeFilePath(it.next());
    }

    return files;
}

QString ClassParser::correctType( QString &type)
{
    type.remove("*");
    type.remove("&");
    return type.trimmed();
}

int ClassParser::findMatchingBrace(const QString &text ,int pos)
{
    int level = 1;

    pos += 1;

    while(pos != text.size())
    {
        if(text.at(pos) == '{')
            level ++;
        if(text.at(pos) == '}')
            level --;

        if(level == 0)
            return pos;

        ++ pos;
    }
    return -1;
}

QStandardItem * ClassParser::addItem(IconType iconType,const QString &identifier,
                                     const QString & type,const QString &args)

{
    QStandardItem * item = new QStandardItem;

    QString text;

    item->setIcon(itemIcon(iconType));

    text += identifier;

    if(!args.isNull())
        text += QString("(%1)").arg(args);

    if(!type.isNull())
    {
        text += " " ;
        text += type;
    }
    else
    {
        switch(iconType)
        {
        case icon_class:
            item->setData("class");
            break;
        case icon_struct:
            item->setData("struct");
            break;
        case icon_union:
            item->setData("union");
            break;
        default:
            break;
        }
    }

    item->setText(text);

    return item;
}

void ClassParser::parseFile(const QString &fileName , QStandardItem * parent)
{


}

ClassParser::IconType ClassParser::findIconType(AccessType acType,Type type)
{
    switch(acType)
    {
    case access_public:
        if(type == method)
        {
            return icon_method_public;
        }
        else if(type == var)
        {
            return icon_var_public;
        }
        break;
    case access_protected:
        if(type == method)
        {
            return icon_method_protected;
        }
        else if(type == var)
        {
            return icon_var_protected;
        }
        break;
    case access_private:
        if(type == method)
        {
            return icon_method_private;
        }
        else if(type == var)
        {
            return icon_var_private;
        }
        break;
    default:
        return no_icon;
    }

    return no_icon;

}

QStandardItem * ClassParser::findItem(const QString &text ,QStandardItem * item)
{
    if( item->text() == text || funcName(item->text()) == text)
        return item;

    for(int row = 0 ; row < item->rowCount() ;++ row)
    {
        return findItem(text,item->child(row));
    }

    return 0;

}

QStandardItem * ClassParser::findItemRef(const QString &text ,QStandardItem *item)
{

    if( item->text() == text || funcName(item->text()) == text)
        return item;

    else
    {
        for (int i = 0; i < item->rowCount(); i++)
        {
            return findItemRef(text,item->child(i));
        }
    }

    return 0;

}

QStringList ClassParser::itemVals(QStandardItem *item)
{
    QStringList vals;

    for(int row = 0 ; row < item->rowCount() ;++ row)
    {
        vals << item->child(row)->text();
    }

    return vals;
}

QStringList ClassParser::findTypeItems(const QStringList &context,QStandardItem * item)
{

    QStandardItem * courantItem = item;

    for(int i = 0; i < context.count(); i++)
    {
        courantItem = findItem(context[i],courantItem);

        if(!courantItem)
            return QStringList();
    }


    return itemVals(courantItem);
}

QString ClassParser::findType(const QString &context , QStandardItem *& item)
{
    QStandardItem * fItem = findItem(context,item);

    if(fItem)
    {
        return funcType(fItem->text());
    }
    else
        return QString();
}

bool ClassParser::itemExists(const QStringList &context,QStandardItem * item)
{

    //definition = context.last()

    QStringList list = findTypeItems(context,item);

    foreach(QString func ,list)
    {
        if(funcName(func) == context.last())
            return true;
    }

    return false;

}

QStringList ClassParser::findItems(const QStringList &context,QStandardItem * item)
{
    QStringList items;

    QStringList list = findTypeItems(context,item);

    foreach(QString func ,list)
    {
        if(funcName(func) == context.last())
            items << func;
    }

    return items;
}

QString ClassParser::funcName(const QString &text)
{
    funcModel.indexIn(text);
    return funcModel.cap(1);
}

QString ClassParser::argument(const QString &text)
{
    funcModel.indexIn(text);
    return funcModel.cap(2);

}

QString ClassParser::funcType(const QString &text)
{
    funcModel.indexIn(text);
    return  funcModel.cap(3);
}

QString ClassParser::regularFunction(const QString &formatedFunc, const QString &className)
{
    QString _type = funcType(formatedFunc);
    QString _funcName = funcName(formatedFunc);
    QString arg = argument(formatedFunc);

    if(className.isNull())
        return _type + " " + _funcName +arg;
    else
        return _type + " " + className + "::" + _funcName +arg;

}

QIcon ClassParser::itemIcon(int type)
{
    switch(type)
    {
    case icon_namespace:
        return QIcon(Core::Icon::NAMESPACE);
        break;
    case icon_class:
        return QIcon(Core::Icon::CLASS);
        break;
    case icon_struct:
        return QIcon(Core::Icon::STRUCTURE);
        break;
    case icon_union:
        return QIcon(Core::Icon::UNION);
        break;
    case icon_template:
        return QIcon(Core::Icon::TEMPLATE);
        break;
    case icon_method_public:
        return QIcon(Core::Icon::METHOD_PUBLIC);
        break;
    case icon_method_protected:
        return QIcon(Core::Icon::METHOD_PROTECETED);
        break;
    case icon_method_private:
        return QIcon(Core::Icon::METHOD_PRIVATE);
        break;

    case icon_var_public:
        return QIcon(Core::Icon::VAR_PUBLIC);
        break;
    case icon_var_protected:
        return QIcon(Core::Icon::VAR_PROTECETED);
        break;
    case icon_var_private:
        return QIcon(Core::Icon::VAR_PRIVATE);
        break;

    case icon_enum:
        return QIcon(Core::Icon::ENUM);
        break;
    case icon_enum_public:
        return QIcon(Core::Icon::ENUM_PUBLIC);
        break;
    case icon_enum_protected:
        return QIcon(Core::Icon::ENUM_PROTECTED);
        break;
    case icon_enum_private:
        return QIcon(Core::Icon::ENUM_PRIVATE);
        break;
    default:
        return QIcon();
    }


}

QString ClassParser::swapHeaderSource(QString fileName)
{
    if(fileName.endsWith(".cpp") || fileName.endsWith(".c"))
    {
        return Bases::baseNamePath(fileName) + ".h";
    }
    else
        return fileName.replace(".h",".cpp");
}

bool ClassParser::isHeaderFile(const QString &file)
{
    return file.endsWith(".h");
}


