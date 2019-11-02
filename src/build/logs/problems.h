#ifndef PROBLEMS_H
#define PROBLEMS_H

#include <QTreeWidget>
#include "compiler/message.h"

class Compiler;
class BuildManager;

class  Problems : public QTreeWidget
{
    Q_OBJECT
public:
  explicit Problems(BuildManager *buildManager, QWidget *parent = 0);
  QString getFileAbsolutePath(const QString &fileName) const;
signals:
    void openFile(const QString &fileName,int line,int index);
public slots:
    void addError(const QString &data);
    void findErrorLineNumber(QTreeWidgetItem*item, int);
    void showMessage(const QString &text, const QIcon &icon);
private slots:
    void showMenu();
    void copy();
    void showOutput();
    void addItemMessage(const Message &msg);
private:
    BuildManager *_buildManager;
    Compiler* compiler ;
};

#endif //  PROBLEMS_H
