#include "registres.h"

Registres::Registres(QWidget *parent)
    :DebuggerClient(parent)
{

}

Registres::~Registres()
{

}

void Registres::updateClient(const QString &output)
{
    clear();

    QRegExp outputReg(outputFormat());

    QStringList lines = output.split("\r\n");

    for(int i = 0; i < lines.count() ;i++)
    {

        while( i < lines.count() - 1 && lines[i].endsWith(" "))
        {
            lines[i] += lines[i+1];
            lines.removeAt(i+1);
        }

        outputReg.indexIn(lines[i]);
        QStringList strings = outputReg.capturedTexts();

        strings.removeFirst();

        QTreeWidgetItem * item = new QTreeWidgetItem(strings);
        addTopLevelItem(item);

    }
}

QStringList Registres::headers() const
{
    return QStringList()<<"Registres"<<"Value16";
}

QString Registres::outputFormat() const
{
    return "(\\w+)\\s*([^\\r]+)";
}

QString Registres::cmd() const
{
    return "info all-registers";
}

