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

#include "synhighoptions.h"
#include "ui_synhighoptions.h"

#include <QDebug>
#include <QSettings>
#include <QDir>

#include "lexerstyle.h"

const char saveDir[] =  "style/" ;

SynHighOptions::SynHighOptions(LexerStyle * lexerStyle,QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SynHighOptions),
  lexStyle(lexerStyle)
{

  ui->setupUi(this);

  //setup();
}

SynHighOptions::~SynHighOptions()
{
  delete ui;
}
void SynHighOptions::setup()
{
  QSettings settings;
  QString currentStyle = settings.value("Style").toString();

  currentStyle = "default";

  QDir dir("style","*.style");

  QStringList styles ;

  foreach(QString style , dir.entryList())
    {
      QString styleBase = QFileInfo(style).baseName();
      styles.append(styleBase);
    }

  ui->styleName->addItems(styles);

  int index = 0;

  while(ui->styleName->itemText(index) != currentStyle)
    {
      index +=1;
    }

  ui->styleName->setCurrentIndex(index);

  for(int sty = 0;sty <= 24;sty++)
    {
      ui->style->addItem(lexStyle->styleName(sty));

      fgColors.append(lexStyle->foregroundColor(sty));
      bgColors.append(lexStyle->backgroundColor(sty));

      //qDebug()<<lexStyle->foregroundColor(sty);
      fonts.append(lexStyle->font(sty));

    }

  QFont f = lexStyle->font(0);

  ui->fontBox->setCurrentFont(f);
  setFontSizeValue(f.pointSize());

}

void SynHighOptions::on_forg_clicked()
{
  fgColors.replace(currentStyle(),selectColor(ui->forg));
}


void SynHighOptions::on_back_clicked()
{
  bgColors.replace(currentStyle(), selectColor(ui->back));
}

QColor SynHighOptions::selectColor(QPushButton *button,const QColor &c)
{
  if (c.isValid())
    {
      button->setPalette(QPalette(c));
    }

  return c;
}

void SynHighOptions::userAccept()
{
  QString styleName = saveDir + ui->styleName->currentText() ;

  lexStyle->save(styleName,ui->fontBox->currentText(),ui->fontSize->currentText().toInt(),
                 fgColors ,bgColors,fonts);

}

void SynHighOptions::on_style_clicked(const QModelIndex &index)
{
  int style = index.row();

  selectColor(ui->forg,fgColors.value(style));
  selectColor(ui->back,bgColors.value(style));

  QFont f = fonts[style];
  checkFont(f.bold(),f.italic(),f.underline());
}

void SynHighOptions::setFontSizeValue(int fontSize)
{
  int index = 0;

  while(ui->fontSize->itemText(index).toInt() !=  fontSize)
    {
      index +=1;
    }

  ui->fontSize->setCurrentIndex(index);
}

void SynHighOptions::checkFont(bool bold,bool italic,bool underline)
{
  ui->bold->setChecked(bold);
  ui->italic->setChecked(italic);
  ui->underline->setChecked(underline);
}

void SynHighOptions::on_bold_clicked(bool checked)
{
  updateFont(checked);
}

void SynHighOptions::on_italic_clicked(bool checked)
{
  updateFont(-1,checked);
}

void SynHighOptions::on_underline_clicked(bool checked)
{
  updateFont(-1,-1,checked);
}

int SynHighOptions::currentStyle()
{
  return ui->style->currentRow();
}

void SynHighOptions::updateFont(int bold ,int italic,int underLine)
{
  int style = currentStyle();

  QFont font = fonts[style];

  if(bold!=-1)
    font.setBold(bold);

  if(italic!=-1)
    font.setItalic(italic);

  if(underLine!=-1)
    font.setUnderline(underLine);

  fonts.replace(style,font);
}



