#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <QString>

class DownLoader;

class Model
{
public:
    explicit Model(std::shared_ptr<DownLoader> downloader);

    void fetchData(QString url);

private:
    std::shared_ptr<DownLoader> downloader_;
};

#endif // MODEL_H
