#ifndef LEXERSTYLE_H
#define LEXERSTYLE_H

#include "texteditor_global.h"

#include <QObject>

#include <QColor>
#include <QFont>
#include <QHash>
#include <QDomElement>

#define MAXSTYLE 24

class TEXTEDITORSHARED_EXPORT LexerStyle : public QObject
{
    Q_OBJECT
public:
    explicit LexerStyle(QObject *parent = 0);

    void load(const QString &fileName);
    void save(const QString &styleName,const QString &fontName,int fontSize,
              QList<QColor> foregroundColors,QList<QColor> backgroundColors,
              QList<QFont> Fonts);

    QColor backgroundColor(int style);
    QColor foregroundColor(int style);

    QFont font(int style);

    QString styleName(int style) const;

signals:
     void foregroundColorChanged(const QColor &color,int style);
     void backgroundColorChanged(const QColor &color,int style);
     void fontChanged(const QFont &color,int style);

public slots:

private:
    QColor readColor(QDomElement option);
    void addColor(QDomElement &option, const QColor &color);

    QList<QColor> foregColors;
    QList<QColor> backgColors;

    QList<QFont> fonts;

};

#endif // LEXERSTYLE_H
