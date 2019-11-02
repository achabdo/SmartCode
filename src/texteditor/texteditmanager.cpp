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

#include "texteditmanager.h"

#include "analyzer.h"
#include "autocompleter.h"
#include "classparser.h"

#include "lexerstyle.h"

using namespace TextEditor;

static LexerCPP * CPPLexer;
static LexerGit * GitLexer;
static ClassParser * clParser;

TextEditManager::TextEditManager(QObject *parent) :
    QObject(parent)
{
    setupLexers();
}

void TextEditManager::setupLexers()
{
    LexerStyle * lexStyle = new LexerStyle;

    lexStyle->load("style/default");

    CPPLexer = new LexerCPP(lexStyle);

    clParser = new ClassParser;

    AutoCompleter* completer = new AutoCompleter(CPPLexer);
    completer->setClassParser(clParser);

    GitLexer = new LexerGit;
}

LexerCPP * TextEditManager::lexerCPP()
{
    return CPPLexer;
}

LexerGit * TextEditManager::lexerGit()
{
    return GitLexer;
}

ClassParser * TextEditManager::classParer()
{
    return clParser;
}

void TextEditManager::setTopLevelItem(QStandardItem * item)
{
   classParer()->topLevelItem = item;
}

