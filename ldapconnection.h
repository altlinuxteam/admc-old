#ifndef LDAPCONNECTION_H
#define LDAPCONNECTION_H

#include "ldapobject.h"
#include "connector.h"

class LdapConnection : public LdapObject
{
public:
    LdapConnection(Connector &c);

private:
    Connector &connector;
};

#endif // LDAPCONNECTION_H
