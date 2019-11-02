#ifndef DIALOG_H
#define DIALOG_H

#include <QObject>

#include "core_global.h"

class CORESHARED_EXPORT Dialog : public QObject
{
    Q_OBJECT
public:
    explicit Dialog(QObject *parent = 0);

    static int exec(QWidget *parent, const QString &title , const QString &msg, QWidget *widget);
    static QString stringFromMessageBox(QWidget *parent,const QString &title,const QString &message , QString string = QString());
    
signals:
    
public slots:
    
};

#endif // DIALOG_H
