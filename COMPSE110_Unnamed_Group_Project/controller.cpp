#include "controller.h"
#include "model.h"

#include <iostream>

Controller::Controller(std::shared_ptr<Model> model, QQmlApplicationEngine *engine,
                       QObject *parent) :
    QObject{parent},
    model_{ model },
    engine_{ engine }
{
}

void Controller::fetchData(QString url, QString place)
{
    model_->fetchData(url, place);
}

// Render weather data to application UI graphs.
void Controller::renderData(QString chart_name, QString series_name)
{
    model_->renderData(chart_name, series_name, engine_);
}
