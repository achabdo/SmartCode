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

#include "classgenerator.h"

#include <QFileDialog>

#include <bases.h>

#include "ui_classgenerator.h"

ClassGenerator::ClassGenerator(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::ClassGenerator)
{

    ui->setupUi(this);
    connect(ui->classname,SIGNAL(textChanged(QString)),this,SLOT(update()));
}

ClassGenerator::~ClassGenerator()
{
    delete ui;
}

void ClassGenerator::setClassPath(const QString &path)
{
    ui->path->setText(path);
}

void ClassGenerator::update()
{

    ui->sourcefile->setText(ui->classname->text().toLower()+".cpp");
    ui->header->setText(ui->classname->text().toLower()+".h");
}

void ClassGenerator::on_toolButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this,"Choose Directory");
    ui->path->setText(path);
}

void ClassGenerator::OnAccept()
{
    QString stext;
    QString htext;
    QString className=ui->classname->text();
    QString classParent=ui->classparent->text();

    QString sourceFile=ui->sourcefile->text();
    QString header=ui->header->text();
    QString path=ui->path->text();
    QString srcFile=path+"/"+sourceFile;
    QString hFile=path+"/"+header;


    QString cName = "class " + className;

    if(!classParent.isEmpty())
    {
        QString parentHeader = classParent.toLower() + ".h";

        htext+="#include \""+ parentHeader+"\"";
        htext+="\n";

        QString parent=" : pubic "+classParent;
        htext+=cName+parent;
    }
    else
        htext+=cName;

    htext+="\n{\n";
    htext+="public:\n";
    htext+=className+"();\n";
    htext+="private:\n";
    htext+=  "};";

    stext+="#include \"";
    stext+=header+"\"";
    stext+="\n";
    stext+=className+"::"+ className+"()";
    stext+="\n";
    stext+="{\n}\n";
    //export the texts

    Bases::out(srcFile,stext);
    Bases::out(hFile,htext);

    newClass(QStringList() << srcFile << hFile);
}

bool ClassGenerator::classNameIsValid()
{
    return !ui->classname->text().isEmpty()&&
            !ui->classname->text().contains(" ") &&
            !ui->header->text().isEmpty()&&
            !ui->header->text().contains(" ")&&
            !ui->sourcefile->text().isEmpty()
            && ! ui->sourcefile->text().contains(" ") && QFileInfo(ui->path->text()).exists();

}

bool ClassGenerator::validatePage()
{
    return classNameIsValid();
}
