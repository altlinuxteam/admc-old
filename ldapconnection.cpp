#include "ldapconnection.h"
#include "common.h"

LdapConnection::LdapConnection(Connector &connector):
    LdapObject(connector.server(), connector, nullptr, ConnectionType)
{
    qDebug() << "LdapConnection::LdapConnection: " << connector.server();
}

bool LdapConnection::canFetchRoot() const
{
    return connector.updated();
}

void LdapConnection::fetchRoot()
{
    qDebug() << "LdapConnection::fetch: fetch!!!";
    queryRootData();
}

void LdapConnection::queryRootData()
{
    connector.queryRoot(objectData, childObjects, this);
}
