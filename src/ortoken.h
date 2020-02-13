#ifndef __ORTOKEN_H__
#define __ORTOKEN_H__

#include "token.h"

class OrToken : public Token {
	public:
		void check();
        void OrToken(Token* l, Token* r) : Token() {
            left = l;
            right = r;
        }
	protected:
        Token* left;
        Token* right;

};

#endif //__ORTOKEN_H__
