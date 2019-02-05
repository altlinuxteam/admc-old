#include "ldapconnection.h"
#include "common.h"

LdapConnection::LdapConnection(Connector &connector):
    LdapObject(connector.server(), connector, nullptr, ConnectionType)
{
}

bool LdapConnection::canFetchRoot() const
{
    return connector.updated();
}

void LdapConnection::fetchRoot()
{
    qDebug() << "LdapConnection::fetch: fetch!!!";
    queryRootData();
    getRootChilds();
}

void LdapConnection::queryRootData()
{
    connector.query(objectData, this);
}

void LdapConnection::getRootChilds()
{
    connector.childs(childObjects, this);
}
