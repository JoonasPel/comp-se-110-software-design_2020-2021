#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <QString>
#include <QObject>
#include <QtCharts>
#include <vector>
#include <QQmlApplicationEngine>

class fmiAPI;
class renderElectricityData;
class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(std::shared_ptr<fmiAPI> downloader,std::shared_ptr<renderElectricityData> elecData, QObject *parent = nullptr);

    void fetchData();
    void fetchForecast();
    QList<QPointF> getPointSeries(QString name);
    void renderData(QString chart_name, QString series_name, QQmlApplicationEngine* engine);
    void setParameter(QString name, QString value);

signals:
    void fetchCompleted();
    void forecastCompleted();

public slots:
    void fetchedDataReady(std::map<QString,std::map<QString,QString>>, QString);

private:
    QString urlModifier(QString);

    std::shared_ptr<fmiAPI> fmiapi_;
    std::map<QString, QString> parameters_;
    std::map<QString,std::map<QString,QString>> fmiData_;
    std::shared_ptr<renderElectricityData> elecData_;

};

#endif // MODEL_H
