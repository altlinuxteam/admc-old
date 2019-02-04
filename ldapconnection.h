#ifndef LDAPCONNECTION_H
#define LDAPCONNECTION_H

#include "ldapobject.h"

class LdapConnection : public LdapObject
{
public:
    LdapConnection(Connector &connector);

};

#endif // LDAPCONNECTION_H
