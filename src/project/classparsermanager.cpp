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

#include "classparsermanager.h"

#include <QDir>
#include <QDirIterator>
#include <core_constants.h>
#include <bases.h>
#include <QDebug>
#include <QDomElement>

#include <classparser.h>
#include <projectexplorer.h>

ClassParserManager::ClassParserManager(ProjectExplorer * explorer ,QObject *parent) :
    QObject(parent)

{
    pExplorer = explorer;
}

void ClassParserManager::setClassParser(ClassParser * parser)
{
    classParserModel = parser;

    connect(pExplorer,SIGNAL(projectAdded()),this,SLOT(load()));
//    connect(pExplorer,SIGNAL(projectClosed()),this,SLOT(save()));

    connect(pExplorer,SIGNAL(fileAdded(QString)),this,SLOT(setupClassModel(QString)));
}

void ClassParserManager::parse()
{
    const QString path = "C:/smart";

    QStringList files;

    QDirIterator it(path,QStringList() << "*.h",QDir::Files |QDir::AllDirs|QDir::NoDotAndDotDot
                    , QDirIterator::Subdirectories);

    while(it.hasNext())
    {
        files<< it.next();
    }

    //    QStandardItem * incs , *item;

    //    incs = new QStandardItem;

    //    item = new QStandardItem(path);

    //    incs->setText("Includes");
    //    incs->appendRow(item);

    //    pExplorer->h.insert(incs,"C:/smart/includes");
    //    pExplorer->fileName.insert(incs,"C:/smart/includes");

    //    pExplorer->h.insert(item,"C:/smart/includes/"+ path);
    //    pExplorer->fileName.insert(item,path);

    //    pExplorer->fileName.key("C:/smart/smart.smc")->appendRow(incs);

    //    pExplorer->printFiles("C:/smart/includes",files,path);

    //    qDebug() <<  pExplorer->fileName.values();

    //    pExplorer->addParentItem(pExplorer->currentProjectName(),Core::Project::ProjectIncludes,files);

    //    foreach(QString file ,files)
    //    {
    //        if(QFileInfo(file).isFile())
    //            classParserModel->parseFile(file,pExplorer->fileName.key(file));
    //    }
}

void ClassParserManager::setupClassModel(const QString &fileName)
{
    const QString fileType = pExplorer->fileType(fileName);

    if( fileType == Core::Project::SOURCES || fileType == Core::Project::HEADERS)
        classParserModel->parseFile(fileName,pExplorer->fileNameItem(fileName));

}

void ClassParserManager::updateClassModel(const QString &var)
{
    //    QString fileName = editor->currentTabFilePath();

    //    if(fileType(fileName) == Core::Project::HEADERS)
    //        fileName = ClassParser::swapHeaderSource(fileName);

    //    QStandardItem * p = this->fileName.key(fileName);

    //    //    if(p)
    //    //        classParserModel->addItem(var,p);

}

void ClassParserManager::load()
{
    QFile file("D:/smart/ess.xml");

    if(!file.open(QFile::ReadOnly))
        return ;

    doc.setContent(&file);
    file.close();

    QDomElement root;

    root = doc.documentElement();

    QStandardItem * parentItem = pExplorer->addParentItem
            (pExplorer->currentProjectName(),Core::Project::ProjectIncludes,QStringList(),true);

    parItem(root,parentItem);
}

void ClassParserManager::parItem(QDomElement xmlParent,QStandardItem * item)
{
    QDomElement xmlItem = xmlParent.firstChild().toElement();

    while(!xmlItem.isNull())
    {
        QStandardItem * newItem = new QStandardItem(xmlItem.attribute("name"));
        item->appendRow(newItem);

        parItem(xmlItem,newItem);
        xmlItem = xmlItem.nextSibling().toElement();
    }
}


void ClassParserManager::save()
{
    doc.clear();

    QDomElement root = doc.createElement(Core::Project::ProjectIncludes);
    doc.appendChild(root);

    parItemSave(root,pExplorer->fileNameItem(pExplorer->currentProjectFilter(Core::Project::ProjectIncludes)));

    Bases::out("D:/smart/mac.xml",doc.toString());
}

void ClassParserManager::parItemSave(QDomElement xmlParent, QStandardItem *item)
{
    QDomElement xmlItem = doc.createElement(item->text());
    xmlParent.appendChild(xmlItem);

    for(int row = 0 ; row < item->rowCount() ;++ row)
    {
        parItemSave(xmlItem,item->child(row));
    }
}

