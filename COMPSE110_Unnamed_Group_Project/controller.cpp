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

// Render weather data to application UI graphs.
void Controller::renderData(QLineSeries *series)
{
    // Coordinates for data points fetched.
    QList<QPointF> points = model_->getPointSeries( series->objectName() );

    if ( series != nullptr ) {
        // Add new points
        series->replace(points);
        series->setPointsVisible(true);

        // Rescale ChartView axis
        QChartView *view = qobject_cast<QChartView*>( series->parent() );

    }
}
