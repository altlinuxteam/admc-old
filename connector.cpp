#include "connector.h"
#include "ldapobject.h"
#include "ldapconnection.h"
#include "common.h"

#include <QDirIterator>

Connector::Connector(QObject *parent) : QObject(parent), isMounted(false), isUpdated(true)
{

}

bool Connector::connect(QString server)
{
    dc = server;
    return connect(QDir("/home/sin/work/samba/admc.git/mnt"));
}

bool Connector::connect(QDir mountpoint)
{
    root = mountpoint;

    if (mountpoint.isReadable())
    {
        isMounted = true;
        return true;
    } else {
        //isUpdated = false;
    }

    return false;
}

void Connector::query(ObjectData &data, LdapObject *parent)
{
    if (!parent) {
        qDebug() << "Connector::query: for null parent";
    } else {
        qDebug() << "Connector::query: " << parent->name();
    }
}

void Connector::query(ObjectData &data, LdapConnection *parent)
{
    if (!parent) {
        qDebug() << "Connector::query: for null connection";
    } else {
        qDebug() << "Connector::query: for connection" << parent->name();
    }
}

void Connector::childs(LdapObjectList &objectList, LdapObject *parent)
{
    if (!parent) {
        qDebug() << "Connector::childs: parent is null!";
        return;
    }

    qDeleteAll(objectList);

    qDebug() << "Connector::childs: root path is" << root.path();
    QDir adfsPath(root.path() + QDir::separator() + parent->path());

    if (!adfsPath.isReadable()) {
        qDebug() << "Connector::childs: adfs path not ready" << adfsPath << QDir::currentPath();
        return;
    }

    adfsPath.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    qDebug() << "Connector::childs: adfs path is" << adfsPath;

    QDirIterator it(adfsPath);
    while (it.hasNext()) {
        qDebug() << "Connector::childs: " << it.next();
        QFileInfo info(it.next());
        if(info.isDir())
            objectList.append(new LdapObject(info.fileName(), *this, parent));
    }
}

void Connector::childs(LdapObjectList &objectList, LdapConnection *connection)
{
    if (!connection) {
        qDebug() << "Connector::childs: connection is null!";
        return;
    }

    LdapObject *parent = connection;
    childs(objectList, parent);
    isUpdated = false;
}

bool Connector::updated() const
{
    return isUpdated;
}
