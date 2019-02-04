#include "ldapobject.h"

#include <QStringList>

LdapObject::LdapObject(const ObjectData &data, LdapObject *parent, ObjectType objectType):
    objectType(objectType)
{
    parentObject = parent;
    objectData = data;
}

LdapObject::~LdapObject()
{
    qDeleteAll(childObjects);
}

void LdapObject::appendChild(LdapObject *object)
{
    childObjects.append(object);
}

LdapObject *LdapObject::child(int row)
{
    return childObjects.value(row);
}

int LdapObject::childCount() const
{
    return childObjects.count();
}

int LdapObject::columnCount() const
{
    return objectData.count();
}

QVariant LdapObject::data(AttributeType attr) const
{
    return objectData.value(attr);
}

LdapObject *LdapObject::parent()
{
    return parentObject;
}

int LdapObject::row() const
{
    if (parentObject)
        return parentObject->childObjects.indexOf(const_cast<LdapObject*>(this));

    return 0;
}

ObjectType LdapObject::type()
{
    return objectType;
}
