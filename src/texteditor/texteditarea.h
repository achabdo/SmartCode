#ifndef TEXTEDITAREA_H
#define TEXTEDITAREA_H

#include "texteditor_global.h"

#include <QWidget>

class TextEdit;
class QComboBox;
class QStandardItem;

class TEXTEDITORSHARED_EXPORT TextEditArea : public QWidget
{
  Q_OBJECT
public:
  enum DataType{Text,Image};

  explicit TextEditArea(const QString &fileName , DataType dataType = Text, QWidget *parent = 0);

  void setFileItem(QStandardItem *item);


signals:

public slots:
  void upadteNmcClsStrList(const QStringList &items);
  void upadteMethodsVarsList(const QString &context);
private :

  void createTextArea(const QString &fileName);
  void createImageArea(const QString &fileName);

  friend class TabWidget;

  TextEdit * textEdit;

  QComboBox * nmcClsStrList;
  QComboBox * methodsVarsList;

  QStandardItem * fileItem;

  void parseItem(QStandardItem *item, const QStandardItem *fileItem, QStringList &list);
};



#endif // TEXTEDITAREA_H
