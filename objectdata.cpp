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

AttributeType attributeTypeByTypeName(QString type)
{
    for (unsigned int attrType = 0; attrType < UnknownAttributeType; attrType++)
    {
        if (type == attributeTypes[attrType])
            return (AttributeType) attrType;
    }

    return UnknownAttributeType;
}


ObjectData::ObjectData()
{

}

QVariant ObjectData::value(AttributeName attrType) const
{
//    qDebug() << "ObjectData::value for attr: " << attrType;
    const Attribute val(ObjectMap::value(attributeName(attrType)));

//    qDebug() << "ObjectData::value size: " << val.size();
    if (val.size() <= 0)
        return QString("UnknownAttr");

    return val.first();
}

void ObjectData::insert(AttributeName attrName, AttributeType attrType, QString val) {
    QString attr = attributeName(attrName);
    QString type = attributeType(attrType);
    qDebug() << "ObjectData::insert for attrName: " << attrName << val << type;
    ObjectMap::insert(attr, Attribute(val, attrType));
    qDebug() << "ObjectData::insert inserted: " << values(attributeName(attrName));
}

void ObjectData::insert(QString attr, QString type, QString val) {
    AttributeType attrType = attributeTypeByTypeName(type);
    qDebug() << "ObjectData::insert for attr: " << attr << val << type;
    ObjectMap::insert(attr, Attribute(val, attrType));
    qDebug() << "ObjectData::insert inserted by name: " << values(attr);
}
