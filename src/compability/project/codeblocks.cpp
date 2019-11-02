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

#include "codeblocks.h"
#include "core_constants.h"
#include <project.h>
#include <QtXml>

CodeBlocks::CodeBlocks(QObject *parent) :
    QObject(parent)
{
}

void CodeBlocks::import(const QString &cbp)
{
    QHash<QString , QVariant> smcProject;

    QString smcProjectName;
    QFile file(cbp);

    if(!file.open(QFile::ReadOnly))
        return ;

    QDomDocument doc;
    doc.setContent(&file);

    QDomElement root = doc.documentElement();

    QDomElement project = root.firstChildElement("Project");

    QDomElement item = project.firstChild().toElement();

    while(!item.isNull())
    {
        if(item.tagName() == "Option")
        {
            if(!item.attribute("title").isNull())
                smcProjectName = item.attribute("title");
        }

        if(item.tagName() == "Build")
        {
            QDomElement target = item.firstChild().toElement();

            while(!target.isNull())
            {
                target = target.nextSibling().toElement();

                if(item.tagName() == "Option")
                {
                    if(!item.attribute("title").isNull())
                        smcProjectName = item.attribute("title");

                    else if(!item.attribute("object_output").isNull())
                        smcProject.insert(Core::Project::OBJECTSDIR,item.attribute("object_output"));

                }
            }
        }

        item = item.nextSibling().toElement();
    }
}
