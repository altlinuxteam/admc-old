#include "ldapobject.h"
#include "common.h"

#include <QStringList>

LdapObject::LdapObject(QString name, Connector &connector, LdapObject *parent, ObjectType objectType):
    connector(connector), parentObject(parent), objectType(objectType), isFetched(false)
{
    qDebug() << "LdapObject::LdapObject: for" << name;
    objectData.insert(NameAttr, name);
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

QString LdapObject::name() const
{
    return objectData.value(NameAttr).toString();
}

QString LdapObject::path(QString child) const
{
    if (type() == ConnectionType)
        return QString(QDir::separator());

    QString path = name();
    if (!child.isNull())
        path += QDir::separator() + child;

    if (parentObject != nullptr && parentObject->type() != ConnectionType)
        return parentObject->path(path);

    return path;
}

LdapObject *LdapObject::parent() const
{
    return parentObject;
}

int LdapObject::row() const
{
    if (parentObject)
        return parentObject->childObjects.indexOf(const_cast<LdapObject*>(this));

    return 0;
}

ObjectType LdapObject::type() const
{
    return objectType;
}

bool LdapObject::canFetch() const
{
    return !isFetched;
}

void LdapObject::fetch()
{
    qDebug() << "LdapObject::fetch: fetch!!!";
    queryData();
    getChilds();
    isFetched = true;
}

void LdapObject::queryData()
{
    connector.query(objectData, this);
}

void LdapObject::getChilds()
{
    connector.childs(childObjects, this);
}
