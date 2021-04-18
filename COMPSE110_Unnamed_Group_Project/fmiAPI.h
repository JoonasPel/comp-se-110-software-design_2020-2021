#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QMap>
#include <QWidget>
#include <QNetworkReply>

class QNetworkAccessManager;
class QFormLayout;

class fmiAPI :public QWidget
{
    Q_OBJECT
public:
    explicit fmiAPI(QWidget *parent = nullptr);
    Q_INVOKABLE void load(std::map<QString, QString>);

signals:
    void fetchCompleted(std::map<QString,std::map<QString,QString>>);

private Q_SLOTS:
    void downloadCompleted(QNetworkReply *);

private:
    QFormLayout *form;
    QNetworkAccessManager *network;
    QString urlFMI;
    bool XMLparser(QNetworkReply*);
    //structure to save parsed data
    std::map<QString,std::map<QString,QString>> structure_;
    QString urlModifier(std::map<QString, QString>);
};


#endif /* DOWNLOADER_H */

