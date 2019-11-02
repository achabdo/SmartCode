#ifndef INSERTFUNCTIONSWIDGET_H
#define INSERTFUNCTIONSWIDGET_H

#include <QDialog>

class QListWidgetItem;
class ClassParser;

namespace Ui {
class InsertFunctionsWidget;
}

class InsertFunctionsWidget : public QDialog
{
    Q_OBJECT
    
public:
    explicit InsertFunctionsWidget(ClassParser *classParser,const QString &fileName,QWidget *parent = 0);
    ~InsertFunctionsWidget();
signals:
    void methodsSelected(const QStringList &methods);

public slots:
     void accept();
private slots:

    void on_methods_itemActivated(QListWidgetItem *item);

    void on_classes_itemClicked(QListWidgetItem *item);



private:
    Ui::InsertFunctionsWidget *ui;
    ClassParser *clParser;

};

#endif // INSERTFUNCTIONSWIDGET_H
