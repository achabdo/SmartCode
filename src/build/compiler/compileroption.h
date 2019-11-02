#ifndef COMPILEROPTION_H
#define COMPILEROPTION_H

#include <QObject>

#include <QString>
#include <QStringList>

class Flag
{
public:
  Flag(const QString &description,const QString &arg){
    _description = description;
    _arg = arg;
  }

  QString description(){return _description;}
  QString arg(){return _arg;}


private:
  QString _description;
  QString _arg;
};

class  CompilerOption : public QObject
{

public:
  explicit CompilerOption(const QString &text,int defaultFlag = 0,QObject * parent = 0);

  void setText(const QString &text);
  void addFlag(const QString &description, const QString &arg);

  void addBoolFlags(const QString &yesArg, const QString &noArg = QString());
  void addEmptyFlag();

  QString text()const;
  QList<Flag*> flags()const;

  int defaultFlag() const;
  int currentFlag() const;

public slots:
  void setCurrentFlag(int currentFlag);
private:
  QString _text;
  QList<Flag*> _flags;
  int _defaultFlag;
  int _currentFlag;
};

#endif // COMPILEROPTION_H
