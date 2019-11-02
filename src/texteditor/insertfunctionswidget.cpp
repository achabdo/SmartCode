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

#include "insertfunctionswidget.h"
#include "ui_insertfunctionswidget.h"

#include <QListWidgetItem>
#include <QDebug>

#include "classparser.h"

InsertFunctionsWidget::InsertFunctionsWidget(ClassParser *classParser,const QString &fileName ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertFunctionsWidget)
{
    ui->setupUi(this);

    clParser = classParser;
    QString header = clParser->swapHeaderSource(fileName);
    QStringList classes = clParser->findFileClasses(header);

    ui->classes->addItems(classes);
}

InsertFunctionsWidget::~InsertFunctionsWidget()
{
    delete ui;
}

void InsertFunctionsWidget::on_methods_itemActivated(QListWidgetItem *item)
{

}

void InsertFunctionsWidget::on_classes_itemClicked(QListWidgetItem *item)
{
    QString className = item->text();

    QString header = "";/*clParser->findClassHeader(className)*/
    QStringList list ;//= clParser->funcsListFromFile(header,className);

    QListWidgetItem *method;

    foreach(QString function, list)
    {
        method = new QListWidgetItem(clParser->regularFunction(function,className)) ;
        method->setCheckState(Qt::Unchecked);

        ui->methods->addItem(method);
    }

}

void InsertFunctionsWidget::accept()
{
    QStringList methods;

    for(int i=0;i<ui->methods->count();i++)
    {
        QListWidgetItem *item;
        item =  ui->methods->item(i);

        if(item->checkState() == Qt::Checked)
        {
            QString method = item->text();
            methods<<method;
        }
    }

    QDialog::accept();

    emit methodsSelected(methods);
}
