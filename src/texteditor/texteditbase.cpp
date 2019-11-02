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

#include "texteditbase.h"

#include <QPrintDialog>
#include <qsci/qsciprinter.h>
#include <QStandardItem>
#include <QSettings>
#include <QDebug>

#ifdef _WIN32
#define STDCALL __stdcall
#else
#define STDCALL
#endif

using namespace std;

extern "C" const char* STDCALL AStyleGetVersion(void);
extern "C" char* STDCALL AStyleMain(const char* sourceIn,
                                    const char* optionsIn,
                                    void (STDCALL* fpError)(int, const char*),
                                    char* (STDCALL* fpAlloc)(unsigned long));
void  STDCALL ASErrorHandler(int errorNumber, const char* errorMessage);
char* STDCALL ASMemoryAlloc(unsigned long memoryNeeded);

TextEditBase::TextEditBase(QWidget *parent) :
  QsciScintilla(parent),lastLine(-1)
{

}

int TextEditBase::findText(const QString &text,int start,int end , bool regExp)
{

  SendScintilla(SCI_SETTARGETSTART,start);
  SendScintilla(SCI_SETTARGETEND, end);

  int searchFlags;

  searchFlags = SCFIND_MATCHCASE|SCFIND_WHOLEWORD ;

  if(regExp)
    searchFlags |= SCFIND_REGEXP ;

  SendScintilla(SCI_SETSEARCHFLAGS,searchFlags);

  ScintillaBytes expr = textAsBytes(text);

  return SendScintilla(SCI_SEARCHINTARGET, expr.length(),
                       ScintillaBytesConstData(expr));

}


int TextEditBase::doFind(const QString &text, bool regExp ,bool forward , int pos)
{
  if(pos == -1)
    pos = curPos();

  if(forward)
    {
      return  findText(text,pos,getLength(),regExp) ;
    }
  else
    return  findText(text,pos,0,regExp);

  return -1;
}

bool TextEditBase::find(const QString &text  ,bool regExp, bool forward)
{
  int pos = doFind(text,regExp,forward);

  if(pos  != -1)
    {
      goToPosition(pos);

      return true;
    }
  else
    return false;
}

bool TextEditBase::ensureFindText(const QString &text,int start,int end)
{
  return findText(text,start,end) > -1;
}

void  TextEditBase::complete(AutoCompletionSource acs,bool checkTresh)
{
  Q_UNUSED(acs);
  Q_UNUSED(checkTresh);
}

QString TextEditBase::getTextRange(int startPos,int endPos)
{
  int word_len = endPos - startPos;

  if(word_len > 0)
    {
      char *buf = new char[word_len + 1];

      SendScintilla(SCI_GETTEXTRANGE, startPos, endPos, buf);

      QString word = bytesAsText(buf);

      delete[] buf;

      return word;

    }

  return QString();
}

QString TextEditBase::getTextBetween2Braces(int brace_pos)
{
  return getTextRange(brace_pos,getMatchingBrace(brace_pos));
}

int TextEditBase::findBraceCount(char brace)
{
  return getCurrentInstruction().count(brace);
}

bool TextEditBase::braceCountEqual(char brace,char matching_brace)
{
  return findBraceCount(brace) == findBraceCount(matching_brace);
}

QString TextEditBase::getInstruction(int pos)
{
  int start , end;

  if(instructStartEndPos(pos,&start,&end))
    return getTextRange(start,end).trimmed();
  else
    return text(curLine());

}

bool TextEditBase::instructStartEndPos(int pos,int *start,int *end)
{
  int endPos =  getLength();

  int blockStartPos = findText("{",pos,0);
  int blockEndPos =   findText("}",pos,endPos);

  *start = findText(";",pos,0) +1;
  *end = findText(";",pos , endPos);

  if((*start < blockStartPos || *start ) && (blockStartPos != -1))
    *start = blockStartPos + 1;

  if((*end > blockEndPos)  && (blockEndPos != -1))
    *end = blockEndPos - 1;

  if(*start == -1 || *end == -1)
    return false;
}

QString TextEditBase::getCurrentInstruction()
{
  return getInstruction(curPos());
}

bool TextEditBase::getCurInstrucStartEnd(int *start,int *end)
{
  return instructStartEndPos(curPos(),start,end);

}

int TextEditBase::curLine() const
{
  return SendScintilla(SCI_LINEFROMPOSITION,curPos());
}

int TextEditBase::curPos() const
{
  return SendScintilla(SCI_GETCURRENTPOS);
}

int TextEditBase::getLength() const
{
  return SendScintilla(SCI_GETLENGTH);
}



QStringList TextEditBase::classes()
{
  return QStringList();
}

int TextEditBase::getMatchingBrace(long brace)
{
  return SendScintilla(SCI_BRACEMATCH,brace);
}

int TextEditBase::lineFromPosition(int pos) const
{
  return SendScintilla(SCI_LINEFROMPOSITION,pos);
}

void TextEditBase::setCurrentPosition(int pos)
{
  SendScintilla(SCI_SETCURRENTPOS,pos);
}

void TextEditBase::goToPosition(int pos)
{
  SendScintilla(SCI_GOTOPOS, pos);
}

void TextEditBase::removeText(int line,int index,int length)
{
  int pos = positionFromLineIndex(line,index);

  SendScintilla(SCI_DELETERANGE,pos,length);
}

char TextEditBase::charAt(int pos)
{
  return SendScintilla(SCI_GETCHARAT, pos);
}

void TextEditBase::setSelectionIndentation(const char *options)
{
  if(hasSelectedText())
    {
      replaceSelectedText(format(selectedText(),options));
    }
}

int TextEditBase::lineFromCurrentPoint(bool get)
{
  if(get)
    {
      QPoint pos = mapFromGlobal(cursor().pos());
      lastLine = lineFromPosition(SendScintilla(SCI_POSITIONFROMPOINT,pos.x(),pos.y()));
    }

  return  lastLine;
}

void TextEditBase::formatSourceCode(const char *options)
{
  selectAll();
  replaceSelectedText(format(text(),options));
}

const char *TextEditBase::formatOptions()
{
  QSettings settings;

  return settings.value("FormatOptions").toString().toLatin1().constData();
}

QString TextEditBase::format(const QString &text,const char * options)
{
  if(options == NULL)
    options = formatOptions();

  ScintillaBytes bytes = textAsBytes(text);

  const char* textIn = ScintillaBytesConstData(bytes) ;

  // call the Artistic Style formatting function
  char* textOut = AStyleMain(textIn,
                             options,
                             ASErrorHandler,
                             ASMemoryAlloc);

  // does not need to terminate on an error
  // an error message has been displayed by the error handler

  if (textOut == NULL)
    qDebug()<<"Cannot format";

  QString formatText = textOut;
  // must delete the temporary buffers
  delete [] textIn;
  delete [] textOut;

  return formatText;
}

void  STDCALL ASErrorHandler(int errorNumber, const char* errorMessage)
{   qDebug() << "astyle error " << errorNumber << "\n"
             << errorMessage << endl;
}

// Allocate memory for the Artistic Style formatter.
char* STDCALL ASMemoryAlloc(unsigned long memoryNeeded)
{   // error condition is checked after return from AStyleMain
  char* buffer = new(nothrow) char [memoryNeeded];
  return buffer;
}



