#include "examinememory.h"
#include "ui_examinememory.h"

ExamineMemory::ExamineMemory(Debugger * _debugger, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExamineMemory)
{
    debugger = _debugger;
    ui->setupUi(this);
}

ExamineMemory::~ExamineMemory()
{
    delete ui;
}

void ExamineMemory::on_examineMemoryButton_clicked()
{
    ui->memoryLog->setText(debugger->executeAndRead(QString("x/3uh %1").arg(ui->adresse->text())));
}
