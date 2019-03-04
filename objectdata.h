#ifndef OBJECTDATA_H
#define OBJECTDATA_H

#include <QMap>
#include <QString>
#include <QVariant>

enum AttributeType
{
    NameAttr,
    DNAttr,
    CNAttr,
    DistinguishedNameAttr,
    ShowInAdvancedViewOnlyAttr,
    ObjectCategoryAttr,
    ObjectClassAttr,
    ObjectGUIDAttr,
    ObjectSidAttr,
    uSNChangedAttr,
    uSNCreatedAttr,
    WhenChangedAttr,
    WhenCreatedAttr,
    InstanceTypeAttr,
    AdminCountAttr,
    sAMAccountNameAttr,
    sAMAccountTypeAttr,
    DescriptionAttr,
    UserAccountControlAttr,
    CodePageAttr,
    CountryCodeAttr,
    AccountExpiresAttr,
    LastLogoffAttr,
    LastLogonAttr,
    LogonCountAttr,
    PrimaryGroupIDAttr,
    BadPwdCountAttr,
    BadPasswordTimeAttr,
    PwdLastSetAttr,
    MemberAttr,
    MemberOfAttr,
    SystemFlagsAttr,
    isCriticalSystemObjectAttr,
    UnknownAttr
};

enum AttributeFormat {
    StringFormat,
    BASE64Format
};

QString attributeName(AttributeType attr);

class Attribute: public QStringList
{
public:
    Attribute(): format(StringFormat) {}
    Attribute(QString &s, AttributeFormat format = StringFormat): QStringList(s), format(format) {}
    AttributeFormat format;
};

typedef QMap<QString, Attribute> ObjectMap;
class ObjectData: public ObjectMap
{
public:
    ObjectData();

    void insert(QString val, AttributeType attrType);
    QVariant value(AttributeType attrType) const;
};

#endif // OBJECTDATA_H
