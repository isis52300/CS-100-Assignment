#ifndef __ECHOTOKEN_H__
#define __ECHOTOKEN_H__

#include "token.h"

class EchoToken : public Token {
public:
    EchoToken() : Token() { argument = ""; }
    EchoToken(string a) : Token() {
        argument = a;
    }
    void execute() {
        if (argument.at(0) == '\"') {
                        string temp = "";
                        for (unsigned i = 1; i < argument.size(); ++i) {
                            temp.push_back(argument.at(i));
                        }
                        argument = temp;
        }
        if (argument.at(argument.size() - 1) == '\"') {
            argument.erase(argument.size() - 1, 1);
        }
        cout << argument << endl;
    }
    bool isValid() {return true;}
    
private:
    string argument;
    
};

#endif //__ECHOTOKEN_H__

