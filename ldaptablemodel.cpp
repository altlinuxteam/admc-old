#include "ldaptablemodel.h"
#include "common.h"

LdapTableModel::LdapTableModel(QObject *parent)
    : QAbstractTableModel(parent), parentObject(nullptr)
{
     qDebug() << "LdapTableModel::LdapTableModel" << (void*)this;
}

QVariant LdapTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

int LdapTableModel::rowCount(const QModelIndex &parent) const
{
    if (parentObject == nullptr)
        return 0;

//    qDebug() << "LdapTableModel::rowCount =" << parentObject->childCount();

    return parentObject->childCount();
}

int LdapTableModel::columnCount(const QModelIndex &parent) const
{
    if (parentObject == nullptr)
        return 0;

    return 1;
}

QVariant LdapTableModel::data(const QModelIndex &index, int role) const
{
    if (parentObject == nullptr)
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    LdapObject* object = parentObject->child(index.row());
//    qDebug() << "LdapTableModel::data return NameAttr for ObjectType" << index.row() << index.column() << object->type() << object->name();
    return object->data(NameAttr);
}

void LdapTableModel::setRootObject(LdapObject *object)
{
    if (object == nullptr)
        return;

    beginResetModel();
    qDebug() << "LdapTableModel: setRootObject" << object << "for parentObject" << parentObject;
    parentObject = object;
    qDebug() << "LdapTableModel: setRootObject done" << object;
    endResetModel();
}

QModelIndex LdapTableModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parentObject == nullptr)
        return QModelIndex();

    LdapObject* object = parentObject->child(row);
    return createIndex(row, column, object);
}

