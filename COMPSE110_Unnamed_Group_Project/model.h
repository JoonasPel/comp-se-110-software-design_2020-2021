#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <QString>
#include <QObject>
#include <QtCharts>
#include <vector>
#include <QQmlApplicationEngine>

class DownLoader;

class Model
{
public:
    explicit Model(std::shared_ptr<DownLoader> downloader);

    void fetchData(QString url, QString place, QString startTime, QString endTime);
    QList<QPointF> getPointSeries(QString name);
    void renderData(QString chart_name, QString series_name, QQmlApplicationEngine* engine);
    void setParameter(QString name, QString value);

private:
    bool XMLparser();
    QString urlModifier(QString, std::vector<QString>);

    std::shared_ptr<DownLoader> downloader_;
    std::map<QString,std::map<QString,QString>> structure_;
    std::map<QString, QString> parameters_;

};

#endif // MODEL_H
