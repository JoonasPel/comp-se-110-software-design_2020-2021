#ifndef FINGRIDAPI_HH
#define FINGRIDAPI_HH

#include <QWidget>
#include <QNetworkReply>

class QNetworkAccessManager;
class QFormLayout;


class FinGridAPI:public QWidget
{
public:
    FinGridAPI(QWidget* parent = nullptr);
    void downloadData(QString startTime,QString endTime, QString variableid);
    //return requested data.
    std::map<QString,int> giveRequestData();

signals:
    void dataIsReady();

private Q_SLOTS:
    void downloadFinished(QNetworkReply*);

private:
    QNetworkAccessManager* man;
    std::map<QString,int> requestData_;
};

#endif // FINGRIDAPI_HH
