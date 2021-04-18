#include "controller.h"
#include "model.h"
#include "storage.h"

#include <iostream>
//#include "renderelectricitydata.hh"

Controller::Controller(std::shared_ptr<Model> model, std::shared_ptr<Storage> storage, QQmlApplicationEngine *engine,
                       QObject *parent) :
    QObject{parent},
    model_{ model },
    storage_{ storage },
    engine_{ engine }
{
    connect(model_.get(), SIGNAL(fetchCompleted()), this, SIGNAL(fetchCompleted()));
    connect(model_.get(), SIGNAL(forecastCompleted()), this, SIGNAL(forecastCompleted()));
    connected = false;
}

void Controller::fetchData()
{
    if(!connected) {
        connectSignal();
    }

    model_->fetchData();
}

void Controller::fetchForecast()
{
    if(!forecastConnected) {
        connectForecastSignal();
    }

    model_->fetchForecast();
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

void Controller::connectSignal()
{
    connected = true;
    connect(this, SIGNAL(fetchCompleted()), engine_->rootObjects().at(0)->findChild<QObject*>("fetchButton"), SIGNAL(renderData()));
}

void Controller::connectForecastSignal()
{
    forecastConnected = true;
    connect(this, SIGNAL(forecastCompleted()), engine_->rootObjects().at(0)->findChild<QObject*>("fetchForecast"), SIGNAL(renderForecast()));
}
