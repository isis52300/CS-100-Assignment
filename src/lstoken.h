#ifndef __LSTOKEN_H__
#define __LSTOKEN_H__

#include "token.h"

class LsToken : public Token {
public:
    LsToken() : Token() {
        argument = "";
    }
    LsToken(string a) : Token() {
        argument = a;
    }
    void execute(); //Need a CurrentDirectory class before this can be implementeds
    bool isValid() {
        if (argument == "-a" || argument == "") {
            return true;
        }
        return false;
    }
private:
    string argument;
    
};

#endif //__LSTOKEN_H__

