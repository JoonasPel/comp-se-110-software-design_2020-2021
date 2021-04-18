#ifndef FINGRIDAPI_HH
#define FINGRIDAPI_HH

#include <QWidget>
#include <QNetworkReply>
#include <IElectricityData.hh>

class QNetworkAccessManager;
class QFormLayout;


class FinGridAPI:public QWidget
{
    Q_OBJECT
public:
    FinGridAPI(QWidget* parent = nullptr);
    void downloadData(QString startTime,QString endTime, QString variableid);
    //return requested data.
    std::map<QString,double> giveRequestData();

signals:
    void dataIsReady(std::map<QString,double>,QString urlType);
    void currentDataReady(QString type, double value);

private Q_SLOTS:
    void downloadFinished(QNetworkReply*);
    QString getSeriesName(QString val);

private:
    QNetworkAccessManager* man;
    //std::map<QString,double> requestData_;
};

#endif // FINGRIDAPI_HH
