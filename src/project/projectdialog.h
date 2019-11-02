#ifndef PROJECTDIALOG_H
#define PROJECTDIALOG_H
#include "project_global.h"

#include <QDialog>
#include <QListWidget>
#include <QDir>

namespace Ui {
class ProjectDialog;
}

class PROJECTSHARED_EXPORT ProjectDialog : public QDialog
{
    Q_OBJECT
    
public:

    enum NewType {NewProject ,NewFile ,AllTypes};

    explicit ProjectDialog(QWidget *parent = 0);
    ~ProjectDialog();

    void setItems(NewType newType);

signals:
    void templateSelected(const QString &templat);

public slots:
    void accept();
private slots:

    void on_listWidget_clicked(const QModelIndex &index);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_listWidget_2_itemClicked(QListWidgetItem *item);

    void on_listWidget_2_itemDoubleClicked(QListWidgetItem *item);

private:

    QString newType();

    Ui::ProjectDialog *ui;

};

#endif // PROJECTDIALOG_H
