#ifndef DEBUGGERCLIENT_H
#define DEBUGGERCLIENT_H

#include <QTreeWidget>

class DebuggerClient : public QTreeWidget
{
  Q_OBJECT
public:
  enum TakeLines {TakeFirstLine = 1, TakeEndLine = 2 , NoTakeLine = 0};

  explicit DebuggerClient(QWidget *parent = 0);
  ~DebuggerClient();

  virtual QStringList headers() const ;
  virtual QString cmd()  const = 0;


  virtual void updateClient(const QString &output);
protected:
  virtual int linesToBeRemoved() const;
  virtual QString outputFormat() const = 0;
};

#endif // DEBUGGERCLIENT_H
