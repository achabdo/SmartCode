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

#include "lexergit.h"
#include <Qsci/qsciscintilla.h>
#include <QDebug>

using namespace TextEditor;

LexerGit::LexerGit(QObject *parent) :
    QsciLexerCustom(parent)
{

}

QColor LexerGit::defaultColor(int style) const
{
    switch(style)
    {
    case normal:
        return QColor(Qt::black);
    case plus:
        return QColor(Qt::green);
    case minus:
        return QColor(Qt::red);
    case arobaz:
        return QColor(Qt::blue);
    }

    return QsciLexer::defaultColor(style);
}

void LexerGit::styleText(int start, int end)
{
    while(start < end)
    {
        char ch = editor()->SendScintilla(QsciScintilla::SCI_GETCHARAT,start);

        int line = editor()->SendScintilla(QsciScintilla::SCI_LINEFROMPOSITION,start);
        int lineCount = editor()->SendScintilla(QsciScintilla::SCI_LINELENGTH,line);

        switch(ch)
        {
        case '+':
            startStyling(start);
            setStyling(lineCount,plus);

            break;
        case '-':
            startStyling(start);
            setStyling(lineCount,minus);
            break;
        case '@':
            startStyling(start);
            setStyling(lineCount,arobaz);
            break;
        default:
            startStyling(start);
            setStyling(lineCount,normal);

        }
        start += lineCount;
    }
}

const char * LexerGit::language() const
{
    return "Git";
}

QString LexerGit::description(int style) const
{
    switch(style)
    {
    case normal:
        return "normale";
    case plus:
        return "plus";
    case minus:
        return "minus";
    case arobaz:
        return "arobaz";
    }

    return QString();
}
