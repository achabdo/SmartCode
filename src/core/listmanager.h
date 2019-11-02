#ifndef LISTMANAGER_H
#define LISTMANAGER_H
#include "gui_global.h"
#include <QObject>
#include <QStringList>
#include <QLineEdit>
#include <QListWidget>

class GUISHARED_EXPORT ListManager : public QObject
{
    Q_OBJECT
public:
    explicit ListManager(QObject *parent = 0);
    static void addItem();
    void deleteItem();
    void editItem();
    void clear();
    void addFile();
signals:
    
public slots:
private:
   QListWidget *listWidget;

   QLineEdit *edit;
   QStringList list;
};

#endif // LISTMANAGER_H
