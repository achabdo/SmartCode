// Copyright (C) 2014  by Achrouf Abdeour <achroufabdenour@gmail.com>
// Auteur Achrouf Abdenour

// This File is part of SmartCode

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program. If not, see http://www.gnu.org/licenses/.

#include "qtapp.h"
#include <bases.h>
#include <project.h>

#include "core_constants.h"
const char QT[]        = "QT";
const char QTEMPLATE[] = "TEMAPLATE";
const char QCONFIG[]   = "CONFIG";
const char QTARGET[]   = "TARGET";
const char QSOURCES[]  = "SOURCES";
const char QHEADERS[]  = "HEADERS";
const char QLIBS[]     = "LIBS";
const char QINCS[]     = "INCLUDEPATH";
const char ps[]        = " += ";
const char eq[]        = " = ";

QtApp::QtApp(QObject *parent) :
    QObject(parent)
{

}

void QtApp::setQmake(const QString &qtProject)
{
    QProcess * qmake = new QProcess;
    //qmake->setWorkingDirectory("C:/smart");
    qmake->start("qmake.exe",QStringList()<<"-makefile"<<qtProject);
}

void QtApp::import(const QString &pro)
{
    QHash<QString,QVariant> smcProject;

    QStringList src,h,incs,libs;
    QFile f(pro);

    if(!f.open(QFile::ReadOnly))
        return ;

    QString content = f.readAll();

    QStringList configs = content.split("\n");

    f.close();

    QString text;

    foreach(QString config,configs)
    {
        if(config.contains(QSOURCES))
        {
            //            while(config.endsWith("\") )
            //            {
            //                                  C
            //        }
        }
        else
        {
            if(config.contains(QTEMPLATE))
                smcProject.insert(Core::Project::TEMPLATE, optionFromLine(config));
            else if(config.contains(QTARGET))
                smcProject.insert(Core::Project::TARGET, optionFromLine(config));
        }
    }


//    Project::writeProject(Text::baseNamePath(pro) + ".smc" , smcProject);

}

QString QtApp::optionFromLine(const QString &line)
{
    return line.right(line.indexOf("=")).trimmed();
}

QStringList QtApp::pathsFromConfig(const QString &pro)
{
    return pro.split("/");
}

void QtApp::QtProjectFromSMC(Project * project)
{
//    QString pro;

//    if(!project->load())
//        return ;

//    pro+=setConfg(QT,eq,QStringList()<<"core");
//    pro+=setConfg(QTARGET,eq,QStringList()<<project->currentConfiguration()->target());
//    pro+=setConfg(QTEMPLATE,eq,QStringList()<<QString::number(project->currentConfiguration()->toTemplate()));
//    pro+=setConfg(QSOURCES,ps,project->stringList(SOURCES)());
//    pro+=setConfg(QHEADERS,ps,project->stringList(HEADERS));
//    pro+=setConfg(QINCS,ps,project->currentConfiguration()->includes());
//    pro+=setConfg(QLIBS,ps,project->currentConfiguration()->libs());

//    Bases::out(project->path()+".pro",pro);
}

void QtApp::start(const QString &proFile)
{
    QProcess proc;
    proc.start("qmake.exe",QStringList()<<"-makefile"<<proFile);
}

QString QtApp::setConfg(const QString &confg,const QString &opr,const QStringList &paths)
{
    return confg+opr+paths.join("\\\n\t")+"\n";
}

