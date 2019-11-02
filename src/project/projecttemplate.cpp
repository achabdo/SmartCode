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

#include "projecttemplate.h"

ProjectTemplate::ProjectTemplate(QObject *parent) :
    QObject(parent)
{


}
void ProjectTemplate::readTemplate(const QString &templateName)
{
    QDomDocument doc;
    QDomElement root;
    QDomElement item;

    QFile f(templateName);

    if(!f.open(QFile::ReadOnly))
        return ;

    doc.setContent(&f);
    f.close();

    root = doc.documentElement();

    tmpType = root.attribute("type");

    item = root.firstChild().toElement();

    while(!item.isNull())
    {
        if (item.tagName() == "wizard")
        {
            QDomElement fileName = item.firstChild().toElement();

            while(!fileName.isNull())
            {

                if (fileName.tagName() == "add")
                {
                    const QString pageName = fileName.attribute("page","error");
                    const QString option = fileName.attribute("option");

                    pages << pageName;

                    if(!option.isEmpty())
                    {
                        options.insert(pageName,option);
                    }
                }

                fileName = fileName.nextSibling().toElement();
            }
        }

        else if(item.tagName() == "src")
        {

            QDomElement fileName=item.firstChild().toElement();
            while(!fileName.isNull())
            {
                if (fileName.tagName() == "file")
                {
                    files<<fileName.attribute("name","error");
                }

                fileName = fileName.nextSibling().toElement();
            }
        }

        else if(item.tagName() == "Template")
            tpl = item.text();

        item = item.nextSibling().toElement();

    }
}

QStringList ProjectTemplate::toSourceFiles() const
{
    return files;
}

QStringList ProjectTemplate::toWizardPages() const
{
    return pages;
}

QString  ProjectTemplate::toTemplate() const
{
    return tpl;
}

QString ProjectTemplate::templateType() const
{
    return tmpType;
}

QString ProjectTemplate::pageOption(const QString &page) const
{
    return options.value(page);
}

