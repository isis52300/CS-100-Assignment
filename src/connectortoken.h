#ifndef __CONNECTORTOKEN_H__
#define __CONNECTORTOKEN_H__

#include "token.h"

class ConnectorToken : public Token {
public:
    ConnectorToken() : Token () {};
    virtual void addLeft(Token*) = 0;
    virtual void addRight(Token*) = 0;
    
protected:
    
};

#endif //__CONNECTORTOKEN_H__

