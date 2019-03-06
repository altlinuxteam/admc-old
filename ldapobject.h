#ifndef LDAPOBJECT_H
#define LDAPOBJECT_H

#include "objectdata.h"
#include "connector.h"

enum ObjectType
{
    ConnectionType,
    UnknownType,
    UserType,
    GroupType,
    OrganizationalUnitType
};

class LdapObject
{
public:
    LdapObject(QString name, Connector &connector, LdapObject *parent = nullptr, ObjectType objectType = UnknownType);
    virtual ~LdapObject();

    void appendChild(LdapObject *child);
    void appendAttribute(QString name, QString value);

    LdapObject *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(AttributeName attr) const;
    QString name() const;
    QString path(QString parent = QString()) const;
    int row() const;
    LdapObject *parent() const;
    ObjectType type() const;
    bool canFetch() const;
    void fetch();

protected:
    Connector &connector;

private:
    LdapObject *parentObject;

protected:
    ObjectData objectData;
    LdapObjectList childObjects;

private:
    ObjectType objectType;

    void queryData();
    bool isFetched;
};

#endif // LDAPOBJECT_H
