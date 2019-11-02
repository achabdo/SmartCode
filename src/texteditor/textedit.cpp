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

#include "textedit.h"

#include <QToolTip>
#include <QHelpEvent>
#include <QFileInfo>
#include <QMenu>
#include <QDir>
#include <QDebug>

#include <Qsci/qscilexer.h>
#include <Qsci/qscilexercpp.h>
#include <Qsci/qsciabstractapis.h>

#include <bases.h>
#include <tabwidget.h>

#include "core_constants.h"
#include "insertfunctionswidget.h"
#include "texteditmanager.h"
#include "classparser.h"

using namespace std;

const char acSeparator = '\x03';

TextEdit::TextEdit(QWidget *parent) :
  TextEditBase(parent)
{
  registerImage(0,QPixmap(Core::Icon::METHOD_PUBLIC));
  registerImage(1,QPixmap(Core::Icon::METHOD_PRIVATE));
  registerImage(2,QPixmap(Core::Icon::METHOD_PROTECETED));
  registerImage(3,QPixmap(Core::Icon::CLASS));
  registerImage(4,QPixmap(Core::Icon::ENUM));
  registerImage(5,QPixmap(Core::Icon::ENUM_PUBLIC));

  setBraceMatching(StrictBraceMatch);
  setMatchedBraceForegroundColor(Qt::red);

  setAutoCompletionThreshold(3);
  setAutoCompletionCaseSensitivity(false);
  setMarginSensitivity(1,true);
  setFolding(QsciScintilla::BoxedTreeFoldStyle);
  setCallTipsPosition(QsciScintilla::CallTipsAboveText);
  setCallTipsStyle(QsciScintilla::CallTipsNoContext);

  setAutoIndent(true);

  markerDefine(QsciScintilla::Circle ,TextEdit::Breakpoint);
  markerDefine(QsciScintilla::CircledMinus ,TextEdit::BreakpointDisabled);
  markerDefine(QsciScintilla::SmallRectangle ,Bookmark);
  markerDefine(QsciScintilla::RightTriangle ,CurrentLine);
  setMarkerBackgroundColor(Qt::red,0);

  indicatorDefine(SquiggleIndicator,0);
  setIndicatorForegroundColor(Qt::red,0);

  indicatorDefine(SquiggleIndicator,1);
  setIndicatorForegroundColor(Qt::green,1);

  updateLineNumberArea();

  connect(this,SIGNAL(linesChanged()),this,SLOT(updateLineNumberArea()));
  connect(this,SIGNAL(marginClicked(int,int,Qt::KeyboardModifiers))
          ,this,SLOT(addMarker(int,int,Qt::KeyboardModifiers)));

  connect(this,SIGNAL(SCN_CHARADDED(int)),
          SLOT(handleCharAdded(int)));

  connect(this,SIGNAL(SCN_HOTSPOTRELEASECLICK(int,int)),this,SLOT(handleHotspot(int,int)));
  connect(this,SIGNAL(newHeader(QStringList)),this,SLOT(updateClasses(QStringList)));
  connect(this,SIGNAL(textChanged()),this,SLOT(update()));

  QFont f("Courier",10);

  setMarginsForegroundColor(Qt::darkGray);
  setMarginsFont(f);

  SendScintilla(SCI_SETHOTSPOTACTIVEFORE ,true, QColor(Qt::blue));
  SendScintilla(SCI_SETHOTSPOTACTIVEUNDERLINE,true);

  setAutoCompletionSource(AcsAll);
  setUtf8(true);

  createErrorIndicators();
}

void TextEdit::createErrorIndicators()
{
  setIndicatorOutlineColor(QColor(Qt::red),FillSyntaxeError);
  setIndicatorOutlineColor(QColor(Qt::green),FillWarning);
  setIndicatorOutlineColor(QColor(Qt::blue),FillSyntaxeError);
}

void TextEdit::fillError(int start , int end,FillType fileType)
{
  int startLine,endLine,startIndex,endIndex;

  lineIndexFromPosition(start,&startLine,&startIndex);
  lineIndexFromPosition(end,&endLine,&endIndex);

  fillIndicatorRange(startLine,startIndex,endLine,endIndex,fileType);
}

