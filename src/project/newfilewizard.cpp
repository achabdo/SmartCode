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

#include "newfilewizard.h"
#include "ui_newfilewizard.h"

#include <bases.h>

NewFileWizard::NewFileWizard(FileType _fileType ,const QString &path,QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::NewFileWizard),
    fileType(_fileType)
{
    ui->setupUi(this);


    ui->path->setText(path);

    connect(wizard(),SIGNAL(accepted()),this,SLOT(OnAccept()));
}

NewFileWizard::~NewFileWizard()
{
    delete ui;
}

void NewFileWizard::onAccept()
{
    QString text;

    QString filePath = ui->path->text() + "/" + ui->fileName->text() ;

    if(fileType == SourceFile)
    {
        if(hasNotSuffix(ui->fileName->text()))
        {
            filePath += ".cpp" ;
        }

    }
    else if(fileType == HeaderFile)
    {
        QString headerNameUpper = Bases::baseName(filePath) + "_";

        if(hasNotSuffix(ui->fileName->text()))
        {
            filePath += ".h" ;
            headerNameUpper += "H" ;
        }

        else
        {
            headerNameUpper += Bases::fileSuffix(ui->fileName->text()).toUpper() ;
        }

        text += "#ifndef " + headerNameUpper;
        text += "#define " + headerNameUpper;
        text += "\n";
        text += "#endif // " + headerNameUpper;

    }

    else if(fileType == TextFile)
    {
        if(hasNotSuffix(ui->fileName->text()))
        {
            filePath += ".txt" ;
        }
    }

    else if(fileType == XMLFile)
    {
        if(hasNotSuffix(ui->fileName->text()))
        {
            filePath += ".xml" ;
        }
    }

    Bases::out(filePath , text);
    emit newFileAdded(QStringList() << filePath);
}

bool NewFileWizard::hasNotSuffix(const QString &fileName)
{
    return Bases::fileSuffix(fileName).isEmpty();
}
