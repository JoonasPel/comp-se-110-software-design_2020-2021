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
#include <DownLoader.h>
#include <QQmlContext>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    auto downloader{ std::make_shared<DownLoader>() };
    // give the QML side access
    auto context{ engine.rootContext() };
    context->setContextProperty("downloader", downloader.get());

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
