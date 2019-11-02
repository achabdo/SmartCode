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

#include "dialog.h"

#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>

Dialog::Dialog(QObject *parent) :
    QObject(parent)
{
}

int Dialog::exec(QWidget * parent ,const QString &title, const QString &msg , QWidget * widget)
{
    QDialog box(parent);

    QGridLayout layout;

    box.setWindowTitle(title);
    box.setLayout(&layout);

    QDialogButtonBox buttonBox;
    buttonBox.setStandardButtons(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);

    connect(&buttonBox, SIGNAL(accepted()), &box, SLOT(accept()));
    connect(&buttonBox, SIGNAL(rejected()), &box, SLOT(reject()));

    QLabel label ;
    label.setText(msg);

    layout.addWidget(&label,0,1);
    layout.addWidget(widget,1,1);
    layout.addWidget(&buttonBox,2,1);

    if(box.exec() != -1)
    {
        widget->setParent(0);

        return box.result();
    }

    return 0;
}

QString Dialog::stringFromMessageBox(QWidget * parent ,const QString &title,const QString &message
                                              ,QString string)
{
    QLineEdit * edit = new QLineEdit;

    if(!string.isNull())
    {

        edit->setText(string);
        int selectionEnd = string.indexOf(".");
        edit->setSelection(0,selectionEnd);

    }

    if(exec(parent,title,message,edit) ==  QDialog::Accepted)
    {
        string =  edit->text();
        delete edit;

        return string;
    }

    delete edit;

    return QString();
}
