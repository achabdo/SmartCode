#ifndef TEXTEDITBASE_H
#define TEXTEDITBASE_H

#include "texteditor_global.h"

#include  <Qsci/qsciscintilla.h>
#include  <QHash>

class QStandardItem;
class TEXTEDITORSHARED_EXPORT TextEditBase : public QsciScintilla
{
  Q_OBJECT
public:

  explicit TextEditBase(QWidget *parent = 0);

  int findText(const QString &text, int start, int end, bool regExp = false);

  int doFind(const QString &text,  bool regExp = false , bool forward = true, int pos = -1) ;
  bool find(const QString &text , bool regExp = false, bool forward = true);

  bool ensureFindText(const QString &text,int start,int end);

  void setCurrentPosition(int pos);
  virtual void complete(QsciScintilla::AutoCompletionSource acs, bool checkTresh);

  QString getTextRange(int startPos, int endPos);

  QString getInstruction(int pos);
  QString getCurrentInstruction();

  QString getTextBetween2Braces(int brace_pos);

  int findBraceCount(char brace);
  bool braceCountEqual(char brace,char matching_brace);

  int curLine() const;
  int curPos() const;
  int getLength() const;

  bool instructStartEndPos(int pos,int *start, int *end);
  bool getCurInstrucStartEnd(int *start,int *end);

  QStringList classes();

  int getMatchingBrace(long brace);

  int lineFromPosition(int pos) const;

  void removeText(int line, int index, int length);

  char charAt(int pos);

signals:

public slots:

  void goToPosition(int pos);
  void formatSourceCode(const char *options = NULL);
private slots:
  void setSelectionIndentation(const char *options = NULL);
protected:
  QStringList globalVars;

  int lineFromCurrentPoint(bool get = false);
private:
  QString format(const QString &text, const char *options);


  int lastLine;
  const char *formatOptions();
};

#endif // TEXTEDITBASE_H
