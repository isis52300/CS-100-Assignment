#ifndef __TOKENIZER_CPP__
#define __TOKENIZER_CPP__

#include <vector>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "tokenizer.h"
#include "token.h"
#include "andtoken.h"
#include "ortoken.h"
#include "semicolontoken.h"
#include "lstoken.h"
#include "echotoken.h"
#include "mkdirtoken.h"
#include "exittoken.h"
#include "testtoken.h"

using namespace std;

Tokenizer::Tokenizer() {}

vector<string> Tokenizer::sliceVector(const vector<string> &originalVector, int startIndex, int endIndex) {
    
    vector<string> v = originalVector;
    
    if (startIndex == 0) {
        for (unsigned i = 0; i < (originalVector.size() - endIndex - 1); ++i) {
            v.pop_back();
        }
    }
    else {
        for (unsigned i = 0; i < startIndex; ++i) {
            v.erase(v.begin());
        }
    }
    
    return v;
    
}

Token* Tokenizer::tokenize(vector<string> userInput) {
    unsigned i;
    int temp1, temp2;
    string currentToken, editedCurrentToken, otherToken;
    vector<string> slicedUserInput1, slicedUserInput2;
    
    for (i = 0; i < userInput.size(); ++i) {// Checks for # tokens
        currentToken = userInput.at(i);
        bool isStartQuotations = false, isEndQuotations = false;
        if (currentToken == "#") {
            for (unsigned j = 0; j < userInput.size(); ++j) {
                otherToken = userInput.at(j);
                if (j < i && otherToken.at(0) == '\"') {
                    isStartQuotations = true;
                }
                if (j > i && otherToken.at( otherToken.size() - 1) == '\"') {
                    isEndQuotations = true;
                }
            }
            
            if (isStartQuotations == false && isEndQuotations == false) {
                temp1 = 0; temp2 = i-1;
                slicedUserInput1 = sliceVector(userInput, temp1, temp2);
                return tokenize(slicedUserInput1);
            }
        }
    }
    
    for (i = 0; i < userInput.size(); ++i) {
        currentToken = userInput.at(i);
        bool isStartQuotations = false, isEndQuotations = false;
        if (currentToken.at(currentToken.size() - 1) == ';') {//Checks for ; tokens
            
            for (unsigned j = 0; j < userInput.size(); ++j) {
                otherToken = userInput.at(j);
                if (j < i && otherToken.at(0) == '\"') {
                    isStartQuotations = true;
                }
                if (j > i && otherToken.at( otherToken.size() - 1) == '\"') {
                    isEndQuotations = true;
                }
            }

            if (isStartQuotations == false && isEndQuotations == false) {
            	//Slices the user input to have the line before the ;
            	temp1 = 0; temp2 = i - 1;
            	slicedUserInput1 = sliceVector(userInput, temp1, temp2);
            	editedCurrentToken = currentToken;
            	editedCurrentToken.pop_back(); //remove
        //    slicedUserInput1.push_back(editedCurrentToken);
            	//Slices the user input to have the line after the ;
            	temp1 = i + 1; temp2 = userInput.size() - 1;
            	slicedUserInput1.push_back(editedCurrentToken);
            	slicedUserInput2 = sliceVector(userInput, temp1, temp2);
            
            	return new SemiColonToken(tokenize(slicedUserInput1), tokenize(slicedUserInput2));
            }
        }
    }
    
    for (i = 0; i < userInput.size(); ++i) {//Checks for && tokens
        currentToken = userInput.at(i);
        bool isStartQuotations = false, isEndQuotations = false;
        if (currentToken == "&&") {
            
            for (unsigned j = 0; j < userInput.size(); ++j) {
                otherToken = userInput.at(j);
                if (j < i && otherToken.at(0) == '\"') {
                    isStartQuotations = true;
                }
                if (j > i && otherToken.at( otherToken.size() - 1) == '\"') {
                    isEndQuotations = true;
                }
            }

            if (isStartQuotations == false && isEndQuotations == false) {  
            	//Slices the vector to the first and second parts
            	temp1 = 0; temp2 = i - 1;
            	slicedUserInput1 = sliceVector(userInput, temp1, temp2);
            	temp1 = i + 1; temp2 = userInput.size() - 1;
            	slicedUserInput2 = sliceVector(userInput, temp1, temp2);
            
            	//Returns AndToken pointer, and makes a tree with the tokenize fucntion making the leaves
            	return new AndToken( tokenize(slicedUserInput1), tokenize(slicedUserInput2) );
             }
        }
    }
    
    for (i = 0; i < userInput.size(); ++i) {//Checks for || tokens
        currentToken = userInput.at(i);
        bool isStartQuotations = false, isEndQuotations = false;
        if (currentToken == "||") {
      
            for (unsigned j = 0; j < userInput.size(); ++j) {
                otherToken = userInput.at(j);
                if (j < i && otherToken.at(0) == '\"') {
                    isStartQuotations = true;
                }
                if (j > i && otherToken.at( otherToken.size() - 1) == '\"') {
                    isEndQuotations = true;
                }
            }
      
            if (isStartQuotations == false && isEndQuotations == false) {
            	//Slices the vector to the first and second parts
            	temp1 = 0; temp2 = i - 1;
            	slicedUserInput1 = sliceVector(userInput, temp1, temp2);
            	temp1 = i + 1; temp2 = userInput.size() - 1;
            	slicedUserInput2 = sliceVector(userInput, temp1, temp2);
            
            
            	//Returns AndToken pointer, and makes a tree with the tokenize fucntion making the leaves
            	return new OrToken( tokenize(slicedUserInput1), tokenize(slicedUserInput2) );
            }
        }
    }
    
    //At this point, there should be no more connectors to worry about (If there are, edit the above part to get rid of them)
    //
    //Also, I am assuming there are at least one or two strings in the userInput vector
    //(Ex: ls (one string) Ex: ls -a (two strings)
    
    
    if (userInput.at(0) == "ls") {
        if (userInput.size() == 1) {
            return new LsToken();
        }
        else {
            return new LsToken(userInput);
        }
    }
    else if (userInput.at(0) == "mkdir") {
        return new MkdirToken(userInput);
    }
    else if (userInput.at(0) == "echo") {
        return new EchoToken(userInput);
    }
    else if (userInput.at(0) == "exit") {
        return new ExitToken();
    }
    else if (userInput.at(0) == "test") {
        return new TestToken();
    }
    
    return new ExitToken();
}

#endif //__TOKENIZER_CPP__
