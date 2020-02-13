#ifndef __ANDTOKEN_H__
#define __ANDTOKEN_H__

#include "token.h"

class AndToken : public Token {
	public:
		void check();
        void AndToken(Token* l, Token* r) : Token() {
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
    bool isValid() {return true};


	protected:
        Token* left;
        Token* right;

};

#endif //__ANDTOKEN_H__
