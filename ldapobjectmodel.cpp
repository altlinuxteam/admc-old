#include "ldapobjectmodel.h"

LdapObjectModel::LdapObjectModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant LdapObjectModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex LdapObjectModel::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex LdapObjectModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int LdapObjectModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int LdapObjectModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

bool LdapObjectModel::hasChildren(const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

bool LdapObjectModel::canFetchMore(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return false;
}

void LdapObjectModel::fetchMore(const QModelIndex &parent)
{
    // FIXME: Implement me!
}

QVariant LdapObjectModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
