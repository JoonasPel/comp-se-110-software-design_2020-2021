#include <QXmlStreamReader>
#include <map>
#include <vector>
#include <QUrlQuery>
#include <QDateTime>

#include "model.h"
#include "DownLoader.h"
#include "renderelectricitydata.hh"


Model::Model(std::shared_ptr<DownLoader> downloader, QObject* parent) :
    QObject{ parent },
    downloader_(downloader),
    urlFMI_("http://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi::observations::weather::simple&timestep=60&parameters=t2m,ws_10min,n_man")
{
    connect(downloader_.get(), SIGNAL(fetchCompleted()), this, SIGNAL(fetchCompleted()));
}

void Model::fetchData()
{
    QString urlNew = urlModifier(urlFMI_);
    downloader_->load(urlNew);

}

/*
 * Return data points respective to series name
 */
QList<QPointF> Model::getPointSeries(QString name)
{
    //parse file and save to (data structure)
    bool parsingSuccess = XMLparser();
    if(!parsingSuccess)
    {
        qDebug() << "parsing in model.cpp failed(file missing maybe? Fetch FIRST!)";
    }

    QList<QPointF> points;

    QString paramName = "";

    //create QList and append temperatures as Y values. X coords are only 1,2,3...

    float xCoord = 1;
    for(auto dataPoint : structure_)
    {
        QString temperature = dataPoint.second.at(name);
        //Convert  QString temperature to double
        double temperatureDouble = temperature.toFloat();

        //Append temperature to QList and increase x-coord value.
        points.append(QPointF(xCoord++, temperatureDouble));
    }

    return points;
}

void Model::renderData(QString chart_name, QString series_name, QQmlApplicationEngine* engine)
{
    QString paramName = "";

    // Get points by parameter.
    if(series_name == "temperature") { paramName = "t2m"; }
    else if (series_name == "windSpeed") { paramName = "ws_10min"; }
    else if (series_name == "cloudiness") { paramName = "n_man"; }

    // If no proper series is specified do nothing.
    else {
        qDebug() << "No series name specified for model::renderData(), nothing rendered!";
        return;
    }

    // Coordinates for data points fetched.
    QList<QPointF> points = getPointSeries( paramName );

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

void Model::setParameter(QString name, QString value)
{
    parameters_[name] = value;
    qDebug() << "model.cpp parameters_ change:" << name << value;
}

/*
 * //Parse xml file and save data to structure_
 */
bool Model::XMLparser()
{
    auto xmlFile = new QFile("dataFromFMI.xml");
    if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Error opening file in XMLparser";
        return false;
    }
    auto xmlReader = new QXmlStreamReader(xmlFile);

    QString currentTime="";
    QString currentParameterName;

    //Parse the XML until we reach end of it
    while(!xmlReader->atEnd() && !xmlReader->hasError()) {
        // Read next element
        QXmlStreamReader::TokenType token = xmlReader->readNext();
        //If token is just StartDocument - go to next
        if(token == QXmlStreamReader::StartDocument) {
            continue;
        }
        //If token is StartElement - read it
        if(token == QXmlStreamReader::StartElement) {

            if(xmlReader->name() == "ParameterName") {

                currentParameterName=xmlReader->readElementText();


                //qDebug() << currentParameterName;

            }

            if(xmlReader->name() == "ParameterValue") {

                QString value =xmlReader->readElementText();
                structure_[currentTime][currentParameterName]=value;
            }

            if(xmlReader->name() == "Time") {
                auto newTime=xmlReader->readElementText();
                if(currentTime!=newTime){

                    currentTime=newTime;

                    structure_[currentTime]={};
                }
            }
            //Checking if fetching failed and xml file is an expectionreport
            if(xmlReader->name() == "ExceptionText") {

                QString value = xmlReader->readElementText();
                qDebug() << "Fetching error: " << value;
                return false;
            }
        }
    }
    for(auto item: structure_){
        //qDebug()<<item.first;
        for(auto element: item.second){
            //qDebug()<<element;
        }
        //qDebug()<<"";
    }

    if(xmlReader->hasError()) {
        qDebug()<<"XMLparser error";
    }

    //close reader and flush file
    xmlReader->clear();
    xmlFile->close();

    return true;
}

/*
 * Modifies url with given querys and returns modified(new) url
 */
QString Model::urlModifier(QString url)
{
    QUrl urlNew(url);
    QUrlQuery query(urlNew.query());

    //Modify every query separately
    for (auto oneQuery : parameters_) {
        //Removes old query if it exists
        query.removeQueryItem(oneQuery.first);
        //Adds new query (key and value)
        query.addQueryItem(oneQuery.first, oneQuery.second);
    }
    urlNew.setQuery(query);
    qDebug() << urlNew;

    return urlNew.toString();
}
