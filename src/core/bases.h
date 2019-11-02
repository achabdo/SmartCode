#ifndef BASES_H
#define BASES_H

#include "core_global.h"

#include <QFileInfo>
#include <QDir>
#include <QVariant>

class CORESHARED_EXPORT Bases
{

public:
  static QString headerSource(const QString &fileName);

  static QRegExp sourceFilesReg() ;
  static QRegExp headerFilesReg();
  static QRegExp resourceFilesReg() ;
  static QRegExp otherFilesReg() ;

  static bool out(const QString &fileName,const QString &text);

  static inline QString baseName(const QString &fileName)
  {
    return QFileInfo(fileName).baseName();
  }

  static inline QString baseNamePath(const QString &fileName)
  {
    return QFileInfo(fileName).path()+"/" +QFileInfo(fileName).baseName();
  }

  static inline QString fileSuffix(const QString &fileName)
  {
    return QFileInfo(fileName).suffix();
  }

  static inline QString relativeFilePath(const QString &fileName,const QString &otherFileName)
  {
    return QDir(fileName).relativeFilePath(otherFileName);
  }

  static inline QString path(const QString &fileName)
  {
    return QFileInfo(fileName).path();
  }

  static inline QString fileName(const QString &fileName)
  {
    return QFileInfo(fileName).fileName();
  }

  static inline QString variant2String(const QVariant &variant) {return variant.toString();}

  static inline QStringList variant2StringList(const QVariant &variant){return variant.toStringList();}

  static inline QVariant settingVariant(const QList<QVariant> &list,int type) {return list[type];}

  static bool isSourceFile(const QString &fileName);
  static bool isHeaderFile(const QString &fileName);
  static bool isResourceFile(const QString &fileName);
  static bool isOtherFile(const QString &fileName);
private:
  Bases();
  ~Bases();
};

#endif // BASES_H
