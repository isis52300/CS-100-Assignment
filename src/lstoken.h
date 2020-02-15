#ifndef __LSTOKEN_H__
#define __LSTOKEN_H__

#include "token.h"

class LsToken : public Token {
public:
    LsToken() : Token() {
    //    argument = "";
    }
    LsToken(vector<string> a) : Token() {
        argument = a;
    }

    void execute() {
    	vector<char *> argv(argument.size() + 2);
        string ls = "ls";
        argv[0] = &ls[0];
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
        if ( (argument.size() == 1 && 
              (argument.at(0) == "" || argument.at(0) == "-a" || 
               argument.at(0) == "-l" || argument.at(0) == "-lR"
              || argument.at(0) == "-R"))
              || argument.size() == 0  ) {
            return true;
        }
        return false;
    }
private:
    vector<string> argument;
    
};

#endif //__LSTOKEN_H__

