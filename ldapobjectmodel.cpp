#include "common.h"
#include "ldapobjectmodel.h"

LdapObjectModel::LdapObjectModel(QObject *parent)
    : QAbstractItemModel(parent)
{

}

QVariant LdapObjectModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

QModelIndex LdapObjectModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    LdapObject *childObject;

    if (!parent.isValid())
        childObject = connections.at(row);
    else {
        LdapObject *parentObject = static_cast<LdapObject*>(parent.internalPointer());
        childObject = parentObject->child(row);
    }

    if (childObject)
        return createIndex(row, column, childObject);
    else
        return QModelIndex();
}

QModelIndex LdapObjectModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    LdapObject *childObject = static_cast<LdapObject*>(index.internalPointer());
    LdapObject *const parentObject = childObject->parent();

    if (parentObject == nullptr || parentObject->type() != ConnectionType)
        return QModelIndex();

    return createIndex(parentObject->row(), 0, parentObject);
}

int LdapObjectModel::rowCount(const QModelIndex &parent) const
{
    LdapObject *parentObject;
    int rows = 0;

    if (!parent.isValid()) {
        rows = connections.size();
        qDebug() << "LdapObjectModel::rowCount: for connections " << rows;
    } else {
        parentObject = static_cast<LdapObject*>(parent.internalPointer());
        rows = parentObject->childCount();
        qDebug() << "LdapObjectModel::rowCount: for object " << rows;
    }

    return rows;
}

int LdapObjectModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        qDebug() << "LdapObjectModel::columnCount: parent is valid";
        qDebug() << "LdapObjectModel::columnCount: " << static_cast<LdapObject*>(parent.internalPointer())->columnCount();
        return static_cast<LdapObject*>(parent.internalPointer())->columnCount();
    }

    if (!connections.empty()) {
        qDebug() << "LdapObjectModel::columnCount: connections is not empty";
        return 1;
    }

    qDebug() << "LdapObjectModel::columnCount: 0";
    return 0;
}

bool LdapObjectModel::hasChildren(const QModelIndex &parent) const
{
    LdapObject *parentObject;

    if (!parent.isValid()) {
        qDebug() << "LdapObjectModel::hasChildren parent is not valid";
        return !connections.empty();
    } else {
        qDebug() << "LdapObjectModel::hasChildren parent is valid";
        parentObject = static_cast<LdapObject*>(parent.internalPointer());
    }

    qDebug() << "LdapObjectModel::hasChildren parent child count" << parentObject->childCount();

    return parentObject->childCount() > 0;
}

bool LdapObjectModel::canFetchMore(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        qDebug() << "LdapObjectModel::canFetchMore: for not valid";
    } else {
        LdapObject *parentObject = static_cast<LdapObject*>(parent.internalPointer());
        qDebug() << "LdapObjectModel::canFetchMore: for object " << parentObject->name();
        return parentObject->canFetch();
    }

    return false;
}

void LdapObjectModel::fetchMore(const QModelIndex &parent)
{
    if (!parent.isValid()) {
        qDebug() << "LdapObjectModel::fetchMore: for not valid";
    } else {
        LdapObject *parentObject = static_cast<LdapObject*>(parent.internalPointer());
        qDebug() << "LdapObjectModel::fetchMore: for object " << parentObject->name();
        parentObject->fetch();
    }
}

QVariant LdapObjectModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        qDebug() << "LdapObjectModel::data index is not valid";
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        qDebug() << "LdapObjectModel::data for not DisplayRole";
        return QVariant();
    }

    LdapObject *object = static_cast<LdapObject*>(index.internalPointer());

    qDebug() << "LdapObjectModel::data return NameAttr for ObjectType" << object->type();
    return object->data(NameAttr);
}

void LdapObjectModel::addConnector(Connector &connector)
{
    qDebug() << "LdapObjectModel::addConnector";
    connections.append(new LdapConnection(connector));
}
