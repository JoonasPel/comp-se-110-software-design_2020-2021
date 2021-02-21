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
