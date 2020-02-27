#ifndef __ANDTOKEN_H__
#define __ANDTOKEN_H__

#include "token.h"

class AndToken : public Token {
	public:
        AndToken() : Token() {}
        AndToken(Token* l, Token* r) : Token() {
            left = l;
            right = r;
        }
    
    void execute(){
        if (left->isValid()) {
            left->execute();
            if (right->isValid()) {
                right->execute();
            }
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

#endif //__ANDTOKEN_H__
