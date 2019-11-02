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

#include "recents.h"
#include <QDebug>

Recents::Recents(QObject *parent ) :
    QObject(parent)
{

}

void Recents::setKey(const QString &newKey)
{
    key = newKey;
}

void Recents::remove(const QString &recent)
{
    QSettings settings;

    QStringList recents = settings.value(key).toStringList();
    recents.removeOne(recent);

    settings.setValue(key, recents);
    updateRecentActions();
}

void Recents::set(QMenu * m)
{
    menu = m;

    for (int i = 0; i < MaxRecents; ++i)
    {
        recentActs[i] = new QAction(this);
    }

    for (int i = 0; i < MaxRecents; ++i)
        menu->addAction(recentActs[i]);

    menu->addSeparator();

    clearMenuAct = menu->addAction("Clear Menu",this,SLOT(clear()));

    updateRecentActions();
}

void Recents::setCurrentRecent(const QString &recentName)
{
    curRecent = recentName;

    QSettings settings;

    QStringList recents = settings.value(key).toStringList();

    recents.removeAll(curRecent);
    recents.prepend(curRecent);

    while (recents.size() > MaxRecents)
        recents.removeLast();

    settings.setValue(key, recents);

    updateRecentActions();
}
void Recents::updateRecentActions()
{
    QSettings settings;

    QStringList recents = settings.value(key).toStringList();

    int numRecents = qMin(recents.size(), (int)MaxRecents);

    for (int i = 0; i < numRecents; ++i) {

        recentActs[i]->setText(recents[i]);
        recentActs[i]->setVisible(true);
    }

    for (int j = numRecents; j < MaxRecents; ++j)
        recentActs[j]->setVisible(false);

    clearMenuAct->setVisible(numRecents > 0);
}

void Recents::clear()
{
    QSettings settings;
    settings.remove(key);

    menu->clear();
}
