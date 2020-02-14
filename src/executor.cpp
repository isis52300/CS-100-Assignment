#include <iostream>
#include <string>
#include <vector>

#include "tokenizer.h"

using namespace std;

Executor::Executor()
{
	cout << "default" << endl;
}

void Executor::execute() {
    Tokenizer makeTokens; //Initializes Tokenizer class;
    Token* treeOfTokens; //Tree pointer place holder
    
    bool timeToExit = false; //Used to loop the while loop
    vector<string> userInput; //is used to pass through tokenizer
    string line = "", token = ""; //used to help cin the user input and make it a vector
    
    while (!timeToExit) { //Might make this repeat forever until ExitToken is executed
        
        cout << "$ ";
        getline(cin, line); //Gets user input as a string
        
        for (unsigned i = 0; i < line.size(); ++i) { //Turns the string into a vector of individual strings
            if (line.at(i) != ' ') {
                token = token + line.at(i);
            }
            else {
                userInput.push_back(token);
                token = "";
            }
        }
        
        treeOfTokens = makeTokens.tokenize(userInput); //Uses vector of strings to make a tree of tokens
        
        treeOfTokens->execute(); //Now that the token tree is made, it will go through and execute everything
        
        userInput.clear(); //Clears the userInput vector so it is fresh when it's used again
        
        /* Note: Might need to implement a way to clear the treeOfTokens pointer to make sure there are no floating pointers and memory leaks*/
        
    }
}
