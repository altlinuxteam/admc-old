#ifndef LDAPOBJECT_H
#define LDAPOBJECT_H

#include "objectdata.h"

class LdapObject
{
public:
    LdapObject(const ObjectData &data, LdapObject *parent = 0);
    ~LdapObject();

    void appendChild(LdapObject *child);

    LdapObject *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    LdapObject *parent();

private:

    QList<LdapObject*> childObjects;
    ObjectData objectData;
    LdapObject *parentObject;
};

#endif // LDAPOBJECT_H
