#ifndef CLASSVIEW_H
#define CLASSVIEW_H

#include <cplusplus/SymbolVisitor.h>
#include <cplusplus/ASTVisitor.h>

#include <QStandardItem>

namespace CPlusPlus {
class Document;
}

class ClassView : public  CPlusPlus::SymbolVisitor
{
public:
  enum IconType
  {
    NamespaceIcon,
    UsingNamespaceDirectiveIcon,
    ClassIcon,
    StructIcon,
    UnionIcon,
    TemplateIcon,
    PublicFunctionIcon,
    ProtectedFunctionIcon,
    PrivateFunctionIcon,
    PublicDeclarationIcon,
    ProtectedDeclarationIcon,
    PrivateDeclarationIcon,
    EnumIcon,
    PublicEnumIcon,
    ProtectedEnumIcon,
    PrivateEnumIcon,
  };

  ClassView();

  void parse(CPlusPlus::Document * doc,QStandardItem * parent);

  bool preVisit(CPlusPlus::Symbol *s);
  void postVisit(CPlusPlus::Symbol * s);

private:
  QList<QStandardItem*> items;

  QIcon itemIcon(IconType type);
};

#endif // CLASSVIEW_H
