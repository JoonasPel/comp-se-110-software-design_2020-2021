#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <QString>
#include <QObject>
#include <QtCharts>
#include <QQmlApplicationEngine>

class DownLoader;

class Model
{
public:
    explicit Model(std::shared_ptr<DownLoader> downloader);

    void fetchData(QString url);
    QList<QPointF> getPointSeries(QString name);
    void renderData(QString chart_name, QString series_name, QQmlApplicationEngine* engine);

private:
    bool XMLparser();

    std::shared_ptr<DownLoader> downloader_;
    std::map<QString,std::vector<QString>> structure_;
    std::map<QString,std::map<QString,QString>> structure2_;
};

#endif // MODEL_H
