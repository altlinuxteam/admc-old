#include "connector.h"

Connector::Connector(QObject *parent) : QObject(parent), isMounted(false)
{

}

bool Connector::connect(QString server)
{
    dc = server;
    return connect(QDir("mnt"));
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
