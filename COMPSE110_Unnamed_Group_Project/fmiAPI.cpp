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
    form = new QFormLayout(this);
    network = new QNetworkAccessManager(this);
    connect(network, &QNetworkAccessManager::finished, this, &fmiAPI::downloadCompleted);
}

void fmiAPI::load(std::map<QString, QString> parameters)
{
    QString urlNew = urlModifier(parameters);

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
        emit fetchCompleted(structure_);
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
QString fmiAPI::urlModifier(std::map<QString, QString> parameters)
{
    QUrl urlNew(urlFMI);
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
