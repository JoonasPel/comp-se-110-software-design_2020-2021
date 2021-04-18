#include "fmiAPI.h"
#include <QLabel>
#include <QtDebug>
#include <QFile>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QFormLayout>
#include <QXmlStreamReader>
#include <QUrlQuery>

fmiAPI::fmiAPI(QWidget *parent)
    : QWidget(parent)
{
    urlFMI = ("https://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi::observations::weather::simple&timestep=60&parameters=t2m,ws_10min,n_man");
    urlFMIforeCast = ("https://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi::forecast::harmonie::surface::point::simple&timestep=30&eparameters=temperature");

    form = new QFormLayout(this);
    network = new QNetworkAccessManager(this);
    connect(network, &QNetworkAccessManager::finished, this, &fmiAPI::downloadCompleted);
}

void fmiAPI::load(std::map<QString, QString> parameters)
{
    fetchType_ = "normal";

    QString urlNew = urlModifier(parameters, urlFMI);

    network->get(QNetworkRequest(urlNew));
}

void fmiAPI::loadforeCast(std::map<QString, QString> parameters)
{
    fetchType_ = "forecast";

    //Construct date now and date after 24 hours
    QDateTime timeNow = QDateTime::currentDateTimeUtc();
    QString timeNowStr = QDateTime::currentDateTimeUtc().toString(Qt::ISODate);
    QDateTime dayLater = timeNow.addDays(1);
    QString daylaterStr = dayLater.toString(Qt::ISODate);

    parameters["starttime"] = timeNowStr;
    parameters["endtime"] = daylaterStr;

    QString urlNew = urlModifier(parameters, urlFMIforeCast);
    network->get(QNetworkRequest(urlNew));
}


void fmiAPI::downloadCompleted(QNetworkReply *reply)
{

    // Parse data and save to structure
    bool parsingSuccess = XMLparser(reply);
    reply->deleteLater();

    if(!parsingSuccess) {
        qDebug() << "parsing in fmiAPI failed";
    } else {
        qDebug() << "Fetching ready!";
        emit fetchCompleted(structure_, fetchType_);
    }
}

/*
 * //Parse xml file and save data to structure_
 */
bool fmiAPI::XMLparser(QNetworkReply *reply)
{
    auto xmlReader = new QXmlStreamReader(reply);

    QString currentTime="";
    QString currentParameterName;
    structure_.clear();

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
            //Checking if fetching failed and xml file is an expectionreport
            if(xmlReader->name() == "ExceptionText") {

                QString value = xmlReader->readElementText();
                qDebug() << "Fetching error: " << value;
                return false;
            }
        }
    }

    if(xmlReader->hasError()) {
        qDebug()<<"XMLparser (fmiAPI) error";
    }

    xmlReader->clear();

    return true;
}

/*
 * Modifies url with given querys and returns modified(new) url
 */
QString fmiAPI::urlModifier(std::map<QString, QString> parameters, QString url)
{
    QUrl urlNew(url);
    QUrlQuery query(urlNew.query());

    //Modify every query separately
    for (auto oneQuery : parameters) {
        //Removes old query if it exists
        query.removeQueryItem(oneQuery.first);
        //Adds new query (key and value)
        query.addQueryItem(oneQuery.first, oneQuery.second);
    }
    urlNew.setQuery(query);
    qDebug() << urlNew;

    return urlNew.toString();
}
