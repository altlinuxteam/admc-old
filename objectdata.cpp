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

QVariant ObjectData::value(AttributeType attrType) const
{
    qDebug() << "ObjectData::value for attr: " << attrType;
    const Attribute val = ObjectMap::value(attributeName(attrType));

    qDebug() << "ObjectData::value size: " << val.size();
    if (val.size() <= 0)
        return QString("UnknownAttr");

    return val.first();
}

QVariant ObjectData::insert(QString val, AttributeType attrType) {
    QString key = attributeName(attrType);
    qDebug() << "ObjectData::insert for attrType: " << attrType << val;
    ObjectMap::insert(key, val);
    qDebug() << "ObjectData::insert inserted: " << values(attributeName(attrType));
}
