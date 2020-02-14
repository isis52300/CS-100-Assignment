#ifndef __ORTOKEN_H__
#define __ORTOKEN_H__

#include "token.h"

class OrToken : public Token {
	public:
		void check();
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
    bool isValid() {return true;}
    
	protected:
        Token* left;
        Token* right;

};

#endif //__ORTOKEN_H__
