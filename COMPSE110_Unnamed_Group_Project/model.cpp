#include "model.h"
#include "DownLoader.h"

Model::Model(std::shared_ptr<DownLoader> downloader) :
    downloader_(downloader)
{
}

void Model::fetchData(QString url)
{
    downloader_->load(url);
}

/*
 * Return data points respective to series name
 */
QList<QPointF> Model::getPointSeries(QString name)
{
    // -- WIP --
    QList<QPointF> points = {QPoint(1, 1), QPoint(2, 3), QPoint(3, 3), QPoint(25, 16), QPoint(32, 19), QPoint(43, 29), QPoint(65, 14), QPoint(123, 24), QPoint(143, 29)};

    return points;
}

void Model::renderData(QString chart_name, QString series_name, QQmlApplicationEngine* engine)
{
    // Coordinates for data points fetched.
    QList<QPointF> points = getPointSeries( series_name );

    QObject *view = engine->rootObjects().at(0)->findChild<QObject*>(chart_name);
    QAbstractSeries* series = nullptr;
    QAbstractSeries* target_series = nullptr;

    int count = view->property("count").toInt();

    // Find wanted series by name.
    if (view != nullptr) {
        for(int i = 0; i < count; i++) {
            QMetaObject::invokeMethod(view, "series", Qt::AutoConnection, Q_RETURN_ARG(QAbstractSeries*, series), Q_ARG(int, i));
            if (series->objectName() == series_name) {
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
}



