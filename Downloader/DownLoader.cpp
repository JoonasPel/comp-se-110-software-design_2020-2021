#include "DownLoader.h"
#include <QLabel>
#include <QtDebug>
#include <QFile>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QFormLayout>

DownLoader::DownLoader(QWidget *parent)
    : QWidget(parent)
{
    form = new QFormLayout(this);
    network = new QNetworkAccessManager(this);
    connect(network, &QNetworkAccessManager::finished, this, &DownLoader::downloadCompleted);
}

void DownLoader::load(const QString &url)
{
    network->get(QNetworkRequest(url));
}


void DownLoader::downloadCompleted(QNetworkReply *reply)
{
    //Create file to save data
    QFile file("dataFromFMI.txt");

    //Save data to file
    Q_ASSERT(file.open(QFile::WriteOnly));
    file.write(reply->readAll());
    file.close();
    reply->deleteLater();

    //Inform user that data is saved
    auto *label = new QLabel;
    form->addRow(QString("Download completed. File saved"), label);
}

