#ifndef RENDERELECTRICITYDATA_HH
#define RENDERELECTRICITYDATA_HH


#include <QWidget>
#include <fingridapi.hh>
#include <vector>
#include <QQmlApplicationEngine>

class renderElectricityData: public QWidget
{
    Q_OBJECT

public:
    renderElectricityData(QQmlApplicationEngine *engine,QWidget* parent = nullptr);
    void fetchData(QString startTime, QString endTime,QString type="");
    

public slots:
    void render(std::map<QString,double> dataPoints,QString urlType);
    

private:
    QList<QPointF> getPointSeries(std::map<QString,double> data);
    void calcPercent();
    void addToChart(QString series_name,QList<QPointF> points);

    FinGridAPI* fingrid_;
    QQmlApplicationEngine* engine;
    std::vector<QString> typeList;
    int typeCount;

    std::map<QString,std::map<QString,double>> allCurrentData;

};


#endif // RENDERELECTRICITYDATA_HH
