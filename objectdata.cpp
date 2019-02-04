#include "common.h"
#include "objectdata.h"

const char* attributeNames[]
{
    "name",
    "dn",
    "cn",
    "distinguishedName",
    "showInAdvancedViewOnly",
    "objectCategory",
    "objectClass",
    "objectGUID",
    "objectSid",
    "uSNChanged",
    "uSNCreated",
    "whenChanged",
    "whenCreated",
    "instanceType",
    "adminCount",
    "sAMAccountName",
    "sAMAccountType",
    "description",
    "userAccountControl",
    "codePage",
    "countryCode",
    "accountExpires",
    "lastLogoff",
    "lastLogon",
    "logonCount",
    "primaryGroupID",
    "badPwdCount",
    "badPasswordTime",
    "pwdLastSet",
    "member",
    "memberOf",
    "systemFlags",
    "isCriticalSystemObject"
};

QString attributeName(AttributeType attr)
{
    if (attr >= UnknownAttr)
        return QString("UknownAttr");

    return QString(attributeNames[attr]);
}

ObjectData::ObjectData()
{

}

QVariant ObjectData::value(AttributeType attr) const
{
    qDebug() << "ObjectData::value for attr: " << attr;
    QList<QString> vals = values(attributeName(attr));

    qDebug() << "ObjectData::value size: " << vals.size();
    if (vals.size() <= 0)
        return QString("UnknownName");

    return vals.first();
}

QVariant ObjectData::insert(AttributeType attr, QString val)
{
    QString key = attributeName(attr);
    qDebug() << "ObjectData::insert for attr: " << attr << val;
    ObjectMap::insert(key, val);
    qDebug() << "ObjectData::insert inserted: " << values(attributeName(attr));
}
