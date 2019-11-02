#ifndef WORDGENERATOR_H
#define WORDGENERATOR_H

#include <QObject>

class WordGenerator : public QObject
{
    Q_OBJECT
public:
    explicit WordGenerator(QObject *parent = 0);
    ~WordGenerator();

    void generate(const QString &str);

signals:

public slots:
};

#endif // WORDGENERATOR_H
