#include <QXmlStreamReader>
#include <map>
#include <vector>

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
    //parse file and save to (data structure)
    bool parsingSuccess = XMLparser();
    if(!parsingSuccess)
    {
        qDebug() << "parsing in model.cpp failed(file missing maybe? Fetch FIRST!)";
    }

    //create QList and append temperatures as Y values. X values are only 1,2,3...
    QList<QPointF> points;
    float x_value = 0;
    for(auto DataPoint : structure2_)
    {
        QString temperature = DataPoint.second.at("t2m");
        //Convert  QString temperature to double
        double temperatureDouble = temperature.toFloat();
        //change temperature from negative to positive
        temperatureDouble = fabs(temperatureDouble);

        //Append temperature to QList and increase x-coord value.
        x_value++;
        points.append(QPointF(x_value, temperatureDouble));
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

bool Model::XMLparser()
{
    //Check if data file exists (downloaded in DownLoader)
    bool fileExists = QFile::exists("dataFromFMI.xml");
    if(!fileExists){ return false; }

    //Parse xml file and save data to structure2_

    auto xmlFile = new QFile("dataFromFMI.xml");
    if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
                        qDebug()<<"Error";
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
                            qDebug()<<currentParameterName;
                            //structure[currentTime].push_back(value);
                        }

                        if(xmlReader->name() == "ParameterValue") {

                            QString value =xmlReader->readElementText();
                            structure_[currentTime].push_back(value);
                            structure2_[currentTime][currentParameterName]=value;
                        }
                        if(xmlReader->name() == "Time") {
                            auto newTime=xmlReader->readElementText();
                            if(currentTime!=newTime){

                                currentTime=newTime;

                                structure_[currentTime]={};
                                structure2_[currentTime]={};
                            }
                        }
                }
        }
        for(auto item: structure2_){
                qDebug()<<item.first;
                //qDebug()<<"koko on "<<item.second.size();
                for(auto element: item.second){
                    qDebug()<<element;
                }
                qDebug()<<"";
        }

        if(xmlReader->hasError()) {
                    qDebug()<<"se on error";
        }

        //close reader and flush file
        xmlReader->clear();
        xmlFile->close();

        return true;
}



