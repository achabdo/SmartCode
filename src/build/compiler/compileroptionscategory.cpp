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

#include <QList>

#include "compileroptionscategory.h"
#include "compileroption.h"

CompilerOptionsCategory::CompilerOptionsCategory(const QString &name, QObject *parent)
 :QObject(parent)
{
_name = name;
}


void CompilerOptionsCategory::addCompilerOption(CompilerOption *option)
{
    compilerOptions << option;
}

QList<CompilerOption*> CompilerOptionsCategory::toCompilerOptions()
{
    return compilerOptions;
}

QString CompilerOptionsCategory::name() const
{
    return _name;
}


