#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <QString>
#include <QObject>
#include <QtCharts>
#include <vector>
#include <QQmlApplicationEngine>

class fmiAPI;

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(std::shared_ptr<fmiAPI> downloader, QObject *parent = nullptr);

    void fetchData();
    QList<QPointF> getPointSeries(QString name);
    void renderData(QString chart_name, QString series_name, QQmlApplicationEngine* engine);
    void setParameter(QString name, QString value);

signals:
    void fetchCompleted();

private:
    QString urlModifier(QString);

    std::shared_ptr<fmiAPI> fmiapi_;
    std::map<QString, QString> parameters_;

};

#endif // MODEL_H
