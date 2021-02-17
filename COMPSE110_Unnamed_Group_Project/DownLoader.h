#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QMap>
#include <QWidget>
#include <QNetworkReply>

class QNetworkAccessManager;
class QFormLayout;

class DownLoader :public QWidget
{
    Q_OBJECT
public:
    explicit DownLoader(QWidget *parent = nullptr);
    Q_INVOKABLE void load(const QString &url);

private Q_SLOTS:
    void downloadCompleted(QNetworkReply *);

private:
    QFormLayout *form;
    QNetworkAccessManager *network;
};


#endif /* DOWNLOADER_H */

