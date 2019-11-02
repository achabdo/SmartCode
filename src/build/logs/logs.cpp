#include "logs.h"

#include <QMenu>
#include <QSettings>

#include "problems.h"
#include "log.h"
#include "debugger/watches.h"
#include "compiler/buildmanager.h"


Logs::Logs(QWidget *parent)
    :   QTabWidget(parent)
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    setAcceptDrops(true);

    connect(this, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(showLogsMenu()));

    setTabsClosable(true);
    setMovable(true);

    BuildManager  * compiler = parentWidget()->findChild<BuildManager*>("BuildManager");

    probl = new Problems(compiler);
    compileLog = new Log;
    appLog = new Log;


    QSettings settings;

    QStringList list = settings.value("Logs").toStringList();

       addTab(probl,tr("Problems"));
       addTab(compileLog,tr("Compile Output"));
       addTab(appLog,tr("Application Output"));


    foreach(QString tab,list)
    {
        if(tab == "Problems")
            addTab(probl,tr("Problems"));
        else  if(tab == "Compile Output")
            addTab(compileLog,tr("Compile Output"));
        else  if(tab == "Application Output")
            addTab(appLog,tr("Application Output"));
    }

    connect(tabBar(),SIGNAL(tabMoved(int,int)),this,SLOT(saveSetting()));

}

Logs::~Logs()
{

}
Log *Logs::compileOutput() const
{
    return compileLog;
}

Log *Logs::appOutput() const
{
    return appLog;
}

Problems * Logs::problems() const
{
    return probl;
}


void Logs::showLogsMenu()
{
    QMenu logsMenu;

    QStringList tabNames;

    tabNames <<tr("Problems") << tr("Compile Output")<< tr("Application Output");

    QSettings settings;


    foreach(QString tab,tabNames)
    {
        QAction * action = new QAction(tab,this);

        action->setCheckable(true);
        action->setChecked(true);
        action->setChecked(settings.value("Logs").toStringList().contains(tab));
        logsMenu.addAction(action);

    }

    connect(&logsMenu,SIGNAL(triggered(QAction*)),this,SLOT(setLogsVisibility(QAction*)));
    logsMenu.exec(QCursor::pos());

}

void Logs::saveSetting()
{
    QSettings settings;

    QStringList list;

    for(int index = 0; index< this->count();index++)
    {
        list << this->tabText(index);
    }
    settings.setValue("Logs",list);

}

void Logs::setLogsVisibility(QAction * action)
{
    if(action->isChecked())
    {
        if(action->text() == tr("Problems"))
            this->addTab(probl,action->text());
        else  if(action->text() == tr("Compile Output"))
            this->addTab(compileLog,action->text());
        else if(action->text() == tr("Application Output"))
            this->addTab(appLog,action->text());
    }
    else
    {
        for(int index = 0; index < this->count(); index ++)
        {
            if(action->text() == tabText(index))
            {
                this->removeTab(index);
            }
        }
    }

    saveSetting();

}
