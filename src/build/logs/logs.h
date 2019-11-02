#ifndef LOGS_H
#define LOGS_H

#include "build_global.h"

#include <QTabWidget>

class Log;
class Watches;
class Problems;

class BUILDSHARED_EXPORT Logs : public QTabWidget
{
 Q_OBJECT
public:
    Logs(QWidget * parent = 0);
    ~Logs();

    Log *appOutput()const;
    Log *compileOutput()const;

    Problems *problems() const;
public slots:

private slots:
    void showLogsMenu();
    void setLogsVisibility(QAction *action);
     void saveSetting();
private:

    Problems *probl;
    Log *appLog;
    Log *compileLog;

};

#endif // LOGS_H
