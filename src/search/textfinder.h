#ifndef TEXTFINDER_H
#define TEXTFINDER_H

#include "search_global.h"

#include <QDockWidget>
#include <QSettings>
#include <QMenu>
#include <QAction>

class TabWidget;
class AdvancedSearch;

namespace Ui {
class TextFinder;
}

class SEARCHSHARED_EXPORT TextFinder : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit TextFinder(TabWidget *myEditor , QWidget *parent = 0);
    ~TextFinder();

signals:
    void advandeSearch();
public slots:
private slots:
    void getRecentFinds();
    void on_next_clicked();

    void on_prev_clicked();

    void on_ReplaceAll_clicked();
    void on_Replace_clicked();

    void showFindOptionMenu();


    void setCaseSensitive(bool _caseSensitive);
    void setwholeWords(bool _wholeWords);
    void setRegularExp(bool _regularExp);

private:
    void Find(bool forward, int line =-1);

    void setup();

    Ui::TextFinder *ui;
    TabWidget * editor;

    bool caseSensitive;
    bool wholeWords;
    bool regularExp;
};

#endif // TEXTFINDER_H
