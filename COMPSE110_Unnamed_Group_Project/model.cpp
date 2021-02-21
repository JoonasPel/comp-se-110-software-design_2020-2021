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
    QList<QPointF> points = {QPoint(1, 1), QPoint(2, 3), QPoint(3, 3), QPoint(25, 16), QPoint(32, 19), QPoint(43, 29), QPoint(65, 14), QPoint(123, 24), QPoint(143, 29)};

    return points;

}

