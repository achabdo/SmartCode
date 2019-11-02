#include "breakpointwidget.h"
#include "ui_breakpointwidget.h"

#include "breakpoint.h"

BreakPointWidget::BreakPointWidget(BreakPoint *_breakPoint, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::BreakPointWidget)
{
  ui->setupUi(this);
  breakPoint = _breakPoint;

  setup();
}

BreakPointWidget::~BreakPointWidget()
{
  delete ui;
}

void BreakPointWidget::setup()
{
  ui->fileName->setText(breakPoint->fileName());
  ui->line->setText(QString::number(breakPoint->line()));

  BreakPoint::ConditionType condType = breakPoint->conditionType();

  if(condType != BreakPoint::NoCondition)
    {
      ui->conditionGroup->setChecked(true);

      ui->condition->setText(breakPoint->condition());

      ui->condTrueButton->setChecked(condType == BreakPoint::isTrue);
      ui->varChangedButton->setChecked(condType == BreakPoint::VariableChanged);
    }
}

void BreakPointWidget::accept()
{
  QString fileName = ui->fileName->text();

  if(breakPoint->fileName() != fileName)
    breakPoint->setFileName(fileName);

  int line = ui->line->text().toInt();

  if(breakPoint->line() != line)
    breakPoint->setLine(line);

  QString condition = ui->condition->text();

  if(!condition.isEmpty())
    {
      breakPoint->setCondition(condition);

      if(ui->condTrueButton->isChecked())
        breakPoint->setConditionType(BreakPoint::isTrue);
      else
        breakPoint->setConditionType(BreakPoint::VariableChanged);
    }

  QDialog::accept();

}
