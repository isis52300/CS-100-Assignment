#ifndef __ECHOTOKEN_H__
#define __ECHOTOKEN_H__

#include <cstring>
#include <string.h>

#include "token.h"

class EchoToken : public Token {
public:
    EchoToken() : Token() { }
    EchoToken(vector<string> a) : Token() {
        argument = a;
    }
    void execute() {
 
	vector<char *> argv(argument.size() + 2);
        string echo = "echo";
        argv[0] = &echo[0];
	for (unsigned i = 1; i < argument.size(); ++i){
                
		if (argument.at(i).at(0) == '\"' && argument.at(i).at(argument.at(i).size() -1) == '\"') {
		     argument.at(i) = argument.at(i).substr(1, argument.at(i).size() -2 );
		}
		if (argument.at(i).at(0) == '\"') {
                     argument.at(i) = argument.at(i).substr(1, argument.size() );
                }
                if (argument.at(i).at(argument.at(i).size() -1) == '\"') {
                     argument.at(i) = argument.at(i).substr(0, argument.at(i).size() -1 );
                }
    		argv[i] = &argument[i][0];
	}

   
        pid_t pid = fork();
        int status;
        
        if (pid == 0) { //This is the child
            
            execvp(argv[0], argv.data());
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
    vector<string> argument;
    
};

#endif //__ECHOTOKEN_H__

