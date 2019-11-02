#ifndef OPTIONS_H
#define OPTIONS_H

#include  <QDialog>
#include  <QModelIndex>
#include  <QVariant>

class CompilerSetting;
class TextEditBase;

namespace Ui {
  class Options;
}

class Options : public QDialog
{
  Q_OBJECT

public:
  explicit Options(QWidget *parent = 0);
  ~Options();

  void setupCompilerSetting(CompilerSetting * cSetting);
signals:
public slots:
  void accept();

private slots:

  void on_listWidget_clicked(const QModelIndex &index);

  void setLocal(int index);

  void setFormatSourceStyle(int style);

  void on_toolButton_clicked();

private:
  Ui::Options *ui;

  QMap<QString,QVariant> options;

  TextEditBase * textEdit;

  void setup();
};

#endif // OPTIONS_H
