#ifndef BREAKPOINTWIDGET_H
#define BREAKPOINTWIDGET_H

#include <QDialog>

class BreakPoint;

namespace Ui {
  class BreakPointWidget;
}

class BreakPointWidget : public QDialog
{
  Q_OBJECT

public:

  explicit BreakPointWidget(BreakPoint* _breakPoint, QWidget *parent = 0);
  ~BreakPointWidget();

public slots:
  void accept();
private:
  Ui::BreakPointWidget *ui;

  BreakPoint * breakPoint;
  void setup();
};

#endif // BREAKPOINTWIDGET_H
