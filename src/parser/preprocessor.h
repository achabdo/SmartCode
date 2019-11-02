#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <cplusplus/CPlusPlusForwardDeclarations.h>

namespace CPlusPlus
{
class Document;
}

class Preprocessor
{
public:
  Preprocessor();

  void includes(CPlusPlus::Document * doc);
private:
  void relativeInclude();
};

#endif // PREPROCESSOR_H