void TextEdit::update()
{
  //    int pos = 0;

  //    QString text;

  //    while(pos != getLength())
  //    {
  //        if(charAt(pos) == '{')
  //        {
  //            int mBracePos = getMatchingBrace(pos);

  //            ++ mBracePos;

  //            while(charAt(mBracePos) == ' ')
  //                ++ mBracePos;

  //            char c = charAt(mBracePos);

  //            if(c != ';')
  //            {
  //                pos = mBracePos;
  //                continue;

  //            }
  //        }

  //        text += charAt(pos);
  //        ++ pos;
  //    }

  // qDebug() << text;

  //        if(line.contains(Syntaxe::varReg) && !variableIsUnderBloc(pos))
  //            emit variableAdded(clParser->varModel(line));

  //            else if(strchr(")",ch) != NULL)
  //            {
  //                if(line.contains(Syntaxe::funcReg))
  //                    emit variableAdded(clParser->functionModel(line));

  //            }
  //    }
}

void TextEdit::setClassParser(ClassParser * parser)
{
  clParser = parser;

  //clParser->thowArg(true);
  //clParser->thowType(true);
}

QString TextEdit::toFileName() const
{
  return fileName;
}

void TextEdit::handleCharAdded(int ch)
{
  long pos = SendScintilla(SCI_GETCURRENTPOS);

  if (pos != SendScintilla(SCI_GETSELECTIONEND) || pos == 0)
    return;

  if(!lex.isNull() && lexerIs("C++"))
    {
      QString line = text(lineFromPosition(pos));

      //        if(strchr(";",ch) != NULL)
      //        {
      //            if(line.contains(Syntaxe::varReg) && !variableIsUnderBloc(pos))
      //                emit variableAdded(clParser->varModel(line));

      //        }

      //        else if(strchr(")",ch) != NULL)
      //        {
      //            if(line.contains(Syntaxe::funcReg))
      //                emit variableAdded(clParser->functionModel(line));

      //        }

      if(line.contains("#include"))
        {
          wseps << "/";
          setAutoCompletionWordSeparators(wseps);

          QString fileName /*= clParser->includeFileName(line)*/;

          if(!fileName.isEmpty())
            emit newHeader(QStringList()<<fileName);
        }

      QsciAbstractAPIs * apis = lex->apis();

      if(apis)
        {
          QString autoComp = apis->autoComplete(ch,pos);

          if(!autoComp.isNull())
            {
              //              _autoComp = autoComp;
              insert(autoComp);
            }
        }
    }

  if (isListActive())
    {
      if (isStartChar(ch))
        {
          cancelList();
          complete(acSource,false);
        }

      return;
    }

  if (call_tips_style != CallTipsNone && !lex.isNull() && strchr("(),", ch) != NULL)
    callTip();

  if (autoInd)
    {
      if (lex.isNull() || (lex->autoIndentStyle() & AiMaintain))
        maintainIndentation(ch, pos);
      else
        autoIndentation(ch, pos);
    }

  if (!isCallTipActive())
    {
      if (isStartChar(ch))
        {
          complete(acSource,false);
        }
      else if (acThresh >= 1 && isWordCharacter(ch))
        {
          complete(acSource,true);
        }
    }

  wseps.removeOne("/");
  setAutoCompletionWordSeparators(wseps);
}

void TextEdit::setLexer(QsciLexer *lexer)
{
  QsciScintilla::setLexer(lexer);

  if(lexerIs("Git"))
    setReadOnly(true);
}

bool TextEdit::lexerIs(const char * language)
{
  if(lex.isNull())
    return false;

  return QString::compare(lex->language(),language) == 0;
}

void TextEdit::complete(AutoCompletionSource acs,bool checkTresh)
{
  QStringList list;

  int pos = SendScintilla(SCI_GETCURRENTPOS);

  QStringList context = apiContext(pos, pos, ctPos);

  if(context.isEmpty())
    return ;

  ScintillaBytes s = textAsBytes(context.last());

  int last_len = s.length();

  if (checkTresh && last_len < acThresh)
    return;

  if ((acs == AcsAll || acs == AcsAPIs) && !lex.isNull())
    {
      QsciAbstractAPIs * apis = lex->apis();

      if (apis)
        apis->updateAutoCompletionList(context, list);

    }

  if (acs == AcsAll || acs == AcsDocument)
    {
      completeFromDocument(s,pos,list);
    }

  //    if(list.isEmpty())
  //        return;

  //    int max = 0;

  //    foreach(QString e,list)
  //    {
  //        if(e.length() > max)
  //            max = e.length();
  //    }

  //SendScintilla(SCI_AUTOCSETMAXWIDTH,0);
  //SendScintilla(SCI_AUTOCSETMAXHEIGHT,list.count())


  SendScintilla(SCI_AUTOCSETSEPARATOR, acSeparator);
  ScintillaBytes slist = textAsBytes(list.join(QChar(acSeparator)));

  SendScintilla(SCI_AUTOCSHOW, last_len, ScintillaBytesConstData(slist));
}

