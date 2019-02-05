#ifndef LDAPCONNECTION_H
#define LDAPCONNECTION_H

#include "ldapobject.h"

class LdapConnection : public LdapObject
{
public:
    LdapConnection(Connector &connector);

    bool canFetch() const override;
    void fetch() override;

private:
    void queryData();
    void getChilds();

};

#endif // LDAPCONNECTION_H
