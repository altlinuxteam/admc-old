#ifndef OBJECTDATA_H
#define OBJECTDATA_H

#include <QMap>
#include <QList>
#include <QVariant>
#include <QStringList>

class ObjectData: QMap<QString, QStringList>
{
public:
    ObjectData();

    int count() const { return 0; }
    QVariant value(int column) const { return column; }
};

#endif // OBJECTDATA_H