void TextEdit::updateLineNumberArea()
{
  unsigned  int n = lines();
  int i = 0;

  while( n >= 1 )
    {
      n = n/10;
      i = i+1;
    }

  setMarginWidth(0,i*10+10);
}

void TextEdit::addMarker(int margin,int line,Qt::KeyboardModifiers key)
{
  Q_UNUSED(margin);

  if(key == Qt::ShiftModifier)
    {
      if(markersAtLine(line) == 0)
        {

          emit bookmarkToggled(fileName,line,true);
        }
      else
        {
          markerDelete(line,Bookmark);
          emit bookmarkToggled(fileName,line,false);
        }
    }
  else
    {
      if(markersAtLine(line) == 0)
        {
          markerAdd(line,TextEdit::Breakpoint);

          emit breakPointToggled(fileName,line,true);
        }
      else
        {
          markerDelete(line,TextEdit::Breakpoint);

          emit breakPointToggled(fileName,line,false);
        }
    }
}

void TextEdit::setDebuggerLine(int line)
{
  markerDeleteAll(CurrentLine);
  markerAdd(line,CurrentLine);

  //markers.append(line);
}

void TextEdit::keyPressEvent(QKeyEvent *e)
{
  QsciScintilla::keyPressEvent(e);

  if(e->key() == Qt::Key_Control)
    {
      SendScintilla(SCI_STYLESETHOTSPOT, QsciLexerCPP::Identifier, true);
      SendScintilla(SCI_STYLESETHOTSPOT, QsciLexerCPP::PreProcessor, true);
      SendScintilla(SCI_STYLESETHOTSPOT, QsciLexerCPP::GlobalClass, true);
      SendScintilla(SCI_STYLESETHOTSPOT, QsciLexerCPP::KeywordSet2, true);
    }

  //    if(e->key() == Qt::Key_Backspace)
  //    {
  //        int pos = curPos();

  //        if(!variableIsUnderBloc(pos))
  //        {
  //            QString text = text(lineFromPosition(pos));

  //            QString varDeclaration = text.split(";").last();
  //            varDeclaration.append(";");
  //        }
  //    }
}

void TextEdit::keyReleaseEvent(QKeyEvent *e)
{
  QsciScintilla::keyReleaseEvent(e);

  if(e->key() ==  Qt::Key_Control)
    {
      SendScintilla(SCI_STYLESETHOTSPOT, QsciLexerCPP::Identifier);
      SendScintilla(SCI_STYLESETHOTSPOT, QsciLexerCPP::PreProcessor);
      SendScintilla(SCI_STYLESETHOTSPOT, QsciLexerCPP::GlobalClass);
      SendScintilla(SCI_STYLESETHOTSPOT, QsciLexerCPP::KeywordSet2);
    }
}

bool TextEdit::event(QEvent *e)
{
  if( e->type() == QEvent::ToolTip)
    {
      QString text;

      QHelpEvent *help = static_cast<QHelpEvent *>(e);

      int pos = positionFromPoint(help->pos());

      int startPos = SendScintilla(SCI_WORDSTARTPOSITION,pos);
      int endPos = SendScintilla(SCI_WORDENDPOSITION,pos);

      QStringList context = apiContext(endPos, endPos, ctPos);

      if(!context.isEmpty())
        {
          text = clParser->type(context,startPos,true);

          if(!text.isEmpty())
            QToolTip::showText(help->globalPos(), text);
          else
            {
              QToolTip::hideText();
              e->ignore();
            }
        }

    }
  return QsciScintilla::event(e);
}

