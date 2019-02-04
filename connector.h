#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QObject>
#include <QProcess>
#include <QDir>

class ObjectData;
class LdapObject;
typedef QList<LdapObject*> LdapObjectList;

class Connector : public QObject
{
    Q_OBJECT
public:
    explicit Connector(QObject *parent = nullptr);

    bool connect(QString server);
    bool connect(QDir mountpoint);

    void query(ObjectData &data, LdapObject *parent);
    void childs(LdapObjectList &objectList, LdapObject *parent);

    QString server() const {
        return dc;
    }
signals:

public slots:

private:
    QString dc;
    QDir root;
    QProcess adfs;
    bool isMounted;
};

#endif // CONNECTOR_H
