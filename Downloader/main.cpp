#include <QFormLayout>
#include <qapplication.h>
#include "DownLoader.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto *downLoader = new DownLoader;

    QString url = "http://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi::observations::weather::simple&place=Pirkkala&timestep=30&parameters=t2m,ws_10min,n_man";

    downLoader->load(url);
    downLoader->show();

    return app.exec();
}
