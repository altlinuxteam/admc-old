#ifndef OBJECTDATA_H
#define OBJECTDATA_H

#include <QMap>
#include <QList>
#include <QVariant>
#include <QStringList>

class ObjectData: public QMap<QString, QStringList>
{
public:
    ObjectData();

    QVariant value(int column) const { return column; }
};

#endif // OBJECTDATA_H
