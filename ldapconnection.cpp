#include "ldapconnection.h"

LdapConnection::LdapConnection(Connector &c):
    LdapObject(ObjectData()), connector(c)
{
    objectData.insert(NameAttr, c.server());
}
