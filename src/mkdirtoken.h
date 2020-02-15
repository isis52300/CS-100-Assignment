#ifndef __MKDIRTOKEN_H__
#define __MKDIRTOKEN_H__

#include "token.h"

class MkdirToken : public Token {
public:
    MkdirToken() : Token() { }
    MkdirToken(vector<string> a) : Token() {
        argument = a;
    }

    void execute() {
    	vector<char *> argv(argument.size() + 2);
        string mkdir = "mkdir";
        argv[0] = &mkdir[0];
        for (unsigned i = 1; i < argument.size(); ++i){
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
    }
    
    bool isValid() {
        if (argument.at(0) == "") {
            return false;
        }
        return true;
    };
    
private:
    vector<string> argument;
    
};

#endif //__MKDIRTOKEN_H__