void TextEdit::callTip()
{
  QsciAbstractAPIs *apis = lex->apis();

  if (!apis)
    return;

  int pos, commas = 0;
  bool found = false;
  char ch;

  pos = SendScintilla(SCI_GETCURRENTPOS);

  // Move backwards through the line looking for the start of the current
  // call tip and working out which argument it is.
  while ((ch = getCharacter(pos)) != '\0')
    {
      if (ch == ',')
        ++commas;
      else if (ch == ')')
        {
          int depth = 1;

          while ((ch = getCharacter(pos)) != '\0')
            {
              if (ch == ')')
                ++depth;
              else if (ch == '(' && --depth == 0)
                break;
            }
        }
      else if (ch == '(')
        {
          found = true;
          break;
        }
    }

  SendScintilla(SCI_CALLTIPCANCEL);

  if (!found)
    return;

  QStringList context = apiContext(pos, pos, ctPos);

  QString type;

  if (context.isEmpty())
    return;

  // The last word is complete, not partial.
  int position = SendScintilla(SCI_GETCURRENTPOS);
  int line, index;
  lineIndexFromPosition(position, &line, &index);

  if(context.count()>1 && context[0] != "this")
    type = clParser->type(QStringList()<<context[context.count()-2],line,index);
  else
    type = clParser->findVarClass(position);

  type = clParser->correctType(type);
  QString fileName = "";/*clParser->findClassHeader(type);*/

  context.prepend(fileName);

  ct_cursor = 0;
  ct_shifts.clear();
  ct_entries = apis->callTips(context,commas, call_tips_style, ct_shifts);

  int nr_entries = ct_entries.count();

  if (nr_entries == 0)
    return;

  if (maxCallTips > 0 && maxCallTips < nr_entries)
    {
      ct_entries = ct_entries.mid(0, maxCallTips);
      nr_entries = maxCallTips;
    }

  QString ct;

  if (maxCallTips < 0 && nr_entries > 1)
    {

      ct = ct_entries[0];
      ct.prepend('\002');
    }
  else
    {
      ct = ct_entries.join("\n");
    }

  QByteArray ct_ba = ct.toLatin1();
  const char *cts = ct_ba.data();


  int showPos = ctPos + context.last().length()+1;
  SendScintilla(SCI_CALLTIPSHOW, showPos , cts);

  // Done if there is more than one call tip.
  if (nr_entries > 1)
    return;

  // Highlight the current argument.
  const char *astart;

  if (commas == 0)
    astart = strchr(cts, '(');
  else
    for (astart = strchr(cts, ','); astart && --commas > 0; astart = strchr(astart + 1, ','))
      ;

  if (!astart || !*++astart)
    return;

  // The end is at the next comma or unmatched closing parenthesis.
  const char *aend;
  int depth = 0;

  for (aend = astart; *aend; ++aend)
    {
      char ch = *aend;

      if (ch == ',' && depth == 0)
        break;
      else if (ch == '(')
        ++depth;
      else if (ch == ')')
        {
          if (depth == 0)
            break;

          -- depth;
        }
    }

  if (astart != aend)
    SendScintilla(SCI_CALLTIPSETHLT, astart - cts, aend - cts);
}

void TextEdit::updateClasses(const QStringList &includes)
{
  //    if(lexerIs("C++"))
  //    {
  //        clParser->updateClasses(includes);

  //        QString header;

  //        if(clParser->isHeaderFile(fileName))
  //        {
  //            header = fileName;
  //        }
  //        else
  //            header = clParser->swapHeaderSource(fileName);

  //        QStringList list ;//= clParser->funcsListFromFile(header);

  //        QsciAbstractAPIs *apis = lex->apis();

  //        apis->load(list);
  //        apis->load(classes());

  //        foreach(QString dir , clParser->searchDirs())
  //        {
  //            QDir d(dir);

  //            QStringList list = d.entryList(QStringList()<< "*.h" , QDir::AllDirs|QDir::NoDotAndDotDot);

  //            list.replaceInStrings(QRegExp("$"),"/");

  //            apis->load(list);
  //            apis->load(d.entryList(QStringList()<< "*.h" , QDir::Files|QDir::NoDotAndDotDot));

  //        }

  //        lex->updateClasses(classes());
  //        lex->updateGlobalVariables(globalVars);

  //        for (int k = 1; k <= 3; ++k)
  //        {
  //            if(k != 2)
  //            {
  //                const char *kw = lexer() -> keywords(k + 1);

  //                if (!kw)
  //                    kw = "";

  //                SendScintilla(SCI_SETKEYWORDS, k, kw);

  //            }
  //        }
  //    }
}

int TextEdit::positionFromPoint(const QPoint &point )
{
  return  SendScintilla(SCI_CHARPOSITIONFROMPOINTCLOSE, point.x(),
                        point.y());
}

