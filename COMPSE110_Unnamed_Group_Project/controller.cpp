#include "controller.h"
#include "model.h"

Controller::Controller(std::shared_ptr<Model> model,
                       QObject *parent) :
    QObject{parent},
    model_{ model }
{
}

void Controller::fetchData(QString url)
{
    model_->fetchData(url);
}
