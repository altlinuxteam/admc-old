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
    UnknownAttributeType,
    FirstAttributeType = BooleanType
};

enum AttributeFormat {
    StringFormat,
    BASE64Format
};

QString attributeName(AttributeName attr);

class Attribute: public QStringList
{
public:
    Attribute(): type(UnknownAttributeType), format(StringFormat) {}
    Attribute(QString &s, AttributeType t, AttributeFormat f = StringFormat): QStringList(s), type(t), format(f) {}
    AttributeType type;
    AttributeFormat format;
};

typedef QMap<QString, Attribute> ObjectMap;
class ObjectData: public ObjectMap
{
public:
    ObjectData();

    void insert(AttributeName attrName, AttributeType attrType, QString val);
    void insert(QString attr, QString type, QString val);
    QVariant value(AttributeName attrName) const;
};

#endif // OBJECTDATA_H
