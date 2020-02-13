#ifndef __ECHOTOKEN_H__
#define __ECHOTOKEN_H__

#include "token.h"

class EchoToken : public Token {
public:
    void check();
    void EchoToken() : Token() {}
    void EchoToken(string a) : Token() {
        argument = a;
    }
    void execute() {
        cout << argument;
    };
    bool isValid() {return true};
    
private:
    string argument;
    
};

#endif //__ECHOTOKEN_H__

