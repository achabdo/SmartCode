#include "setting.h"
#include <QSettings>

Setting::Setting(QObject *parent) : QObject(parent)
{

}

Setting::~Setting()
{

}

QList<int> Setting::load()
{
    QList<int> settingsList;
    QSettings settings;

//    settingsList.append(settings.value("explorer/width"));
//    settingsList.append(settings.value("logs/height"));

    return settingsList;

}

void Setting::save(QList<int> settingsList)
{
    QSettings settings;

    settings.setValue("explorer",settingsList[0]);
    settings.setValue("logs",settingsList[1]);
}
