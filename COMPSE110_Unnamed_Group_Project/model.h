#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <QString>
#include <QObject>

class DownLoader;

class Model
{
public:
    explicit Model(std::shared_ptr<DownLoader> downloader);

    void fetchData(QString url);
    QList<QPointF> getPointSeries(QString name);

private:
    std::shared_ptr<DownLoader> downloader_;
};

#endif // MODEL_H
