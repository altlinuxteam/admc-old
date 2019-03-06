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
    return connect(QDir("/home/sin/work/samba/ui/admc/mnt"));
}

bool Connector::connect(QDir mountpoint)
{
    root = mountpoint;

    if (mountpoint.isReadable())
    {
        isMounted = true;
        return true;
    } else {
        isUpdated = false;
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

void Connector::childs(LdapObjectList &objectList, LdapObject *parent)
{
    if (!parent) {
        qDebug() << "Connector::childs: parent is null!";
        return;
    }

    //qDeleteAll(objectList);

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
        QString child = it.next();
        qDebug() << "Connector::childs: " << child;
        QFileInfo info(child);
        QFileInfo attributesInfo(it.next(), ".attributes");
        if(info.isDir() && attributesInfo.isFile() && attributesInfo.isReadable()) {
            LdapObject *object = new LdapObject(info.fileName(), *this, parent);
            QFile attributesFile(attributesInfo.filePath());
            if (attributesFile.open(QIODevice::ReadOnly))
            {
               QTextStream in(&attributesFile);
               QRegularExpression attributePattern("^(\\S+): (.*)$");
               QRegularExpression attributeBase64Pattern("^(\\S+):: (.*)$");
               QRegularExpression commentPattern("^#");
               while (!in.atEnd())
               {
                  QString line = in.readLine();
                  QRegularExpressionMatch res = commentPattern.match(line);
                  if (res.hasMatch())
                      continue;
                  res = attributeBase64Pattern.match(line);
                  if (!res.hasMatch())
                    res = attributePattern.match(line);
                  if (res.hasMatch())
                     qDebug() << "attribute: " << res.capturedTexts();
               }
               attributesFile.close();
            } else {
                qDebug() << "attribute not opened: " << attributesInfo.path();
            }
            objectList.append(object);
        }
    }
}

void Connector::queryRoot(ObjectData &data, LdapObjectList &objectList, LdapConnection *connection)
{
    if (!connection) {
        qDebug() << "Connector::query: for null connection";
    } else {
        qDebug() << "Connector::query: for connection" << connection->name();

        LdapObject *parent = connection;
        childs(objectList, parent);
        isUpdated = false;
    }
}

bool Connector::updated() const
{
    return isUpdated;
}
