#ifndef __MKDIRTOKEN_H__
#define __MKDIRTOKEN_H__

#include "token.h"

class MkdirToken : public Token {
public:
    void check();
    void MkdirToken(string a) : Token() {
        argument = a;
    }
    
private:
    string argument;
    
};

#endif //__MKDIRTOKEN_H__

