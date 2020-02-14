#ifndef __EXITTOKEN_H__
#define __EXITTOKEN_H__

#include "token.h"

using namespace std;

class ExitToken : public Token {
public:
    ExitToken() : Token() {}
    void execute() {
        cout << "Exiting the shell\n";
        exit(0);
    }
    bool isValid() {return true;}
private:
    
};

#endif //__EXITTOKEN_H__


