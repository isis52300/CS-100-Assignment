#ifndef __SEMICOLONTOKEN_H__
#define __SEMICOLONTOKEN_H__

#include "token.h"

class SemicolonToken : public Token {
public:
    SemicolonToken(Token* l, Token* r) : Token() {
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

