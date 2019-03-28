#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QObject>
#include <QProcess>
#include <QDir>

class ObjectData;
class LdapObject;
class LdapConnection;
typedef QList<LdapObject*> LdapObjectList;

#include <QTemporaryDir>

class Connector : public QObject
{
    Q_OBJECT
public:
    explicit Connector(QObject *parent = nullptr);
    ~Connector();

    bool connect(QString server);
    bool connect(QDir mountpoint);
    void disconnect();

    bool lastErrorExists();
    QString lastError();

    void query(ObjectData &data, LdapObject *parent);
    bool childs(LdapObjectList &objectList, LdapObject *parent);
    void queryRoot(ObjectData &data, LdapObjectList &objectList, LdapConnection *parent);

    QString server() const {
        return dc;
    }

    static QStringList search(QString server = QString());

    bool updated() const;
signals:

public slots:

private:
    QString dc;
    QDir root;
    QProcess adfs;
    bool isUpdated;
    QScopedPointer<QTemporaryDir> temp;
};

#endif // CONNECTOR_H
