#ifndef OBJECTDATA_H
#define OBJECTDATA_H

#include <QMap>
#include <QString>
#include <QVariant>

enum AttributeName
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

enum AttributeType {
    BooleanType,
    IntegerType,
    EnumerationType,
    LargeIntegerType,
    ObjectAccessPointType,
    ObjectDNStringType,
    ObjectORNameType,
    ObjectDNBinaryType,
    ObjectDSDNType,
    ObjectPresentationAddressType,
    ObjectReplicaLinkType,
    StringCaseType,
    StringIA5Type,
    StringNTSecDescType,
    StringNumericType,
    StringObjectIdentifierType,
    StringOctetType,
    StringPrintableType,
    StringSidType,
    StringTeletexType,
    StringUnicodeType,
    StringUTCTimeType,
    StringGeneralizedTimeType,
    UnknownAttributeType
};

enum AttributeFormat {
    StringFormat,
    BASE64Format
};

QString attributeName(AttributeName attr);

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

    void insert(QString val, AttributeName attrName);
    void insert(QString val, QString attr);
    QVariant value(AttributeName attrName) const;
};

#endif // OBJECTDATA_H
