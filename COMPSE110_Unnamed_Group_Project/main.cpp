/*
 * ==================================================
   | COMP.SE.110 Group Project - Group 'Unnamed'    |
   |-------------------------------------------     |
   |    Joonas Pelttari                             |
   |    Kalle-Henrik Raitanen                       |
   |    Jani Uolamo                                 |
   |    Sipi Ylä-Nojonen                            |
 * ==================================================
 */

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <fmiAPI.h>
#include <controller.h>
#include <model.h>
#include <storage.h>

#include "renderelectricitydata.hh"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);

    // Set values for settings
    app.setOrganizationName("Unnamed");
    app.setOrganizationDomain("unnamed");
    app.setApplicationName("WeatherCast");

    QQmlApplicationEngine engine;

    auto fmiapi{ std::make_shared<fmiAPI>() };
    auto electricData{std::make_shared<renderElectricityData>(&engine)};
    auto model{ std::make_shared<Model>(fmiapi,electricData) };
    auto storage{ std::make_shared<Storage>() };
    auto controller{ std::make_shared<Controller>(model, storage, &engine) };

    // give the QML side access
    auto context{ engine.rootContext() };
    context->setContextProperty("controller", controller.get());

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    //auto electricData{std::make_shared<renderElectricityData>(&engine)};
    //ren->fetchData("2021-03-18T22:00:00Z","2021-03-19T04:00:00Z");
    //electricData->getCurrentValues();



    return app.exec();
}
