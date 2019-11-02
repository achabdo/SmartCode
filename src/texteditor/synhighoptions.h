#ifndef SYNHIGHOPTIONS_H
#define SYNHIGHOPTIONS_H

#include "texteditor_global.h"

#include <QWidget>
#include <QColorDialog>
#include <QModelIndex>

namespace Ui {
class SynHighOptions;
}

class LexerStyle;

class TEXTEDITORSHARED_EXPORT SynHighOptions : public QWidget
{
    Q_OBJECT
    
public:
    explicit SynHighOptions(LexerStyle * lexerStyle, QWidget *parent= 0);
    ~SynHighOptions();

     QColor selectColor(QPushButton *button, const QColor &c = QColorDialog::getColor());

private slots:
    void on_forg_clicked();

    void on_back_clicked();

    void on_style_clicked(const QModelIndex &index);

    void userAccept();

    void on_bold_clicked(bool checked);

    void on_italic_clicked(bool checked);

    void on_underline_clicked(bool checked);

private:
    void setup();

    void setFontSizeValue(int fontSize);
    void checkFont(bool bold,bool italic,bool underline);

    LexerStyle *lexStyle;

    Ui::SynHighOptions * ui;

    QList<QColor> bgColors;
    QList<QColor> fgColors;
    QList<QFont> fonts;

    int currentStyle();
    void updateFont(int bold,int italic =-1 , int underLine = -1);

};
#endif // SYNHIGHOPTIONS_H
