#ifndef __TESTTOKEN_H__
#define __TESTTOKEN_H__

#include <cstring>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "token.h"

class TestToken : public Token {
public:
    TestToken() : Token() { }
    TestToken(vector<string> a) : Token() {
        argument = a;
        valid = false;
    }
    void execute() {
        
        int startIndex = 1;
        bool flagE = false, flagF = false, flagD = false;
        
        if (argument.at(startIndex) == "-f") {
            flagF = true;
            ++startIndex;
        }
        else if (argument.at(startIndex) == "-d") {
            flagD = true;
            ++startIndex;
        }
        else if (argument.at(startIndex) == "-e"){
            flagE = true;
            ++startIndex;
        }
        else {
            flagE = true;
        }
        
        //NOTE: This might have to be moved to the constructor
        struct stat sb;
        vector<char *> argv(argument.size() + 2);
        argv[0] = &argument[startIndex][0];
        
        if (stat(argv[0], &sb) == -1) { //Calling the stat() function and testing it
            cout << "(FALSE)\n";
        }
        //Now sb should have all the information about the files that you need
        
        if (flagD && S_ISDIR (sb.st_mode) != 0) {
            valid = true;
            cout << "(TRUE)\n";
        }
        else if (flagF && S_ISREG (sb.st_mode) != 0) {
            valid = true;
            cout << "(TRUE)\n";
        }
        else if (flagE && (S_ISDIR (sb.st_mode) != 0 || S_ISREG (sb.st_mode) != 0)) {
            valid = true;
            cout << "(TRUE)\n";
        }
        /*else {
            cout << "(FALSE)\n";
        }*/
        
    }
    bool isValid() {return true;} //Might have to change true to the bool valid later
    
private:
    vector<string> argument;
    bool valid;
};

#endif //__TESTTOKEN_H__


