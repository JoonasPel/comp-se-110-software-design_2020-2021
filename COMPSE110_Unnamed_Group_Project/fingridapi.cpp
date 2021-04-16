#include "fingridapi.hh"
#include <QString>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>


FinGridAPI::FinGridAPI(QWidget* parent):QWidget(parent)
{
        man=new QNetworkAccessManager(this);
        connect(man,&QNetworkAccessManager::finished,this,&FinGridAPI::downloadFinished);
}

void FinGridAPI::downloadData()
{
    //193:Overall electricity consumption in Finland
    //

    QString variableid="193";
    QString startTime="2021-03-18T22:00:00Z";
    QString endTime="2021-03-19T04:00:00Z";
    QString headerName="x-api-key";
    QString headerValue="4uVZ5S0eNy7TcaGiVZtKf2T9OLDc8UpA1BBqetem";

    QUrl url("https://api.fingrid.fi/v1/variable/"+variableid+"/events/csv?start_time="
             +startTime+"&end_time="+endTime);

    QNetworkRequest request(url);
    request.setRawHeader(headerName.toUtf8(), headerValue.toUtf8());
    man->get(request);
}

void FinGridAPI::downloadFinished(QNetworkReply * reply)
{


    QVariant statuscodeVariant{ reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) };
    int currentStatuscode_ = statuscodeVariant.toInt();

    QByteArray responseContent{ reply->readAll() };
    QString currentContent_ = QString(responseContent);
    qDebug()<<"Koodi:"<<currentStatuscode_;

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonObject root = document.object();

    QByteArrayList list=responseContent.split('\n');
    bool skippedFirst=false;

    QByteArrayList currentItem;

    for(auto i : list){
        if(!skippedFirst){
            skippedFirst=true;
            continue;
        }
        if(i==""){
            continue;
        }
        currentItem=i.split(',');

        if(!currentItem.isEmpty()){
            auto time=currentItem.at(0);
            auto value=currentItem.at(2);

            qDebug()<<"time:"<<time<<"value: "<<value;
        }

    }
}
