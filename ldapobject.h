#ifndef LDAPOBJECT_H
#define LDAPOBJECT_H

#include "objectdata.h"

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
    LdapObject(const ObjectData &data, LdapObject *parent = nullptr, ObjectType objectType = UnknownType);
    ~LdapObject();

    void appendChild(LdapObject *child);

    LdapObject *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(AttributeType attr) const;
    int row() const;
    LdapObject *parent();
    ObjectType type();

protected:
    ObjectData objectData;

private:
    QList<LdapObject*> childObjects;
    LdapObject *parentObject;
    ObjectType objectType;
};

#endif // LDAPOBJECT_H
