#include <map>
#include <vector>
#include <QDateTime>

#include "model.h"
#include "fmiAPI.h"


Model::Model(std::shared_ptr<fmiAPI> fmiapi, QObject* parent) :
    QObject{ parent },
    fmiapi_(fmiapi)
{
    connect(fmiapi_.get(), SIGNAL(fetchCompleted()), this, SIGNAL(fetchCompleted()));
}

void Model::fetchData()
{
    fmiapi_->load(parameters_);
}

void Model::setParameter(QString name, QString value)
{
    parameters_[name] = value;
    qDebug() << "model.cpp parameters_ change:" << name << value;
}

/*
 * Return data points respective to series name
 */
//QList<QPointF> Model::getPointSeries(QString name)
//{
//    //parse file and save to (data structure)
//    bool parsingSuccess = XMLparser();
//    if(!parsingSuccess)
//    {
//        qDebug() << "parsing in model.cpp failed(file missing maybe? Fetch FIRST!)";
//    }

//    QList<QPointF> points;

//    QString paramName = "";

//    //create QList and append temperatures as Y values. X coords are only 1,2,3...

//    float xCoord = 1;
//    for(auto dataPoint : structure_)
//    {
//        QString temperature = dataPoint.second.at(name);
//        //Convert  QString temperature to double
//        double temperatureDouble = temperature.toFloat();

//        //Append temperature to QList and increase x-coord value.
//        points.append(QPointF(xCoord++, temperatureDouble));
//    }

//    return points;
//}

//void Model::renderData(QString chart_name, QString series_name, QQmlApplicationEngine* engine)
//{
//    QString paramName = "";

//    // Get points by parameter.
//    if(series_name == "temperature") { paramName = "t2m"; }
//    else if (series_name == "windSpeed") { paramName = "ws_10min"; }
//    else if (series_name == "cloudiness") { paramName = "n_man"; }

//    // If no proper series is specified do nothing.
//    else {
//        qDebug() << "No series name specified for model::renderData(), nothing rendered!";
//        return;
//    }

//    // Coordinates for data points fetched.
//    QList<QPointF> points = getPointSeries( paramName );

//    QObject *view = engine->rootObjects().at(0)->findChild<QObject*>(chart_name);
//    QAbstractSeries* series = nullptr;
//    QAbstractSeries* target_series = nullptr;

//    int count = view->property("count").toInt();

//    // Find wanted series by name.
//    if (view != nullptr) {
//        for(int i = 0; i < count; i++) {
//            QMetaObject::invokeMethod(view, "series", Qt::AutoConnection, Q_RETURN_ARG(QAbstractSeries*, series), Q_ARG(int, i));
//            if (series->objectName() == series_name) {
//                target_series = series;
//                break;
//            }
//        }
//    }
//    // If series was found replace its points with fetched.
//    if ( target_series != nullptr ) {

//        QLineSeries* lseries = qobject_cast<QLineSeries*>(series);

//        // Add new points
//        lseries->replace(points);
//        lseries->setPointsVisible(true);
//    }
//}
