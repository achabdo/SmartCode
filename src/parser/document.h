#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QString>
#include <cplusplus/CPlusPlusForwardDeclarations.h>
#include <cplusplus/Symbol.h>
#include <cplusplus/SymbolVisitor.h>


namespace CPlusPlus
{
  class ScopeFinder: protected SymbolVisitor
  {
    Symbol *root;
    unsigned line;
    unsigned column;
    Scope *symbol;

  public:
    ScopeFinder(Symbol *root)
      : root(root){}

    Scope * scopeAt(int line,int column)
    {
      this->line = line;
      this->column = column;
      this->symbol = 0;
      accept(root);

      return symbol;
    }

    bool preVisit(Symbol * s) {

      if(Scope * scope = s->asScope())
        {
          if((s->line() < line) || (s->line() == line && s->column() <= column))
            {
              symbol = scope;
              return true;
            }
        }

      return false;
    }
  };

  class Document
  {
  public:
    Document(const QString &fileName = QString());

    QString fileName() const;
    Control *control() const;
    TranslationUnit *translationUnit() const;
    Namespace *globalNamespace() const;

    bool parse();

    void setSource(const QByteArray &source);
    QByteArray source() const;
    void setFileName(const QString &fileName);

    QString findFieldType(const QStringList &context, int line, int column);

    static QString typeToString(CPlusPlus::Type * t, QString end = QString());
    static QString symbolName(CPlusPlus::Symbol * s);
    static QString nameToString(const CPlusPlus::Name *name);

  private:
    QString _fileName;
    QByteArray _source;
    Control* _control;
    TranslationUnit* _translationUnit;
    Namespace *_globalNamespace ;


  };
}

#endif // DOCUMENT_H