QMenu * TextEdit::createStandardContextMenu()
{
  QMenu * menu = new QMenu(this);

  bool hasSelection = hasSelectedText();

  QAction *action;

  if(lexerIs("C++"))
    {
      action = menu->addAction(tr("Switch Header/Source"), this, SIGNAL(switchSourceHeader()),QKeySequence("F4"));

      QMenu * InsertMenu;
      InsertMenu = menu->addMenu(tr("Insert"));

      if(hasTextUnderCursor() && !definitionExsits())
        {
          const QString sourceFile = QFileInfo(clParser->swapHeaderSource(fileName)).fileName();
          action = InsertMenu->addAction(tr("&Add a Definintion in ") + sourceFile, this, SLOT(addDefinition()));
        }

      action = InsertMenu->addAction(tr("&Insert Definitions"), this, SLOT(showInsertFunctionWidget()));
      action = InsertMenu->addAction(tr("&Insert All Definitions"), this, SLOT(insertAllFunction()));

      menu->addAction(tr("Toggle Comment"),this,SLOT(insertBlockComment()));
      menu->addAction(tr("Add Block Comment"),this,SLOT(insertDocComment()));
      menu->addAction(tr("Correct Indentation"),this,SLOT(setSelectionIndentation()));
      menu->addAction("Upper Case",this,SLOT(setTextUpperCase()));

      menu->addSeparator();
    }

  if(SendScintilla(SCI_CANPASTE))
    {
      menu->addAction(tr("&Paste"),this,SLOT(paste()));
      set_shortcut(action, QsciCommand::Paste);
    }

  if(hasSelection)
    {
      menu->addAction(tr("Cu&t"),this,SLOT(cut()));
      set_shortcut(action, QsciCommand::SelectionCut);

      menu->addAction(tr("&Copy"),this,SLOT(copy()));
      set_shortcut(action, QsciCommand::SelectionCopy);
    }

  return menu;
}

bool TextEdit::hasTextUnderCursor()
{
  return !wordAtPosition(curPos()).isEmpty();
}

bool TextEdit::definitionExsits()
{
  //    int endPos = SendScintilla(SCI_WORDENDPOSITION,curPos());

  //    QStringList context = apiContext(endPos,endPos,ctPos);

  //    return clParser->itemExists(context,fileItem);
}

void TextEdit::addDefinition()
{

}

void TextEdit::contextMenuEvent(QContextMenuEvent *e)
{
  QMenu *menu;

  QPoint pos = mapFromGlobal(cursor().pos());

  int marginsWidth = marginWidth(0) + marginWidth(1) ;

  if(pos.x() < marginsWidth)
    {
      menu = new QMenu(this);

      menu->addAction(tr("Toggle Bookmark"));
      menu->addSeparator();

      int line = lineFromCurrentPoint(true);

      if(markersAtLine(line))
        {
          menu->addAction(tr("Remove Breakpoint"),this,SLOT(removeBreakPoint()));

          if(markerLine(line) == CircledMinus)
            menu->addAction("Enable Breakpoint");
          else
            menu->addAction(tr("Disable Breakpoint"),this,SLOT(disableBreakPoint()));

          menu->addAction(tr("Edit Breakpoint"),this,SLOT(editBreakPoint()));
        }
      else
        menu->addAction(QString(tr("set Breakpoint at Line %1")).arg(line),this,SLOT(setBreakPoint()));
    }
  else
    menu = createStandardContextMenu();

  menu->setAttribute(Qt::WA_DeleteOnClose);
  menu->popup(e->globalPos());
}

void TextEdit::editBreakPoint()
{
  emit breakPointEdited(fileName,lineFromCurrentPoint());
}

void TextEdit::disableBreakPoint()
{
  int line = lineFromCurrentPoint();

  markerDelete(line,TextEdit::Breakpoint);
  markerAdd(line,TextEdit::BreakpointDisabled);

  emit breakPointToggled(fileName,line,true);
}

void TextEdit::setBreakPoint()
{
  emit breakPointToggled(fileName,lineFromCurrentPoint(),true);
}

void TextEdit::removeBreakPoint()
{
  emit breakPointToggled(fileName,lineFromCurrentPoint(),false);
}

void TextEdit::insertFunctions(const QStringList &funcs)
{
  foreach(QString func,funcs)
    {
      QString textToInsert;

      textToInsert += "\n\n";
      textToInsert += func;
      textToInsert +="\n{\n\n}";

      insert(textToInsert);
    }
}

