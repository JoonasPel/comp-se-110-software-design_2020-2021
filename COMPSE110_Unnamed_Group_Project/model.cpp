#include "model.h"
#include "DownLoader.h"

Model::Model(std::shared_ptr<DownLoader> downloader) :
    downloader_(downloader)
{
}

void Model::fetchData(QString url)
{
    downloader_->load(url);

}

/*
 * Return data points respective to series name
 */
QList<QPointF> Model::getPointSeries(QString name)
{
    // -- WIP --
    QList<QPointF> points = {QPoint(1, 1), QPoint(2, 3), QPoint(3, 3)};

    return points;

}

