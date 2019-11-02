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

#include "advancedsearch.h"
#include "ui_advancedsearch.h"

#include <projectexplorer.h>
#include <tabwidget.h>
#include <project.h>
#include <QFileInfo>

#define COLTEXT 0
#define COLLINE 1
#define COLINDEX 2

AdvancedSearch::AdvancedSearch(ProjectExplorer *projectExplorer,QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::AdvancedSearch)
{
    ui->setupUi(this);

    proExplorer = projectExplorer;

    showSearchDir(ui->findMode->currentIndex());
    connect(ui->findMode,SIGNAL(activated(int)),this,SLOT(showSearchDir(int)));
}

QTreeWidget *AdvancedSearch::findsList() const
{
    return finds;
}

void AdvancedSearch::setFindMode(int index)
{
    ui->findMode->setCurrentIndex(index);
}

AdvancedSearch::~AdvancedSearch()
{
    delete ui;
}


void AdvancedSearch::find(FindMode findMode)
{
    finds = new QTreeWidget;

    findResult = new QLabel(finds);

    finds->setHeaderLabels(QStringList()<<"Text"<<"Line"<<"index");
    finds->setColumnWidth(COLTEXT,finds->width()* 3/4);

    finds->setColumnHidden(COLINDEX,true);
    finds->setHeaderHidden(true);

    connect(finds,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(openFile(QTreeWidgetItem*,int)));
    setWidget(finds);

    QString text = ui->SearchText->currentText();
    QStringList files;

    QString filter = ui->filter->currentText();

    switch(findMode)
    {

    case CurrentFile:
        if(proExplorer->Editor()->count() != 0)
        {
            QDir::setCurrent(proExplorer->Editor()->currentTabPath());
            files.append(proExplorer->Editor()->currentTabFileName());

            findText(text,files);
        }
        break;

    case CurrentProject:
        QDir::setCurrent(proExplorer->currentProject()->path());

        files = proExplorer->currentProjectFiles(filter);
        findText(text,files);
        break;

    case SystemFiles :
        QDir::setCurrent(ui->findDir->currentText());

        files = QDir(ui->findDir->currentText()).entryList().filter(filter);
        findText(text,files);
        break;

    case AllProject:
        foreach(QString projectName,proExplorer->toProjects())
        {
            QDir::setCurrent(QFileInfo(projectName).path());
            files = proExplorer->projectFiles(projectName,filter);
            findText(text,files);
        }

        break;
    }
}

void AdvancedSearch::openFile(QTreeWidgetItem* item,int col)
{ 
    Q_UNUSED(col);

    if(item->childCount() == 0)
    {
        QString fileName = item->parent()->text(COLTEXT);
        proExplorer->Editor()->openFileAt(fileName,item->text(COLLINE).toInt() -1,item->text(COLINDEX).toInt());
    }

}


void AdvancedSearch::findText(QString text ,const QStringList &files)
{
    QTreeWidgetItem *fileItem;
    QTreeWidgetItem *textItem;

    QStringList foundFiles;

    QRegExp expr(text);

    ui->caseSensitive->isChecked() ? expr.setCaseSensitivity(Qt::CaseSensitive) :
                                     expr.setCaseSensitivity(Qt::CaseInsensitive);

    ui->regularExpression->isChecked() ?  expr.setPatternSyntax(QRegExp::RegExp):
                                          expr.setPatternSyntax(QRegExp::FixedString);

    int totalFindsNumber = 0;

    foreach (const QString file, files) {

        int lineNumber = 1;
        int findsNumber = 1;

        QFile f(file);

        if (f.open(QFile::ReadOnly))
        {
            while (!f.atEnd())
            {
                QString line = f.readLine();

                int index = 0;

                while((index = expr.indexIn(line, index)) != -1)
                {
                    int  matchLength = expr.matchedLength();

                    if(ui->wholeWords->isChecked() )
                    {
                        int end = index + matchLength;

                        if (line.at(index - 1).isLetterOrNumber() ||
                                (line.at(end).isLetterOrNumber()))
                        {
                            index += matchLength;
                            continue;
                        }
                    }


                    if(!foundFiles.contains(file))
                    {
                        fileItem = new QTreeWidgetItem(finds);
                        fileItem->setText(COLTEXT,file);
                        foundFiles<<file;
                    }

                    fileItem->setText(COLLINE,QString::number(findsNumber));
                    textItem = new QTreeWidgetItem(fileItem);

                    textItem->setText(COLTEXT,line.trimmed());
                    textItem->setText(COLLINE,QString::number(lineNumber));
                    textItem->setText(COLINDEX,QString::number(index));

                    index += matchLength;

                    findsNumber++;
                    totalFindsNumber += findsNumber;
                }
                lineNumber++;
            }

        }
        f.close();
    }

    findResult->setText(QString("%1 : %2  %3").arg(ui->findMode->currentText())
                        .arg(text)
                        .arg(QString::number(totalFindsNumber)));
}

void AdvancedSearch::on_pushButton_clicked()
{
    FindMode mode = static_cast<FindMode>(ui->findMode->currentIndex());

    find(mode);
}

void AdvancedSearch::on_getDir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this,tr("Select a path"));
    ui->findDir->insertItem(0,dir);
}

void AdvancedSearch::showSearchDir(int index)
{
    if(index == SystemFiles)
        ui->findDirWidget->setVisible(true);
    else
        ui->findDirWidget->setVisible(false);
}

void AdvancedSearch::clearFinds()
{
    setWidget(ui->searchWidget);
    delete finds;
}
