#ifndef __SEMICOLONTOKEN_H__
#define __SEMICOLONTOKEN_H__

#include "token.h"
#include "connectortoken.h"

class SemicolonToken : public ConnectorToken {
public:
    SemicolonToken() : ConnectorToken() {}
    SemicolonToken(Token* l, Token* r) : ConnectorToken() {
        left = l;
        right = r;
    }
    
    void execute(){
        left->execute();
        right->execute();
    }
    
    void addLeft(Token* l) {
        left = l;
    }
    void addRight(Token* r) {
        right = r;
    }
    
    bool isValid() {return true;}
    
    
protected:
    Token* left;
    Token* right;
    
};

#endif //__SEMICOLONTOKEN_H__

