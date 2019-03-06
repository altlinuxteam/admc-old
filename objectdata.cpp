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

const char* attributeTypes[] {
    "Boolean",
    "Integer",
    "Enumeration",
    "LargeInteger",
    "ObjectAccessPoint",
    "ObjectDNString",
    "ObjectORName",
    "ObjectDNBinary",
    "ObjectDSDN",
    "ObjectPresentationAddress",
    "ObjectReplicaLink",
    "StringCase",
    "StringIA5",
    "StringNTSecDesc",
    "StringNumeric",
    "StringObjectIdentifier",
    "StringOctet",
    "StringPrintable",
    "StringSid",
    "StringTeletex",
    "StringUnicode",
    "StringUTCTime",
    "StringGeneralizedTime"
};

QString attributeName(AttributeName attr)
{
    if (attr >= UnknownAttr)
        return QString("UknownAttributeName");

    return QString(attributeNames[attr]);
}

QString attributeType(AttributeType attrType)
{
    if (attrType >= UnknownAttributeType)
        return QString("UnknownAttributeType");

    return QString(attributeTypes[attrType]);
}

ObjectData::ObjectData()
{

}

QVariant ObjectData::value(AttributeName attrType) const
{
//    qDebug() << "ObjectData::value for attr: " << attrType;
    const Attribute val = ObjectMap::value(attributeName(attrType));

//    qDebug() << "ObjectData::value size: " << val.size();
    if (val.size() <= 0)
        return QString("UnknownAttr");

    return val.first();
}

void ObjectData::insert(QString val, AttributeName attrName) {
    QString key = attributeName(attrName);
    qDebug() << "ObjectData::insert for attrName: " << attrName << val;
    ObjectMap::insert(key, val);
    qDebug() << "ObjectData::insert inserted: " << values(attributeName(attrName));
}

void ObjectData::insert(QString val, QString attr) {
    qDebug() << "ObjectData::insert for attr: " << attr << val;
    ObjectMap::insert(attr, val);
    qDebug() << "ObjectData::insert inserted by name: " << values(attr);
}
