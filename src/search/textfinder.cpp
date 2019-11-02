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

#include "textfinder.h"
#include "ui_textfinder.h"

#include "advancedsearch.h"

#include <tabwidget.h>
#include <textedit.h>

#include <QLineEdit>

TextFinder::TextFinder(TabWidget * myEditor,QWidget *parent) :
    QDockWidget(parent)
  ,ui(new Ui::TextFinder)
{
    ui->setupUi(this);

    editor = myEditor;
    setup();

    ui->findEdit->setClearButtonEnabled(true);
    ui->replaceEdit->setClearButtonEnabled(true);

    connect(ui->AdvancedSearch,SIGNAL(clicked()),this,SIGNAL(advandeSearch()));
}

void TextFinder::setup()
{
    QAction * actFind = ui->findEdit->addAction(QIcon(":/images/Find.png"), QLineEdit::LeadingPosition);
    connect(actFind,SIGNAL(triggered()),this,SLOT(showFindOptionMenu()));

}

void TextFinder::showFindOptionMenu()
{
    QSettings settings;

    QMenu menu;

    QAction * whole,*sen,*reg;

    whole = new QAction("Whole Words",this);
    sen = new QAction("Case Sensitive",this);
    reg = new QAction("Regular Expression",this);


    sen->setCheckable(true);
    whole->setCheckable(true);
    reg->setCheckable(true);

    caseSensitive = settings.value("Find/sen").toBool();
    wholeWords = settings.value("Find/whole").toBool();
    regularExp = settings.value("Find/reg").toBool();

    sen->setChecked(caseSensitive);
    whole->setChecked(wholeWords);
    reg->setChecked(regularExp);

    connect(sen,SIGNAL(toggled(bool)),this,SLOT(setCaseSensitive(bool)));
    connect(whole,SIGNAL(toggled(bool)),this,SLOT(setwholeWords(bool)));
    connect(reg,SIGNAL(toggled(bool)),this,SLOT(setRegularExp(bool)));

    menu.addAction(whole);
    menu.addAction(sen);
    menu.addAction(reg);

    QPoint point;
    point = QWidget::mapToGlobal(ui->findEdit->pos());

    point.setY(point.y() + ui->findEdit->height() - menu.sizeHint().height() - 1);
    menu.exec(point);
}

void TextFinder::setCaseSensitive(bool _caseSensitive)
{
    QSettings settings;
    settings.setValue("Find/sen",_caseSensitive);

    caseSensitive= _caseSensitive;
}

void TextFinder::setwholeWords(bool _wholeWords)
{
    QSettings settings;

    settings.setValue("Find/whole",_wholeWords);
    wholeWords= _wholeWords;
}

void TextFinder::setRegularExp(bool _regularExp)
{
    QSettings settings;

    settings.setValue("Find/reg",_regularExp);
    regularExp = _regularExp;
}

TextFinder::~TextFinder()
{
    delete ui;
}

void TextFinder::Find(bool forward,int line)
{
    QSettings settings;

    QStringList recent  = settings.value("RecentFinds").toStringList();
    recent.prepend(ui->findEdit->text());

    while (recent.size() > 10)
        recent.removeLast();

    settings.setValue("RecentFinds",recent);

    editor->currentTextEdit()->findFirst(ui->findEdit->text(),regularExp,caseSensitive,wholeWords,false,forward,line);

}

void TextFinder::getRecentFinds()
{
    QSettings settings;
    QStringList recentList= settings.value("RecentFinds").toStringList();
    //    ui->findEdit->insertItems(1,recentList);
}

void TextFinder::on_next_clicked()
{
    Find(true);
}

void TextFinder::on_prev_clicked()
{
    Find(false);
    editor->currentTextEdit()->findNext();
}

void TextFinder::on_ReplaceAll_clicked()
{
    int line = editor->currentTextEdit()->firstVisibleLine();

    while(line < editor->currentTextEdit()->lines())
    {
        Find(true,line);
        editor->currentTextEdit()->replace(ui->replaceEdit->text());
        line = line + 1;
    }
}

void TextFinder::on_Replace_clicked()
{
    editor->currentTextEdit()->replace(ui->replaceEdit->text());
}
