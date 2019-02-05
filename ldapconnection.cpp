#include "ldapconnection.h"
#include "common.h"

LdapConnection::LdapConnection(Connector &connector):
    LdapObject(connector.server(), connector, nullptr, ConnectionType)
{
}

bool LdapConnection::canFetch() const
{
    return connector.updated();
}

void LdapConnection::fetch()
{
    qDebug() << "LdapConnection::fetch: fetch!!!";
    queryData();
    getChilds();
}

void LdapConnection::queryData()
{
    connector.query(objectData, this);
}

void LdapConnection::getChilds()
{
    connector.childs(childObjects, this);
}
