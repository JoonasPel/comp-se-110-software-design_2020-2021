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

void Controller::fetchData(QString url)
{
    model_->fetchData(url);
}

// Render weather data to application UI graphs.
void Controller::renderData(QString chart_name, QString ser_name)
{
    // Coordinates for data points fetched.
    QList<QPointF> points = model_->getPointSeries( ser_name );

    QObject *view = engine_->rootObjects().at(0)->findChild<QObject*>(chart_name);
    QAbstractSeries* series = nullptr;
    QAbstractSeries* target_series = nullptr;

    int count = view->property("count").toInt();

    // Find wanted series by name.
    if (view != nullptr) {
        for(int i = 0; i < count; i++) {
            QMetaObject::invokeMethod(view, "series", Qt::AutoConnection, Q_RETURN_ARG(QAbstractSeries*, series), Q_ARG(int, i));
            if (series->objectName() == ser_name) {
                target_series = series;
                break;
            }
        }
    }

    // If series was found replace its points with fetched.
    if ( target_series != nullptr ) {

        QLineSeries* lseries = qobject_cast<QLineSeries*>(series);

        // Add new points
        lseries->replace(points);
        lseries->setPointsVisible(true);
    }
    else {
        engine_->rootObjects().at(0)->setProperty("color", "red");
    }
}
