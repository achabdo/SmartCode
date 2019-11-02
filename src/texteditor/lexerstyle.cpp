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

#include "lexerstyle.h"

#include "lexerstyle.h"

#include <QFile>
#include <QVariant>
#include <QDebug>

#include <Qsci/qscilexercpp.h>

#include "bases.h"

LexerStyle::LexerStyle(QObject *parent) :
    QObject(parent)
{

}

void LexerStyle::load(const QString &fileName)
{
    QFont font;
    bool bold,italic,underLine;

    int styleNum;

    QFile file(fileName + ".style");

    if(!file.open(QFile::ReadOnly))
        return;

    QDomDocument doc ;
    doc.setContent(&file);

    file.close();

    QDomElement root = doc.documentElement();
    QDomElement style = root.firstChild().toElement();

    font.setFamily(root.attribute("font"));
    font.setPointSize(root.attribute("size").toInt());

    font.setStyleStrategy(QFont::PreferAntialias);

    while(!style.isNull())
    {
        QDomElement option = style.firstChild().toElement();

        while(!option.isNull())
        {
            if (option.tagName() == "Foreground_color")
            {
                foregColors.append(readColor(option));


            }
            else if (option.tagName() == "Background_color")
            {
                 backgColors.append(readColor(option));

            }
            else if (option.tagName() == "Font")
            {
                bold = QVariant(option.attribute("bold")).toBool();
                italic = QVariant(option.attribute("italic")).toBool();
                underLine = QVariant(option.attribute("underline")).toBool();

                font.setBold(bold);
                font.setItalic(italic);
                font.setUnderline(underLine);

                styleNum = foregColors.count() - 1;

//                 if(styleNum == QsciLexerCPP::Keyword || QsciLexerCPP::GlobalClass)
//                   font.setWeight(57);

                fonts.append(font);

            }

            option = option.nextSibling().toElement();
        }
         //qDebug()<<style.tagName();

        style = style.nextSibling().toElement();
    }
}


QColor LexerStyle::backgroundColor(int style)
{
    return backgColors.value(style);
}

QColor LexerStyle::foregroundColor(int style)
{
    return foregColors.value(style);
}

QFont LexerStyle::font(int style)
{
    return fonts.value(style);
}

void LexerStyle::save(const QString &styleName,const QString &fontName,int fontSize,
                      QList<QColor> foregroundColors,QList<QColor> backgroundColors, QList<QFont> Fonts)
{

    QDomDocument doc;
    doc.createComment("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>");

    QDomElement root = doc.createElement("Lexer");

    root.setAttribute("font",fontName);
    root.setAttribute("size",fontSize);

    doc.appendChild(root);

    QDomElement style,option;

    for(int styleNum = 0 ; styleNum <= MAXSTYLE ; styleNum++)
    {
      QString styleDescription = this->styleName(styleNum).replace(" ","");
      style = doc.createElement(styleDescription);
      root.appendChild(style);

      QColor color;

      color = foregroundColors[styleNum];
      option = doc.createElement("Foreground_color");
      addColor(option,color);

      style.appendChild(option);

      emit foregroundColorChanged(color,styleNum);

      color = backgroundColors[styleNum];
      option = doc.createElement("Background_color");
      addColor(option,color);

      style.appendChild(option);

      emit backgroundColorChanged(color,styleNum);

      QFont font = Fonts[styleNum];

      option = doc.createElement("Font");
      option.setAttribute("bold",QVariant(font.bold()).toString());
      option.setAttribute("italic",QVariant(font.italic()).toString());
      option.setAttribute("underline",QVariant(font.underline()).toString());

      emit fontChanged(font,styleNum);

      style.appendChild(option);
    }

     Bases::out(styleName+".style",doc.toString());
}

void LexerStyle::addColor(QDomElement &option,const QColor &color)
{
    option.setAttribute("red",color.red());
    option.setAttribute("green",color.green());
    option.setAttribute("blue",color.blue());
}

QColor LexerStyle::readColor(QDomElement option)
{
    int red,green,blue;

    red = option.attribute("red").toInt();
    green = option.attribute("green").toInt();
    blue = option.attribute("blue").toInt();

    return QColor(red,green,blue);
}

QString LexerStyle::styleName(int style) const
{
    switch (style)
    {
    case QsciLexerCPP::Default:
        return tr("Default");

    case QsciLexerCPP::Comment:
        return tr("C comment");

    case QsciLexerCPP::CommentLine:
        return tr("CPP comment");

    case QsciLexerCPP::CommentDoc:
        return tr("JavaDoc style C comment");

    case QsciLexerCPP::Number:
        return tr("Number");

    case QsciLexerCPP::Keyword:
        return tr("Keyword");

    case QsciLexerCPP::DoubleQuotedString:
        return tr("Double-quoted string");

    case QsciLexerCPP::SingleQuotedString:
        return tr("Single-quoted string");

    case QsciLexerCPP::UUID:
        return tr("IDL UUID");

    case QsciLexerCPP::PreProcessor:
        return tr("Pre-processor block");

    case QsciLexerCPP::Operator:
        return tr("Operator");

    case QsciLexerCPP::Identifier:
        return tr("Identifier");

    case QsciLexerCPP::UnclosedString:
        return tr("Unclosed string");

    case QsciLexerCPP::VerbatimString:
        return tr("C-SHARP verbatim string");

    case QsciLexerCPP::Regex:
        return tr("JavaScript regular expression");

    case QsciLexerCPP::CommentLineDoc:
        return tr("JavaDoc style CPP comment");

    case QsciLexerCPP::KeywordSet2:
        return tr("Global Variables");

    case QsciLexerCPP::CommentDocKeyword:
        return tr("JavaDoc keyword");

    case QsciLexerCPP::CommentDocKeywordError:
        return tr("JavaDoc keyword error");

    case QsciLexerCPP::GlobalClass:
        return tr("Global classes and typedefs");

    case QsciLexerCPP::RawString:
        return tr("CPP raw string");

    case QsciLexerCPP::TripleQuotedVerbatimString:
        return tr("Vala triple-quoted verbatim string");

    case QsciLexerCPP::HashQuotedString:
        return tr("Pike hash-quoted string");

    case QsciLexerCPP::PreProcessorComment:
        return tr("Pre-processor C comment");

    case QsciLexerCPP::PreProcessorCommentLineDoc:
        return tr("JavaDoc style pre-processor comment");
    }

    return QString();
}










