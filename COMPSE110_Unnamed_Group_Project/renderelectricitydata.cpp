#include "renderelectricitydata.hh"
#include <QDebug>

#include <QList>
#include <QPointF>
#include <QtCharts>
#include <QTime>

std::vector<QString> types={"193","191","192","188","181"};
renderElectricityData::renderElectricityData(QQmlApplicationEngine *engine,QWidget* parent)
    :QWidget(parent),engine{engine}
{
    fingrid_=new FinGridAPI();
    connect(fingrid_,&FinGridAPI::dataIsReady,this,&renderElectricityData::render);
    connect(fingrid_,&FinGridAPI::currentDataReady,this,&renderElectricityData::currentValuesReady);

    typeCount=0;
}

void renderElectricityData::fetchData(QString startTime, QString endTime, QString type)
{
    //
    allCurrentData.clear();

    for(auto i : types){
        fingrid_->downloadData(startTime,endTime,i);
    }

    //forecast
    //165: consumption
    //242: A tentative production prediction for the next 24 hours as an hourly energy

    QDateTime time = QDateTime::currentDateTime();
    QString now=time.toString("yyyy-dd-mm")+"T"+time.toString("hh:mm:ss")+"Z";
    auto dayLater=time.addDays(1);
    QString DayLaterText=dayLater.toString("yyyy-dd-mm")+"T"+dayLater.toString("hh:mm:ss")+"Z";

    /**
    std::vector<QString> forecastTypes={"165","242"};
    for(auto j:forecastTypes){
        fingrid_->downloadData(now,DayLaterText,j);
    }
    **/
}

void renderElectricityData::getCurrentValues()
{
    for(auto i:types){
        fingrid_->downloadData("","",i);
    }

}

void renderElectricityData::currentValuesReady(QString type, double value)
{
    qDebug()<<"currentti"<<type<<value;
}

void renderElectricityData::render(std::map<QString,double> dataPoints,QString series_name)
{

    allCurrentData[series_name]=dataPoints;

    qDebug()<<"Ei saatana tää toimi!";
    //auto data=fingrid_->giveRequestData();

    auto points=getPointSeries(dataPoints);
    //QString currentType=urlType;


   /**
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
    }
    **/

    //qDebug()<<"current type:"<<currentType;

    addToChart(series_name,points);


}

QList<QPointF> renderElectricityData::getPointSeries(std::map<QString, double> data)
{
    QList<QPointF> points;

    QString paramName = "";

    //create QList and append temperatures as Y values. X coords are only 1,2,3...

    float xCoord = 1;
    for(auto dataPoint : data)
    {
        double value = dataPoint.second;
        if(value==0){
            ++xCoord;
            continue;
        }
        //Append temperature to QList and increase x-coord value.
        points.append(QPointF(xCoord++, value));
    }
    return points;
}

void renderElectricityData::calcPercent()
{
    auto total=allCurrentData["193"];
    std::vector<QString> listProduction={"188","181","191"};
    double value;

    std::map<QString, double> currentPercent;

    //goes through nuclear, wind, hydro
    for(auto i :listProduction){

        qDebug()<<"nyt on :"<<i;
        for(auto j: allCurrentData[i]){
            value=j.second/total[j.first]*100;
            //qDebug()<<value<<"% koko tuotannosta";
            currentPercent[j.first]=value;
        }
        allCurrentData[i+"percent"]=currentPercent;
        auto points=getPointSeries(currentPercent);
        currentPercent.clear();
    }
}

void renderElectricityData::addToChart(QString series_name, QList<QPointF> points)
{
    QString chart_name="consumptionGraph";
    //series_name="totalConsumption";

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
    //QLineSeries* lseries = qobject_cast<QLineSeries*>(series);

    // Add new points

    //lseries->replace(points);
    //lseries->setPointsVisible(true);

    if(allCurrentData.size()==7){
        calcPercent();
    }
}
