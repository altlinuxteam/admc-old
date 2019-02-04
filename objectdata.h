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

QString attributeName(AttributeType attr);

typedef QMap<QString, QString> ObjectMap;
class ObjectData: public ObjectMap
{
public:
    ObjectData();

    QVariant insert(AttributeType attr, QString val);
    QVariant value(AttributeType attr) const;
};

#endif // OBJECTDATA_H
