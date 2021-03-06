#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include "texteditor_global.h"

#include "texteditbase.h"

class QMenu;
class ClassParser;
class TextEditManager;
class QStandardItem;

class TEXTEDITORSHARED_EXPORT TextEdit : public TextEditBase
{
  Q_OBJECT
public:

  enum MarkerType{Breakpoint,BreakpointDisabled,Bookmark,CurrentLine};

  enum FillType { FillSyntaxeError,FillWarning,FillSemanticError};

  explicit TextEdit(QWidget *parent = 0);

  QString toFileName() const;

  int positionFromPoint(const QPoint &point );

  void complete(QsciScintilla::AutoCompletionSource acs, bool checkTresh);

  ClassParser* classParser();
  void setFileName(const QString &file);
  void setCurrentPos(int pos);

  bool lexerIs(const char *language);

  void setClassParser(ClassParser *parser);
signals:

  void openFile(const QString &fileName , int line,int index);
  void breakPointToggled(const QString &fileName,int line ,bool);
  void breakPointEnabled(const QString &fileName,int line ,bool);
  void breakPointEdited(const QString &fileName,int line);
  void bookmarkToggled(const QString &fileName,int line,bool);

  void newHeader(const QStringList &includes);
  void removeHeader(const QStringList &includes);
  void variableAdded(const QString &var);
  void switchSourceHeader();

protected:
  void keyPressEvent(QKeyEvent *e);
  void keyReleaseEvent(QKeyEvent *);

  bool event(QEvent *e);
  void contextMenuEvent(QContextMenuEvent *e);


public slots:

  void addDefinition();
  void setLexer(QsciLexer *lexer);
  void handleCharAdded(int ch);
  void updateLineNumberArea();
  void setDebuggerLine(int line);
  void addMarker(int margin,int line,Qt::KeyboardModifiers key);
  void getTypePosition();
  void updateClasses(const QStringList &includes);
private slots:

  void showInsertFunctionWidget();
  void insertAllFunction();
  void insertFunctions(const QStringList &funcs);

  void update();

  void handleHotspot(int position , int modifiers);

  void editBreakPoint();
  void disableBreakPoint();
  void setBreakPoint();
  void removeBreakPoint();

protected:
  void callTip();
private:
  QString fileName;
  void completeFromDocument(QsciScintillaBase::ScintillaBytes word ,int start ,QStringList &wlist);

  void createErrorIndicators();

  void fillError(int start , int end,FillType fileType);

  bool variableIsUnderBloc(int pos);

  QMenu *createStandardContextMenu();
  bool hasTextUnderCursor();
  bool definitionExsits();

  TextEditManager * manager;

  ClassParser *clParser;
  QString _autoComp;
};

#endif // TEXTEDIT_H                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
