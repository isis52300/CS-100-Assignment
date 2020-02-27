#ifndef __ORTOKEN_H__
#define __ORTOKEN_H__

#include "token.h"

class OrToken : public Token {
	public:
        OrToken() : Token() {}
        OrToken(Token* l, Token* r) : Token() {
            left = l;
            right = r;
        }
    void execute() {
        if (left->isValid()) {
            left->execute();
        }
        else if (right->isValid()) {
            right->execute();
        }
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

#endif //__ORTOKEN_H__
