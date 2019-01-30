#include "connector.h"

Connector::Connector(QObject *parent) : QObject(parent), isMounted(false)
{

}

bool Connector::connect(QString server)
{
    return false;
}

bool Connector::connect(QDir mountpoint)
{
    if (mountpoint.isReadable())
    {
        root = mountpoint;
        isMounted = true;
        return true;
    }

    return false;
}
