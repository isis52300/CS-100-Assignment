#include <iostream>
#include <string>
#include <vector>

#include "tokenizer.h"

usign namespace std;

Executor() {
    
    Tokenizer makeTokens;
    Token* treeOfTokens;
    
    bool timeToExit = false;
    //bool hasOrToken = false, hasAndToken = false, hasSemiToken = false;
    book hasConnector = false;
    vector<string> userInput;
    string line, token = "";
    int userInputSize;
    
    while (!timeToExit) {
        
        hasOrToken = false; hasAndToken = false; hasSemiToken = false;
        
        cout << "$ ";
        getline(cin, line); //Gets user input as a string
        
        for (unsigned i = 0; i < line.size(); ++i) {
            if (line.at(i) != ' ') {
                token = token + line.at(i);
            }
            else {
                userInput.push_back(token);
                token = "";
            }
        }
        
        treeOfTokens = tokenizer(userInput);
        
        treeOfTokens->execute();
        
    }
}

