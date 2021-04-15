#ifndef STORAGE_H
#define STORAGE_H
#include <QSettings>
#include <memory>

class Storage
{
public:
    Storage();

    void editValue(QString key, QVariant value);
    QVariant fetchValue(QString key);

private:
    std::shared_ptr<QSettings> _settings;
};

#endif // STORAGE_H
