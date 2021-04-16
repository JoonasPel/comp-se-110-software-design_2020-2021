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
    void downloadData();


private Q_SLOTS:
    void downloadFinished(QNetworkReply*);

private:
    QNetworkAccessManager* man;
};

#endif // FINGRIDAPI_HH
