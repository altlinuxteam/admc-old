#include "ldapconnection.h"

LdapConnection::LdapConnection(Connector &connector):
    LdapObject(connector.server(), connector, nullptr, ConnectionType)
{
}

