#include "storage.h"

#include <QDebug>

Storage::Storage()
{
    //"weathercast_settings", QSettings::IniFormat
    _settings = std::make_shared<QSettings>(new QSettings("weathercast_config.ini", QSettings::IniFormat));
}

// Set settings value to given value with given key
void Storage::editValue(QString key, QVariant value)
{
    _settings->setValue(key, value);
    _settings->sync();
    return;
}

// Fetch settings value with given key
QVariant Storage::fetchValue(QString key)
{
    QVariant value = _settings->value(key);

    //this block is the workaround
    if (QString(value.typeName()) == "QString" &&
        (value.toString() == "false" || value.toString() == "true"))
        return QVariant(value.toBool());

    return value;
}

