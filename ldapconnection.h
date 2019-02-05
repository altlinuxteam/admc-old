#ifndef LDAPCONNECTION_H
#define LDAPCONNECTION_H

#include "ldapobject.h"

class LdapConnection : public LdapObject
{
public:
    LdapConnection(Connector &connector);

    bool canFetchRoot() const;
    void fetchRoot();

private:
    void queryRootData();
    void getRootChilds();

};

#endif // LDAPCONNECTION_H
