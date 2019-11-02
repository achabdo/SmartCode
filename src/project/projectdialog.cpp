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

#include "projectdialog.h"
#include "ui_projectdialog.h"

#include <QLabel>

const char pro[] = "core/project/";
const char file[] = "core/files/";

ProjectDialog::ProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectDialog)
{
    ui->setupUi(this);

    QDir::setCurrent(QApplication::applicationDirPath());
}

QString ProjectDialog::newType()
{
    QDir d(pro);

    d.setFilter(QDir::Dirs|QDir::NoDotAndDotDot);

    if(d.entryList().contains(ui->listWidget->currentItem()->text()))
        return pro;
    else
        return file;
}

void ProjectDialog::setItems(NewType newType)
{
    QDir dir;

    dir.setFilter(QDir::Dirs|QDir::NoDotAndDotDot);

    QLabel * text  = new QLabel("Projects");
    QLabel * files = new QLabel("Files");

    if(newType == NewProject || newType == AllTypes)
    {
        dir.setPath(pro);

        ui->listWidget->setItemWidget(new QListWidgetItem(ui->listWidget),text);
        ui->listWidget->addItems(dir.entryList());
    }

    if(newType == NewFile || newType == AllTypes)
    {
        dir.setPath(file);

        ui->listWidget->setItemWidget(new QListWidgetItem(ui->listWidget),files);
        ui->listWidget->addItems(dir.entryList());
    }
}

ProjectDialog::~ProjectDialog()
{
    delete ui;
}

void ProjectDialog::on_listWidget_clicked(const QModelIndex &index)
{

}

void ProjectDialog::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QDir dir;

    dir.setPath(newType() + item->text());

    if(item->text().isNull())
        return;

    dir.setFilter(QDir::Dirs|QDir::NoDotAndDotDot);
    ui->listWidget_2->clear();

    foreach(QString entry,dir.entryList())
    {
        item=new QListWidgetItem;
        item->setText(entry);
        item->setIcon(QIcon(dir.absoluteFilePath(entry) + "/" + entry + ".png"));

        ui->listWidget_2->addItem(item);
    }
}

void ProjectDialog::on_listWidget_2_itemClicked(QListWidgetItem *item)
{
    QFile file(newType()+ui->listWidget->currentItem()->text()+"/"+item->text()+"/"+"info.txt");

    if(!file.open(QFile::ReadOnly))
        return;

    ui->textEdit->setText(file.readAll());
}

void ProjectDialog::accept()
{
    QString projectType = ui->listWidget->currentItem()->text();
    QString model  = ui->listWidget_2->currentItem()->text();
    QString path   = newType() + projectType + "/" + model;

    QString tmp = path+ "/" + model + ".tpl";

    QDialog::accept();

    emit templateSelected(tmp);

}

void ProjectDialog::on_listWidget_2_itemDoubleClicked(QListWidgetItem *item)
{
    Q_UNUSED(item);

    accept();
}
