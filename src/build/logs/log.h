#ifndef LOG_H
#define LOG_H

#include <build_global.h>
#include <QTextEdit>


class BUILDSHARED_EXPORT Log : public QTextEdit
{
    Q_OBJECT
public:
    explicit Log(QWidget *parent = 0);
signals:
    
public slots:

    void showError(const QString &text);
    void showMessage(const QString &text);
    void showInformation(const QString &text);

private:

      void showMsg(const QString &text, const QColor &color=Qt::black, const QFont &font=QFont());

};
#endif // LOG_H
