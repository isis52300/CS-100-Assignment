#ifndef __LSTOKEN_H__
#define __LSTOKEN_H__

#include "token.h"

class LsToken : public Token {
public:
    void check();
    void LsToken() : Token() {}
    void LsToken(string a) : Token() {
        argument = a;
    }
    bool validArgument() {
        if (argument == "-a") {
            return true;
        }
        return false;
    }
private:
    string argument;
    
};

#endif //__LSTOKEN_H__

