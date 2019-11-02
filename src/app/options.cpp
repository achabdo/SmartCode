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

#include "options.h"
#include "ui_options.h"

#include  <QDebug>
#include  <QSettings>
#include  <QFileDialog>

#include <synhighoptions.h>
#include <lexerstyle.h>
#include <texteditmanager.h>
#include <compiler/compileroptionswidget.h>
#include <compiler/compilersettingwidget.h>
#include <compiler/compilersetting.h>
#include <texteditbase.h>
#include <Qsci/qscilexercpp.h>
#include <QFormLayout>
#include <compiler/compiler.h>

const int GENERAL = 0 ;
const int ENVIRONEMENT = 1;
const int EDITOR=  2;
const int BUILD = 3;
const int COMPILER = 4;
const int Debugger = 5;
const int VERSIONCONTROL = 6;

Options::Options(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Options)
{
  ui->setupUi(this);

  connect(ui->local,SIGNAL(activated(int)),this,SLOT(setLocal(int)));

  QSettings settings;

  QRegExp styleReg("\\d+");

  styleReg.indexIn(settings.value("FormatOptions").toString());

  ui->formatStyleBox->setCurrentIndex(styleReg.cap(0).toInt() - 1);

  connect(ui->formatStyleBox,SIGNAL(activated(int)),this,SLOT(setFormatSourceStyle(int)));

  setup();
}

void Options::setup()
{
  QSettings setting;
  ui->local->setCurrentIndex(setting.value("localBoxIndex").toInt());

  SynHighOptions * synHighOptions = new SynHighOptions(TextEditManager::lexerCPP()->style());
  ui->editorTabWidget->insertTab(1,synHighOptions,"Font & Colors");

  QFormLayout * layout = qobject_cast<QFormLayout*>(ui->SourceFormatterTab->layout());
  textEdit = new TextEditBase;
  textEdit->setMarginOptions(TextEditBase::MoNone);

  textEdit->setText("int Foo(bool isBar) {\n"
                    "if (isBar) {\n"
                    "bar();\n"
                    "return 1;\n"
                    "} else\n"
                    "return 0;\n}");

  textEdit->setLexer(new QsciLexerCPP);
  layout->addRow(textEdit);
}

void Options::setupCompilerSetting(CompilerSetting * cSetting)
{
  QHBoxLayout * layout = new QHBoxLayout;

  CompilerSettingWidget *compilerSettingWidget = new CompilerSettingWidget(cSetting);

  CompilerOptionsWidget * cow = new CompilerOptionsWidget(this);

  cow->setCompilerOptionsCategories(cSetting->compiler()->flags());
  compilerSettingWidget->setupCompilerOptions(cow);

  connect(this,SIGNAL(accepted()),compilerSettingWidget,SLOT(saveSetting()));

  layout->addWidget(compilerSettingWidget);
  ui->compilerPage->setLayout(layout);
}

Options::~Options()
{
  delete ui;
}
void Options::on_listWidget_clicked(const QModelIndex &index)
{
  ui->stackedWidget->setCurrentIndex(index.row());
}

void Options::setLocal(int index)
{
  QString setting;

  switch(index)
    {
    case 0:
      setting = "en";
      break;
    case 1:
      setting = "fr";
      break;
    }

  options.insert("local",setting);
  options.insert("localBoxIndex",index);
}

void Options::accept()
{
  QSettings setting;

  foreach(QString option, options.keys())
    {
      setting.setValue(option,options.value(option));
    }

  QDialog::accept();
}

void Options::setFormatSourceStyle(int style)
{
  QString options = QString("A%1tO").arg(style + 1);
  textEdit->formatSourceCode(options.toLatin1().constData());

  QSettings settings;
  settings.setValue("FormatOptions",options);
}

void Options::on_toolButton_clicked()
{
  QString dir = QFileDialog::getExistingDirectory(this,tr("Select directory"));

  ui->ProjectsDir->setText(dir);
}
