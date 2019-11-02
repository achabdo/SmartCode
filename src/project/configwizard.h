#ifndef CONFIGWIZARD_H
#define CONFIGWIZARD_H
#include "project_global.h"

#include <QWizardPage>
class Config;

namespace Ui {
class ConfigWizard;
}

class ConfigManager;

class PROJECTSHARED_EXPORT  ConfigWizard : public QWizardPage
{
    Q_OBJECT
    
public:
    explicit ConfigWizard(ConfigManager *cManager, QWidget *parent = 0);
    ~ConfigWizard();

    void initializePage();
    bool validatePage();

    QList<Config*> configs();

public slots:

private:
    Ui::ConfigWizard *ui;
    ConfigManager *configManager;
};
#endif // CONFIGWIZARD_H