void TextEdit::showInsertFunctionWidget()
{
  InsertFunctionsWidget *functionWidget = new InsertFunctionsWidget(clParser,fileName,this);
  connect(functionWidget,SIGNAL(methodsSelected(QStringList)),this,SLOT(insertFunctions(QStringList)));
  functionWidget->exec();
  delete  functionWidget;
}

void TextEdit::insertAllFunction()
{
  QString headerFile = clParser->swapHeaderSource(fileName);
  QStringList classes = clParser->findFileClasses(headerFile);

  foreach(QString klass,classes)
    {
      // QStringList funcs = clParser->funcsListFromFile(headerFile,klass);
      //  insertFunctions(funcs);
    }
}

void TextEdit::handleHotspot(int position , int modifiers)
{
  if( modifiers == SCMOD_CTRL )
    {
      QString foundFile,type;

      int line,index,pos;

      pos = SendScintilla(SCI_WORDENDPOSITION,position);

      lineIndexFromPosition(pos,&line,&index);

      QStringList context = apiContext(pos,pos,ctPos);

      type = clParser->type(context,line,index);

      if(!type.isNull())
        {
          if(classes().contains(type) && context.last() == type)
            foundFile = "";/*clParser->findClassHeader(type)*/
          else
            foundFile = "";/*clParser->toTypeFile()*/

          if(QFileInfo(type).isFile())
            emit openFile(type ,0 , 0);
          else
            {
              if(!foundFile.isNull())
                emit openFile(foundFile ,clParser->foundLine(),clParser->foundIndex());
              else
                {

                  QTimer::singleShot(1,this,SLOT(getTypePosition()));
                }

            }
        }
      foundFile.clear();
    }
}

void TextEdit::getTypePosition()
{
  goToPosition(positionFromLineIndex(clParser->foundLine(),clParser->foundIndex()));
}

ClassParser * TextEdit::classParser()
{
  return clParser;
}

void TextEdit::setFileName(const QString &file)
{
  QString ext = Bases::fileSuffix(file);

  if(ext == "c" || ext == "cpp" || ext == "h")
    {
    setLexer(TextEditManager::lexerCPP());
    }

  else if(ext == "git")
    setLexer(TextEditManager::lexerGit());

  fileName = file;
}

void TextEdit::setCurrentPos(int pos)
{
  SendScintilla(SCI_SETCURRENTPOS,pos);
}

void TextEdit::completeFromDocument(QsciScintillaBase::ScintillaBytes word ,int start,QStringList &wlist)
{
  const char *last_data = ScintillaBytesConstData(word);

  int sflags = SCFIND_WORDSTART;

  if (!SendScintilla(SCI_AUTOCGETIGNORECASE))
    sflags |= SCFIND_MATCHCASE;

  SendScintilla(SCI_SETSEARCHFLAGS, sflags);

  int pos = 0;
  int dlen = SendScintilla(SCI_GETLENGTH);
  int caret = SendScintilla(SCI_GETCURRENTPOS);
  int clen = caret - start;
  char *orig_context = new char[clen + 1];

  SendScintilla(SCI_GETTEXTRANGE, start, caret, orig_context);

  for (;;)
    {
      int fstart;

      SendScintilla(SCI_SETTARGETSTART, pos);
      SendScintilla(SCI_SETTARGETEND, dlen);

      if ((fstart = SendScintilla(SCI_SEARCHINTARGET, clen, orig_context)) < 0)
        break;

      // Move past the root part.
      pos = fstart + clen;

      // Skip if this is the context we are auto-completing.
      if (pos == caret)
        continue;

      // Get the rest of this word.
      QString w = last_data;

      while (pos < dlen)
        {
          char ch = SendScintilla(SCI_GETCHARAT, pos);

          if (!isWordCharacter(ch))
            break;

          w += ch;
          ++pos;
        }

      // Add the word if it isn't already there.
      if (!w.isEmpty())
        {
          if (!wlist.contains(w))
            wlist.append(w);
        }
    }

  delete []orig_context;
}

bool TextEdit::variableIsUnderBloc(int pos)
{
  const int varPos = pos;

  while(pos != -1)
    {
      int bracePos = doFind("{",false,false,pos);
      int mBracePos = getMatchingBrace(bracePos);

      if(varPos  > bracePos && varPos < mBracePos)
        {
          ++ mBracePos;

          while(charAt(mBracePos) == ' ')
            ++ mBracePos;

          if(charAt(mBracePos) == ';')
            return false;
          else
            return true ;


        }

      pos = bracePos;
    }

  return false;
}













