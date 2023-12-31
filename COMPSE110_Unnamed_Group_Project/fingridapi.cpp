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

void FinGridAPI::downloadData(QString startTime,QString endTime, QString variableid)
{
    //193:Overall electricity consumption in Finland
    //75: windpower hourly data
    //188: nuclear production real time data
    //191: hydropower realtime



    //QString variableid="193";
    //QString startTime="2021-03-18T22:00:00Z";
    //QString endTime="2021-03-19T04:00:00Z";
    QString headerName="x-api-key";
    QString headerValue="4uVZ5S0eNy7TcaGiVZtKf2T9OLDc8UpA1BBqetem";
    QUrl moi;
    //qDebug()<<
    QString urlText;
    if(startTime=="dd-mm-yyyy"||endTime=="dd-mm-yyyy"||startTime==""){
         urlText="https://api.fingrid.fi/v1/variable/"+variableid+"/event/csv";

    }else{
         urlText="https://api.fingrid.fi/v1/variable/"+variableid+"/events/csv?start_time="+startTime+"&end_time="+endTime;
    }
    QUrl url(urlText);


    //QUrl url("https://api.fingrid.fi/v1/variable/193/event/csv");
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

    QString url =reply->url().toString();
    qDebug()<<url;
    auto url2=url.split("/variable/");
    auto url3= url2[1].split("/event");

    QString urlType=url3[0];

    std::map<QString,double> requestData_;

    //QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    //QJsonObject root = document.object();

    QByteArrayList list=responseContent.split('\n');
    bool skippedFirst=false;

    QByteArrayList currentItem;

    for(auto i : list){

        if(!skippedFirst){
            skippedFirst=true;
            continue;
        }

        //checks if item is empty
        if(i==""){
            continue;
        }
        currentItem=i.split(',');

        //adds item to map
        if(!currentItem.isEmpty()){
            auto time=currentItem.at(0);
            auto value=currentItem.at(2);
            requestData_[time]=value.toDouble();
            //qDebug()<<"time:"<<time<<"value: "<<value;
        }
    }
    QString seriesName=getSeriesName(urlType);
    //emit dataIsReady(requestData_,urlType);

    //close reply
    reply->close();


    if(url.size()<52){


        emit currentDataReady(seriesName,requestData_[0]);
        return;
    }
    qDebug()<<"koko on:"<<requestData_.size();
    emit dataIsReady(requestData_,seriesName);


}

QString FinGridAPI::getSeriesName(QString currentType)
{
    QString series_name;
    if(currentType=="193"){
       series_name="totalConsumption";
    }
    else if(currentType=="192"){
       series_name="totalProduction";
    }else if(currentType=="188"){
        series_name="nuclearProduction";
    }else if(currentType=="181"){
        series_name="windProduction";
    }else if(currentType=="191"){
        series_name="waterProduction";
    }else if(currentType=="165"){
        series_name="consumptionForecast";
    }else if(currentType=="242"){
        series_name="productionForecast";
    }
    return series_name;
}
