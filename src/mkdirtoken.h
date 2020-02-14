#ifndef __MKDIRTOKEN_H__
#define __MKDIRTOKEN_H__

#include "token.h"

class MkdirToken : public Token {
public:
    MkdirToken() : Token() { argument = ""; }
    MkdirToken(string a) : Token() {
        argument = a;
    }
    void execute() {} //Need a CurrentDirectory class before this can be implementeds
    bool isValid() {
        if (argument == "") {
            return false;
        }
        return true;
    };
    
private:
    string argument;
    
};

#endif //__MKDIRTOKEN_H__

