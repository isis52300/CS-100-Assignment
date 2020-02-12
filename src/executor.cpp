#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include <iostream>
#include <string>
#include <vector>

usign namespace std;

class Executor {
    
public:
    
    Executor();
    void execute(char* [], int);
    bool canExecute(char* []);
    
private:
    
    
};



#endif //__EXECUTOR_H__



Executor() {
    
    bool timeToExit = false;
    char* userInput[];
    int userInputSize;
    
    while (!timeToExit) {
        
        cout << "$ ";
        while (cin >> userInput) {
            ++userInputSize;
        }
        
        execute(userInput, userInputSize);
        
    }
}


void execute (char* userInput[], int userInputSize) {
    
    int startPlaceHolder = 0;
    
    for (unsigned i = 0; i < userInputSize; ++i) {
        if (userInput[i] == "&&" ||
            userInput[i] == "||" ||) {
            
            
            
        }
    }
    
}
