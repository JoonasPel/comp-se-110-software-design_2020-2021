#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <QObject>

#include <QtCharts>
#include <QQmlApplicationEngine>
#include <QMetaObject>

class Model;

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(std::shared_ptr<Model> model, QQmlApplicationEngine *engine,
                        QObject *parent = nullptr);

    Q_INVOKABLE void fetchData(QString url, QString place);

    Q_INVOKABLE void renderData(QString chart_name, QString series_name);

private:
    std::shared_ptr<Model> model_;
    QQmlApplicationEngine* engine_;
};

#endif // CONTROLLER_H
