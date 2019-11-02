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

#include "refactor.h"
#include "textedit.h"
#include <bases.h>

Refactor::Refactor(QObject *parent) : QObject(parent)
{

}

void Refactor::setEditor(TextEditBase *editor)
{
  this->editor = editor;
}

QString Refactor::addDeclaration(const QString &type,const QString &field)
{
  return type + " " + field;
}

QString Refactor::thisField(const QString &type,const QString &field)
{
  if(type.endsWith("*"))
    return "this." + field;
  else
    return "this->" + field;
}

QString Refactor::generateConstructor(const QString &_class ,const QMap<QString,QString> &args)
{
  QString genCode;
  genCode += _class + "::" +_class + "(";

  foreach(QString arg,args.values())
    {
      genCode += addDeclaration(args.key(arg),arg) ;

      if( args.values().last() != arg)
        genCode += ", " ;
    }

  genCode += ")";

  return genCode;
}

QString Refactor::generateConstructor(const QString &_class ,const QMap<QString,QString> &args
                                      ,const QString &content)
{
  QString genCode = generateConstructor(_class,args);

  genCode += "\n{\n";
  genCode += content;
  genCode += "\n}\n";

  return genCode;

}

void Refactor::addConstructorUsingField(const QString _class,const QString &type,const QString &field)
{
  QString genCode;

  QMap<QString,QString> dec;
  dec.insert(type,field);

  genCode += thisField(type,field)  + "=" + field + ";";

  generateConstructor(_class,dec,genCode);
}

void Refactor::addConstructorFromSuperClass(const QString &_class, const QString &super_class,
                                            const QMap<QString,QString> &args)
{
  QString genCode = generateConstructor(_class,args);
  genCode += " : "  + super_class;
  genCode += " \n ";

}

void Refactor::addInclude(const QString &type)
{

}

void Refactor::format()
{

}

void Refactor::correctIndentation()
{

}

void Refactor::insertComment(int commentType)
{
  if(editor->hasSelectedText())
    {
      int start = editor->SendScintilla(TextEditBase::SCI_GETSELECTIONSTART);
      int end   = editor->SendScintilla(TextEditBase::SCI_GETSELECTIONEND);

      int startLine,startIndex ,endLine,endIndex;

      editor->lineIndexFromPosition(start,&startLine,&startIndex);
      editor->lineIndexFromPosition(end,&endLine,&endIndex);

      QString startLineText = editor->text(startLine).trimmed();

      switch(commentType)
        {
        case 0:

          if(startLineText.startsWith("//"))
            {
              for(int line = startLine; line<=endLine; line++)
                editor->removeText(line,0,2);
            }
          else
            {
              for(int line = startLine; line<=endLine; line++)
                editor->insertAt("//",line,0);

            }
          break;

        case 1:
          if(startLineText.startsWith("/*") && editor->text(endLine).trimmed().endsWith("*/"))
            {
              editor->removeText(endLine,endIndex - 2,2);
              editor->removeText(startLine,startIndex,2);

            }
          else
            {   editor->insertAt("*/",endLine ,endIndex);
              editor->insertAt("/*",startLine,startIndex);

            }
          break;
        }
    }
}

void Refactor::toggleComment()
{
  insertComment(0);
}

void Refactor::addBlockComment()
{
  insertComment(1);
}

void Refactor::upperCaseSelection()
{
  editor->replaceSelectedText(editor->selectedText().toUpper());
}

void Refactor::lowerCaseSelection()
{
  editor->replaceSelectedText(editor->selectedText().toLower());
}

QString Refactor::fieldToMethod(const QString &field)
{
  QString method = field;
  return  method.replace(0,1,method[0].toUpper());
}

void Refactor::addSetter(QString _class,const QString &type,const QString &field)
{
  QString genCode;

  genCode += "void " + _class + "::" +"set" + fieldToMethod(field) + "(" + type + " " + field+ ")";
  genCode += "\n{";
  genCode += thisField(field,type) + " = "+ field;
  genCode += "\n}";

  editor->insert(genCode);
}

void Refactor::addGetter(QString _class,const QString &type,const QString &field)
{
  QString genCode;

  if(field.startsWith("_"))
    {
      QString getMethod = field;

      genCode += type+ " " + _class + "::" + field + "()\n{\nreturn " + getMethod.remove(0,1) + ";\n}\n";

    }
  else
    {
      genCode += type+ " " + _class + "::" +"get" + fieldToMethod(field) + "()";
    }

  editor->insert(genCode);
}

void Refactor::addGettersAndSetters(QString _class,const QString &type,const QString &field)
{
  addGetter(_class,type,field);
  addSetter(_class,type,field);

}

QString Refactor::editorSelectedText()
{
  return editor->selectedText();
}

void Refactor::addDefinition()
{

}

void Refactor::addDeclaration(const QString &accessType)
{

}




void Refactor::surroundWith(const QString &key)
{
  int start = editor->SendScintilla(TextEditBase::SCI_GETSELECTIONSTART);
  int end   = editor->SendScintilla(TextEditBase::SCI_GETSELECTIONEND);

  int startLine,startIndex ,endLine,endIndex;

  editor->lineIndexFromPosition(start,&startLine,&startIndex);
  editor->lineIndexFromPosition(end,&endLine,&endIndex);


  QString startText;
  QString endText;

  if(key == "if")
    {
      startText = "if()\n{\n";
      endText = "\n}";

    }
  else if(key == "else if")
    {
      startText = "else if()\n";
      endText = "\n}";

    }

  if(key == "for")
    {
      startText = "for(;;;)\n{\n";
      endText = "\n}";

    }
  else if(key == "else if")
    {
      startText = "while()\n{\n";
      endText = "\n}";

    }

  editor->insertAt(startText,endLine,endIndex);
  editor->insertAt(endText,startLine,startIndex);

}



