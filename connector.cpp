#include "connector.h"
#include "ldapobject.h"
#include "common.h"

#include <QDirIterator>

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

void Connector::query(ObjectData &data, LdapObject *parent)
{
    if (!parent) {
        qDebug() << "Connector::query for root";
    } else {
        qDebug() << "Connector::query: " << parent->name();
    }
}

void Connector::childs(LdapObjectList &objectList, LdapObject *parent)
{
    qDeleteAll(objectList);

    if (!parent) {
        qDebug() << "Connector::child: parent is null!";
        return;
    }

    QDir adfsPath(root.relativeFilePath(parent->path()));

    if (!adfsPath.isReadable()) {
        qDebug() << "Connector::child: adfs path not ready" << adfsPath;
        return;
    }

    QDirIterator it(adfsPath);
    while (it.hasNext()) {
        qDebug() << "Connector::child: " << it.next();
        QFileInfo info(it.next());
        if(info.isDir())
            objectList.append(new LdapObject(info.fileName(), *this, parent));
    }
}
