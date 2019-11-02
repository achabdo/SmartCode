#ifndef RECENTS_H
#define RECENTS_H
#include "core_global.h"

#include <QObject>
#include <QMenu>
#include <QSettings>

class QAction;

class CORESHARED_EXPORT Recents : public QObject
{
    Q_OBJECT
public:
    explicit Recents(QObject *parent=0);
    void setCurrentRecent(const QString &recentName);
    void set(QMenu *m);
    void updateRecentActions();
    void setKey(const QString &newKey);
    void remove(const QString &recent);
public slots:
    void clear();
private:
    QString curRecent;
    enum {MaxRecents = 10};
    QAction *recentActs[MaxRecents];
    QAction * clearMenuAct ;
    QMenu *menu;
    QString key;
};

#endif // Recents_H
