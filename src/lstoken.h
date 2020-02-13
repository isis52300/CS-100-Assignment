#ifndef __LSTOKEN_H__
#define __LSTOKEN_H__

#include "token.h"

class LsToken : public Token {
public:
    void check();
    void LsToken() : Token() {
        argument = "";
    }
    void LsToken(string a) : Token() {
        argument = a;
    }
    void execute();
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

