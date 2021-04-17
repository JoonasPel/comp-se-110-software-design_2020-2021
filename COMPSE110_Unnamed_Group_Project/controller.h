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

    Q_INVOKABLE void fetchData(QString url, QString place, QString startTime, QString endTime);

    Q_INVOKABLE void renderData(QString chart_name, QString series_name);

    Q_INVOKABLE void editSettingsValue(QString key, QVariant value);
    Q_INVOKABLE QVariant fetchSettingsValue(QString key);

    Q_INVOKABLE void setParameter(QString name, QString value);

private:
    std::shared_ptr<Model> model_;
    std::shared_ptr<Storage> storage_;
    QQmlApplicationEngine* engine_;
};

#endif // CONTROLLER_H
