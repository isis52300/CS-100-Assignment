#ifndef __MKDIRTOKEN_H__
#define __MKDIRTOKEN_H__

#include "token.h"

class MkdirToken : public Token {
public:
    void check();
    void MkdirToken() : Token() {}
    void MkdirToken(string a) : Token() {
        argument = a;
    }
    void execute() {};
    bool isValid() {
        if (argument == "") {
            return false;
        }
        return true;
    };
    
private:
    string argument = "";
    
};

#endif //__MKDIRTOKEN_H__

