#include "tokenizer.h" //This file has the other token files included

#include<iostream>

Token* tokenize(vector<string> userInput) {
   unsigned i;
   string currentToken, editedCurrentToken, otherToken;
   vector<string> slicedUserInput1, slicedUserInput2;
   
    for (i = 0; i < userInput.size(); ++i) {// Checks for # tokens
        currentToken = userInput.at(i);
        bool isStartQuotations = false, isEndQuotations = false;
        if (currentToken == "#") {
            for (unsigned j = 0; j < userInput.size(); ++j) {
                otherToken = userInput.at(j);
                if (j < i && otherToken.at(0) == "\"") {
                    isStartQuotations = true;
                }
                if (j > i && otherToken.at(0) == "\"") {
                    isEndQuotations = true;
                }
            }
            
            if (isStartQuotations == false && isEndQuotations == false) {
                slicedUserInput1 = slice(userInput, 0, i - 1);
                tokenize(slicedUserInput1);
            }
        }
    }
   
   for (i = 0; i < userInput.size(); ++i) {
       currentToken = userInput.at(i);
       if (currentToken.at(currentToken.size() - 1) == ";") {//Checks for ; tokens
           
           //Slices the user input to have the line before the ;
           slicedUserInput1 = slice(userInput, 0, i - 1);
           editedCurrentToken = currentToken;
           editedCurrentToken.pop_back();
           
           //Slices the user input to have the line after the ;
           slicedUserInput1.push_back(editedCurrentToken);
           slicedUserInput2 = slice(userInput, i + 1, userInput.size() - 1);
           
           //Forks so that the lines before and after the ; can be tokenized
           pid_t pid = fork();
           int status;
           
           if (pid == 0) { //This is the child (tokens the first half before ;)
               
               tokenize(slicedUserInput1);
               
           }
           else if (pid > 0) { //This is the parent (tokens the second part after ;)
               
               waitpid(pid, &status, 0);
               tokenize(slicedUserInput2);
               
           }
           else { //The forking has failed
               
               cout << "The forking failed";
               exit(1);
               
           }
       }
   }
   
   for (i = 0; i < userInput.size(); ++i) {//Checks for && tokens
       currentToken = userInput.at(i);
       if (currentToken == "&&") {
           
           //Slices the vector to the first and second parts
           slicedUserInput1 = slice(userInput, 0, i - 1);
           slicedUserInput2 = slice(userInput, i + 1, userInput.size() - 1);
           
           //Returns AndToken pointer, and makes a tree with the tokenize fucntion making the leaves
           return new AndToken( tokenize(slicedUserInput1), tokenize(slicedUserInput2) );
       }
   }
    
    for (i = 0; i < userInput.size(); ++i) {//Checks for || tokens
        currentToken = userInput.at(i);
        if (currentToken == "||") {
            
            //Slices the vector to the first and second parts
            slicedUserInput1 = slice(userInput, 0, i - 1);
            slicedUserInput2 = slice(userInput, i + 1, userInput.size() - 1);
            
            //Returns AndToken pointer, and makes a tree with the tokenize fucntion making the leaves
            return new OrToken( tokenize(slicedUserInput1), tokenize(slicedUserInput2) );
        }
    }
    
    //At this point, there should be no more connectors to worry about (If there are, edit the above part to get rid of them)
    
    //Also, I am assuming there are at least one or two strings in the userInput vector
    //(Ex: ls (one string) Ex: ls -a (two strings)
    
    if (userInput.at(0) == "ls") {
        if (userInput.size() == 1) {
            return new LsToken();
        }
        else {
            string argument = "";
            for (unsigned i = 1; i < userInput.size(); ++i) {
                argument = argument + userInput.at(i);
                if (i + 1 != userInput.size()) {
                    argument = argument + " ";
                }
            }
            return new LsToken(argument);
        }
    }
    else if (userInput.at(0) == "mkdir") {
        string argument = "";
        for (unsigned i = 1; i < userInput.size(); ++i) {
            argument = argument + userInput.at(i);
            if (i + 1 != userInput.size()) {
                argument = argument + " ";
            }
        }
        return new MkdirToken(argument);
    }
    else if (userInput.at(0) == "echo") {
        string argument = "";
        for (unsigned i = 1; i < userInput.size(); ++i) {
            argument = argument + userInput.at(i);
            if (i + 1 != userInput.size()) {
                argument = argument + " ";
            }
        }
        return new EchoToken(argument);
    }
    else if (userInput.at(0) == "exit") {
        return new ExitToken();
    }
}
