#ifndef SETTING_H
#define SETTING_H

#include <QObject>

class Setting : public QObject
{
    Q_OBJECT
public:

    explicit Setting(QObject *parent = 0);
    ~Setting();

    QList<int> load();
    void save(QList<int> settingsList);
signals:

public slots:
};

#endif // SETTING_H
