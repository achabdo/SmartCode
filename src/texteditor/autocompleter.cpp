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

#include <Qsci/qscilexer.h>

#include "autocompleter.h"
#include "classparser.h"
#include "texteditbase.h"

#include <QDebug>
#include <QFile>
#include <QDir>
#include <QTimer>

#define ARG_CAP 2
#define RETURNTYPE_CAP 3

AutoCompleter::AutoCompleter(QsciLexer *lexer):
    QsciAbstractAPIs(lexer)
{

}

void AutoCompleter::setClassParser( ClassParser * classParser)
{
    clParser = classParser;
}

QStringList AutoCompleter::callTips(const QStringList &context,int commas,
                                    QsciScintilla::CallTipsStyle style,
                                    QList<int> &shifts)
{
    Q_UNUSED(commas);
    Q_UNUSED(style);
    Q_UNUSED(shifts);

    QStringList args;

//    foreach(QString item ,clParser->findItems(context,0))
//    {
//        args << clParser->argument(item);
//    }

    return args;
}

QString AutoCompleter::autoComplete(char ch,int pos)
{
    TextEditBase *editor = qobject_cast<TextEditBase*>(lexer()->editor());

    if (ch == QLatin1Char('(')  && ! editor->braceCountEqual('(',')'))
        return QLatin1String(")" );
    if (ch ==  QLatin1Char('[')  && !editor->braceCountEqual('[',']'))
        return QLatin1String("]");

    if(ch == QLatin1Char('"'))
        return QLatin1String("\"");
    if(ch == QLatin1Char('\''))
        return QLatin1String("'");

    if(ch == QLatin1Char('{'))
    {
        int curLine,index;

        editor->lineIndexFromPosition(pos,&curLine,&index);
        QString text = editor->text(curLine).trimmed();

        QRegExp cls("^(class|struct)");

        if(text.count()>1)
        {
            if(text.startsWith(QLatin1String("enum")))
                return QLatin1String("};");
            else if(text.contains(cls))
                return QLatin1String("\n};");
            else
                return QLatin1String("}");
        }
        else
        {
            if(editor->text(curLine-1).contains(cls))
                return QLatin1String("\n};");
            else
                return  QLatin1String("\n}");
        }
    }

    return QString();
}

void AutoCompleter::autoCompletionSelected(const QString &sel)
{
    if(QFileInfo(sel).isDir() || QFileInfo(sel).isFile())
    {
        QTimer::singleShot(1,this,SLOT(completeDir()));
    }
    else
    {
        QTimer::singleShot(1,this,SLOT(completeFunction()));
    }
}

void AutoCompleter::completeDir()
{
    TextEditBase *editor = qobject_cast<TextEditBase*>(lexer()->editor());

    editor->cancelList();

    editor->wseps << "/";
    editor->setAutoCompletionWordSeparators(editor->wseps);

    editor->complete(QsciScintilla::AcsAPIs,false);

    editor->wseps.removeOne("/");
    editor->setAutoCompletionWordSeparators(editor->wseps);

}

void AutoCompleter::completeFunction()
{
    TextEditBase *editor = qobject_cast<TextEditBase*>(lexer()->editor());

    QRegExp funcModel("(\\w+)\\s\\(([^\\t]*)\\) : (\\w+)");

    int pos = editor->curPos();

    funcModel.indexIn(editor->acSelection);

    QString arg = funcModel.cap(ARG_CAP).trimmed();

    if(funcModel.cap(RETURNTYPE_CAP) == "void")
    {
        editor->insert("();");

        if(arg.isEmpty())
            editor->goToPosition(pos + 3);
        else
            editor->goToPosition(pos + 1);
    }
    else
    {
        editor->insert("()");

        if(arg.isEmpty())
        {
            editor->goToPosition(pos + 2);
        }
        else
        {
            editor->goToPosition(pos + 1);
            editor->callTip();
        }
    }
}

bool AutoCompleter::load(const QStringList &list)
{
    foreach (const QString entry ,list)
    {
        if(!acList.contains(entry))
            acList <<entry;
    }

    return true;
}

void AutoCompleter::updateAutoCompletionList(const QStringList &context, QStringList &list)
{
    TextEditBase * editor = qobject_cast<TextEditBase*>(lexer()->editor());

    QString _context = context.last();

    int count = context.count();
    int lentgh = _context.length();

    int pos = editor->curPos();

    int line, index;

    editor->lineIndexFromPosition(pos, &line, &index);

    if(count > 1)
    {
        if(editor->text(line).trimmed().startsWith("#include"))
        {
            QDir dir;
            QStringList filters;
            filters<<"*.h";

            QStringList searchDirs = clParser->searchDirs();

            QString compDir = context.join("/");

            foreach(QString searchDir , searchDirs)
            {
                QString checkDir = searchDir + "/" +compDir;

                if(QFileInfo(checkDir).isDir())
                {
                    dir.setCurrent(checkDir);

                    foreach(QString entry,dir.entryList(filters,QDir::Files|QDir::AllDirs|QDir::NoDotAndDotDot))
                    {

                        if(QFileInfo(entry).isDir())
                            entry +="/";

                        if(entry.startsWith(_context,Qt::CaseInsensitive) && entry.length()>lentgh)
                        {
                            list.append(entry);
                        }

                        list<<entry;
                    }

                    break;

                }
            }
        }
        else
        {
            QString type,header;

            QStringList newContext = context;

            if(_context.isEmpty())
                newContext.removeLast();

            if(context[0] == "this")
                type = clParser->findVarClass(line);
            else
                type = clParser->type(newContext ,line,index);

            if(type.isEmpty())
                return;

            if(type.contains(":"))
                type = type.right(type.length() - type.lastIndexOf(":") - 1);

            if(type.contains("*")  && editor->charAt(pos - 1) == '.')
            {
                editor->removeText(line,index-1,1);
                editor->insert("->");
                editor->goToPosition(editor->curPos()+2);
            }

            type = clParser->correctType(type);
//            header = clParser->findClassHeader(type);
            //list = clParser->funcsListFromFile(header,type);
        }

    }

    else
    {
        foreach(QString item , acList)
        {
            if(item.startsWith(_context,Qt::CaseInsensitive) && item.length() > lentgh)
            {
                list.append(item);
            }
        }
    }

}



