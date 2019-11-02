#include "watches.h"

const int sepWidth = 2;

Watches::Watches(QWidget *parent) :
    DebuggerClient(parent)
{

}

QStringList Watches::headers() const
{
    return QStringList()<<"Name"<<"Value"<<"Type";
}

void Watches::updateClient(const QString &output)
{
    clear();

    addVariable(output);

    expandAll();
}

QString Watches::cmd() const
{
    return "info locals";
}

QString Watches::outputFormat() const
{
    return "\\w+";
}

void Watches::addVariable(const QString &code)
{
    QList<QTreeWidgetItem*> parents;

    QTreeWidgetItem *item;

    parents <<invisibleRootItem();

    QRegExp rx(outputFormat());

    int size = code.size();

    int pos = 0;
    int col = 0;

    if(!code.contains("="))
        return;

    while(pos < size)
    {
        QChar ch = code.at(pos);

        if(ch == '=' )
        {
            col++;
        }
        else if( ch == '{')
        {
            if(col > 0)
                col --;

            parents.append(item);
        }
        else if( ch == '}')
        {
            if(col > 0)
                col --;

            parents.pop_back();
        }
        else if( ch == ',')
        {
            if(col > 0)
                col --;
        }

        else if(ch == '\n')
        {
            if(col > 0)
                col--;
        }

        else if(ch == ' ' || ch == '\r')
        {
            pos ++;
            continue;
        }
        else
        {
            if(col == 0)
            {
                item = new QTreeWidgetItem;
                parents.last()->addChild(item);

                rx.indexIn(code,pos);

                item->setText(col,rx.cap(0));

                pos += rx.matchedLength();
            }
            else
            {
                rx.indexIn(code,pos);

                int lastPos = pos;
                pos += rx.matchedLength();

                if(pos < size && code.at(pos)== ' ')
                {
                    int bracePos = pos + 1;
                    int matchingBracePos = findMatchingBrace(code.at(bracePos).toLatin1() ,bracePos,code);

                    if( matchingBracePos != -1)
                    {
                        item->setText(col,code.mid(lastPos,matchingBracePos + 1 - lastPos ));

                        pos = matchingBracePos + 1;
                    }
                }
                else
                    item->setText(col,rx.cap(0));
            }

            continue;

        }

        pos ++;

    }
}

int Watches::findMatchingBrace(const char ch,int pos,const QString &code)
{
    pos += 1;

    int matchingBrace = -1;
    switch(ch)
    {
    case '"':
      while(code.at((pos = code.indexOf('"',pos))- 1 ) == '\\'  )
      {
          pos++;
      }
      matchingBrace = pos;
      break;
    case '<':
        matchingBrace =  code.indexOf('>',pos);
        break;
    }
    return matchingBrace;
}

