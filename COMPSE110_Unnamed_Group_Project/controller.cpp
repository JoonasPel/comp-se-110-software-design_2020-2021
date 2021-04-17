#include "controller.h"
#include "model.h"
#include "storage.h"

#include <iostream>
#include "renderelectricitydata.hh"

Controller::Controller(std::shared_ptr<Model> model, std::shared_ptr<Storage> storage, QQmlApplicationEngine *engine,
                       QObject *parent) :
    QObject{parent},
    model_{ model },
    storage_{ storage },
    engine_{ engine }
{
}

void Controller::fetchData(QString url, QString place, QString startTime, QString endTime)
{
    model_->fetchData(url, place, startTime, endTime);

    auto renEl{std::make_shared<renderElectricityData>(engine_)};
    renEl->fetchData(startTime,endTime);


}

// Render weather data to application UI graphs.
void Controller::renderData(QString chart_name, QString series_name)
{
    model_->renderData(chart_name, series_name, engine_);
}

void Controller::editSettingsValue(QString key, QVariant value)
{
    storage_->editValue(key, value);
    return;
}

QVariant Controller::fetchSettingsValue(QString key)
{
    return storage_->fetchValue(key);
}

void Controller::setParameter(QString name, QString value)
{
    model_->setParameter(name, value);
}
