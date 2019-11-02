#include "log.h"

Log::Log(QWidget *parent) :
    QTextEdit(parent)
{
    setReadOnly(true);
}

void Log::showMsg(const QString &text,const QColor &color,const QFont &font)
{
    QTextCharFormat format;

    format.setForeground(color);
    format.setFont(font);
    setCurrentCharFormat(format);

    insertPlainText(text+"\n");
}

void Log::showError(const QString &text)
{
    showMsg(text,Qt::darkRed);
}

void Log::showMessage(const QString &text)
{
    showMsg(text);
}

void Log::showInformation(const QString &text)
{
    showMsg(text,Qt::blue);
}


