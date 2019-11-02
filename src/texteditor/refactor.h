#ifndef REFACTOR_H
#define REFACTOR_H

#include <QObject>

class TextEditBase;

class Refactor : public QObject
{
  Q_OBJECT
public:
  explicit Refactor(QObject *parent = 0);

signals:

public slots:
  void setEditor(TextEditBase * editor);

  void addSetter(QString _class, const QString &type, const QString &field);
  void addGetter(QString _class,const QString &type, const QString &field);
  void addGettersAndSetters(QString _class,const QString &type, const QString &field);

  void addDefinition();
  void addDeclaration(const QString &accessType);

  void addConstructorFromSuperClass(const QString &_class, const QString &super_class,
                                    const QMap<QString, QString> &arguments);

  void addInclude(const QString &type);
  void format();
  void correctIndentation();
  void toggleComment();
  void addBlockComment();
  void upperCaseSelection();
  void lowerCaseSelection();
  void surroundWith(const QString &key);
  void addConstructorUsingField(const QString _class, const QString &type, const QString &field);
private:

  void insertComment(int commentType);
  TextEditBase * editor;

  QString editorSelectedText();
  QString generateConstructor(const QString &_class, const QMap<QString, QString> &args);
  QString generateConstructor(const QString &_class ,const QMap<QString,QString> &args
                              ,const QString &content);
  QString addDeclaration(const QString &type, const QString &field);
  QString fieldToMethod(const QString &field);
  QString thisField(const QString &type, const QString &field);
};

#endif // REFACTOR_H
