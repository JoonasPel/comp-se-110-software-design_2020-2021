#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <QObject>

#include <QtCharts>
#include <QQmlApplicationEngine>
#include <QMetaObject>

#include "storage.h"

class Model;
class Storage;

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(std::shared_ptr<Model> model, std::shared_ptr<Storage> storage, QQmlApplicationEngine *engine,
                        QObject *parent = nullptr);

    Q_INVOKABLE void fetchData();
    Q_INVOKABLE void fetchForecast();

    Q_INVOKABLE void renderData(QString chart_name, QString series_name);

    Q_INVOKABLE void editSettingsValue(QString key, QVariant value);
    Q_INVOKABLE QVariant fetchSettingsValue(QString key);

    Q_INVOKABLE void setParameter(QString name, QString value);

    // For connecting signal to render Data after download is complete.
    // Must be invoked after QWidgets are populated.
    Q_INVOKABLE void connectSignal();
    Q_INVOKABLE void connectForecastSignal();

signals:
    void fetchCompleted();
    void forecastCompleted();

private:
    std::shared_ptr<Model> model_;
    std::shared_ptr<Storage> storage_;
    QQmlApplicationEngine* engine_;
    bool connected = false;
    bool forecastConnected = false;
};

#endif // CONTROLLER_H
