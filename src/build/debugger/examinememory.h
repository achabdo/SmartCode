#ifndef EXAMINEMEMORY_H
#define EXAMINEMEMORY_H

#include <QWidget>

#include "build_global.h"
#include "debugger.h"

namespace Ui {
class ExamineMemory;
}

class BUILDSHARED_EXPORT  ExamineMemory : public QWidget
{
    Q_OBJECT

public:
    explicit ExamineMemory(Debugger *_debugger, QWidget *parent = 0);
    ~ExamineMemory();

private:
    Ui::ExamineMemory *ui;
protected:
private slots:
    void on_examineMemoryButton_clicked();

private:
    Debugger * debugger;
};

#endif // EXAMINEMEMORY_H
