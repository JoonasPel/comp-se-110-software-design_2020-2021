#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <QObject>

class Model;

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(std::shared_ptr<Model> model,
                        QObject *parent = nullptr);

    Q_INVOKABLE void fetchData(QString url);

private:
    std::shared_ptr<Model> model_;
};

#endif // CONTROLLER_H
