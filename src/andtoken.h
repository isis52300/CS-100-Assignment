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

	protected:
        Token* left;
        Token* right;

};

#endif //__ANDTOKEN_H__
