#ifndef __EXITTOKEN_H__
#define __EXITTOKEN_H__

#include "token.h"

class ExitToken : public Token {
public:
    void check();
    void ExitToken() : Token() {}
    void execute() {
        cout << "Exiting the shell\n";
        exit(0);
    }
    bool isValid() {return true;}
private:
    
};

#endif //__EXITTOKEN_H__


