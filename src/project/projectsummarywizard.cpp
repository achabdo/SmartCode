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

#include "projectsummarywizard.h"
#include "ui_projectsummarywizard.h"

ProjectSummaryWizard::ProjectSummaryWizard(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::ProjectSummaryWizard)
{
    ui->setupUi(this);

    registerField("projects",ui->projects);
}

ProjectSummaryWizard::~ProjectSummaryWizard()
{
    delete ui;
}

void ProjectSummaryWizard::setupProjects(const QStringList & projects , bool templateIsProject)
{
    if(templateIsProject)
        ui->projectLabel->setText(tr("Add to subproject"));
    else
        ui->projectLabel->setText(tr("Add to project"));

    ui->projects->addItems(projects);
}

void ProjectSummaryWizard::selectProject(const QString &project)
{
    for(int i = 0; i <  ui->projects->count(); i++)
    {
        if(ui->projects->itemText(i) == project)
            ui->projects->setCurrentIndex(i);
    }
}
