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
#include <DownLoader.h>
#include <controller.h>
#include <model.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    auto downloader{ std::make_shared<DownLoader>() };
    auto model{ std::make_shared<Model>(downloader) };
    auto controller{ std::make_shared<Controller>(model, &engine) };

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

    return app.exec();
}
