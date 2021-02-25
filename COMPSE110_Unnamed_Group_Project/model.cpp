#include <QXmlStreamReader>
#include <map>
#include <vector>
#include <QUrlQuery>

#include "model.h"
#include "DownLoader.h"

Model::Model(std::shared_ptr<DownLoader> downloader) :
    downloader_(downloader)
{
}

void Model::fetchData(QString url)
{
    //This is just an example how to use urlModifier and will be removed later!
    std::vector<QString> querys;
    querys.push_back("endtime=2021-02-20T09:00:00Z");
    querys.push_back("place=Kuopio");
    querys.push_back("parameters=t2m");
    QString urlNew = urlModifier(url, querys);

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

    //create QList and append temperatures as Y values. X coords are only 1,2,3...
    QList<QPointF> points;
    float xCoord = 1;
    for(auto dataPoint : structure_)
    {
        QString temperature = dataPoint.second.at("t2m");
        //Convert  QString temperature to double
        double temperatureDouble = temperature.toFloat();

        //Append temperature to QList and increase x-coord value.
        points.append(QPointF(xCoord++, temperatureDouble));
    }

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
        }
    }
    for(auto item: structure_){
        qDebug()<<item.first;
        for(auto element: item.second){
            qDebug()<<element;
        }
        qDebug()<<"";
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
QString Model::urlModifier(QString url, std::vector<QString> querys)
{

    QUrl urlNew(url);
    QUrlQuery query(urlNew.query());

    //Modify every query separately
    for (QString oneQuery : querys) {
        //split oneQuery to separate key and value (ie. {"place", "Tampere"})
        QStringList keyAndValue = oneQuery.split("=");
        //Checks that splitting is succesful.
        if(keyAndValue.length() != 2) {
            qDebug() << "urlModifier FAILED! Error in splitting with '='. "
                        "Expected length 2, got: " << keyAndValue.length();
            return url;
        }
        //Removes old query if it exists
        query.removeQueryItem(keyAndValue[0]);
        //Adds new query (key and value)
        query.addQueryItem(keyAndValue[0], keyAndValue[1]);
    }
    urlNew.setQuery(query);
    qDebug() << urlNew;

    return urlNew.toString();
}
