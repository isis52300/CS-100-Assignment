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
        
        //char* echo = "echo";
        char* argv[100];
        argv[0] = "echo";
        int argvIndex = 1;
        
        for (unsigned i = 1; i < argument.size(); ++i) {
            string temp = "";
            if (argument.at(i) != ' ') {
                temp = temp + argument.at(i);
                if (i + 1 == argument.size()) {
                    argv[argvIndex] = temp;
                    ++argvIndex;
                }
            }
            else {
                argv[argvIndex] = temp;
                ++argvIndex;
                temp = "";
            }
        }
        
        pid_t pid = fork();
        int status;
        
        if (pid == 0) { //This is the child
            
            execvp(argv[0], argv);
            cout << endl;
            
        }
        else if (pid > 0) { //This is the parent
            
            waitpid(pid, &status, 0);
            
        }
        else { //The forking has failed
            
            cout << "The forking failed";
            exit(1);
            
        }
        //cout << argument << endl;
    }
    bool isValid() {return true;}
    
private:
    string argument;
    
};

#endif //__ECHOTOKEN_H__

