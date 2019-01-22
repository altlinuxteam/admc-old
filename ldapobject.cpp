

#include "ldapobject.h"

#include <QStringList>

LdapObject::LdapObject(const QList<QVariant> &data, LdapObject *parent)
{
    parentObject = parent;
    //objectData = data;
}

LdapObject::~LdapObject()
{
    qDeleteAll(childObjects);
}

void LdapObject::appendChild(LdapObject *item)
{
    childObjects.append(item);
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

QVariant LdapObject::data(int column) const
{
    return objectData.value(column);
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
