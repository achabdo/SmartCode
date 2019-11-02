#ifndef STARTPAGE_H
#define STARTPAGE_H

#include "core_global.h"

#include <QScrollArea>
#include <QListWidget>
#include <QFileInfo>
#include <QDebug>

namespace Ui {
class StartPage;
}

class CORESHARED_EXPORT StartPage : public QScrollArea
{
    Q_OBJECT
    
public:

    explicit StartPage(QWidget *parent = 0);
    ~StartPage();
    QListWidget* list() const;
    void setupRecentProjectList();
    void  addItems(QListWidget *listWidget, QStringList texts);
private:
    Ui::StartPage *ui;
signals:
    void recentClicked(const QString &projectName);
    void newProject();
    void openProject();
private slots:
void on_listWidget_itemClicked(QListWidgetItem *item);
};

#endif // STARTPAGE_H
