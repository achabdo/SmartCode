#ifndef COMPILEPROGRESSBAR_H
#define COMPILEPROGRESSBAR_H

#include <QProgressBar>

class CompileProgressBar : public QProgressBar
{
public:
    CompileProgressBar(QWidget * parent = 0);
    ~CompileProgressBar();
};

#endif // COMPILEPROGRESSBAR_H
