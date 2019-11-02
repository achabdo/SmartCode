#include "analyzer.h"
#include "texteditbase.h"
#include "regexp.h"

#include <QDebug>

using namespace Syntaxe;

Analyzer::Analyzer(TextEditBase *edit, QObject *parent) :
    QObject(parent)
{
    editor = edit;
}

QList<int>  Analyzer::errors(const QString &code)
{

    QString str = code;

    QList<int> errors;

    QRegExp keywords("if|else|switch|case|default|break|goto|return|for|while|do|continue|typedef"
                     "sizeof|NULL|new|delete|throw|try|catch|namespace|operator|this|const_cast|static_cast"
                     "dynamic_cast|reinterpret_cast|true|false|using|typeid|and|and_eq|bitand|bitor|compl"
                     "not|not_eq|or|or_eq|xor|xor_eq|void|struct|union|enum|char|short|int|long|double|float"
                     "signed|unsigned|const|static|extern|auto|register|volatile|bool|class|private|protected"
                     "public|friend|inline|template|virtual|asm|explicit|typename|mutable");

    QRegExp usingNamespace("using\\s*namespace\\s*id");
    QRegExp aff("id\\s*\\=\\s*id");
    QRegExp switchReg("switch\\s*\\(\\s*id\\s*\\)");
    QRegExp caseReg("case\\s+id\\s*:\\s*(aff|call)");
    QRegExp incr("id\\s*(\\+\\+|--)");
    QRegExp art("id(\\d+)\\s*(\\|+|-|\\*|/|&&|\\|\\|<|>|\\=\\=|>\\=|<\\=|!\\=)\\s*id(\\d+)");
    QRegExp id("\\w+");
    QRegExp p("\\(\\s*id\\d+\\s*\\)");

    QRegExp call("id\\s*\\((\\s*(id|call)\\s*\\,?)*\\)");
    QRegExp checker("((instr|call)(?!\\s*;)) | [\\+-\\*/\\(\\)\\[\\]]|id");
    QRegExp cond("(if|while)\\s*\\(\\s*id\\s*\\)");
    QRegExp forReg("for\\s*\\((aff|dec)\\s*;\\s*id\\s*;\\s*(aff|incr)\\s*\\)");

    QHash<int,int> idPos;
    QHash<int,QString> idName;
    QHash<int,QString> idType;

    int pos = 0;

    int i = 0;

    str.replace(bigCommentReg,"com");
    str.replace(commentReg,"com");

    while ((pos = varReg.indexIn(str, pos)) != -1) {

        idPos.insert (i,pos);
        idName.insert(i,varReg.cap(IDENTIFIER_CAP));
        idType.insert(i,varReg.cap(TYPE_CAP));

        str.replace(pos,varReg.matchedLength(),QString("dec%1").arg(i));
        i++;

        pos += 3;

        continue;

    }

    pos = 0;

    while ((pos = funcReg.indexIn(str, pos)) != -1) {

        idPos.insert (i,pos);
        idName.insert(i,funcReg.cap(IDENTIFIER_CAP));
        idType.insert(i,funcReg.cap(TYPE_CAP));

        str.replace(pos,funcReg.matchedLength(),QString("decf%1").arg(i));

        i++;

        pos += 4;

        continue;

    }

    pos = 0;

    while ((pos = id.indexIn(str, pos)) != -1) {

        if(!id.cap(0).contains(keywords))
        {
            QString idName("id" + QString::number(i));
            idPos.insert(i,pos);

            str.replace(pos,id.matchedLength(),idName);
            i++;


            pos += idName.size();

            continue;

        }

        pos += id.matchedLength();
    }

    pos = 0;

    while ((pos = art.indexIn(str, pos)) != -1) {

        str.replace(art,QString("id%1").arg(i));

        int leftIdType = art.cap(1).toInt();
        int rightIdType = art.cap(2).toInt();

        idPos.insert(i,idPos.value(leftIdType));

        if(idType.value(leftIdType) == idType.value(rightIdType))
            idType.insert(i,idType.value(leftIdType));
        else
            idType.insert(i,"UNKNOWN");


        str.replace(p,QString("id%1").arg(i));

        ++i;
        pos =0;

    }

    str.replace(cond,"cond");
    str.replace(aff,"aff");

    pos  = 0;

    while ((pos = call.indexIn(str, pos)) != -1) {

        str.replace(call,"call");


        pos =0;

    }

    pos = 0;

    while ((pos = checker.indexIn(str, pos)) != -1) {

        //        qDebug()<< "ERROR AT "<<pos;

        pos += checker.matchedLength();

    }

    return errors;

}

bool Analyzer::checkBrace(int pos)
{
    return (editor->getMatchingBrace(pos) != -1);
}

bool Analyzer::identifierUsed(const QString &identifier,int pos)
{
    int bracePos = editor->findText("{",false,false,pos);

    if(bracePos != -1)
    {
        int matchingBrace = editor->getMatchingBrace(bracePos);

        return editor->findText(identifier,pos,matchingBrace) != -1;
    }
}


