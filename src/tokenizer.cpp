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

void Tokenizer::insert (vector<string> &originalVector, string word, unsigned index) {
    
    if (originalVector.size() == 0) {
        originalVector.push_back(word);
        return;
    }
    
    if (index == originalVector.size() - 1) {
        originalVector.push_back(word);
        return;
    }
    
    originalVector.push_back(word);
    string currWord = word;
    string nextWord = originalVector.at(index);
    
    for (unsigned i = index; i + 1 < originalVector.size(); ++i) {
        originalVector.at(i) = currWord;
        currWord = nextWord;
        nextWord = originalVector.at(i+1);
    }
    originalVector.at(originalVector.size() - 1) = currWord;
    
}

vector<string> Tokenizer::seperator(const vector<string> &originalVector) {
    
    vector<string> v = originalVector;
    string currWord, tempWord = "";
    
    for (unsigned i = 0; i < v.size(); ++i) {
        currWord = v.at(i);
        if (currWord.size() != 1 && currWord.at(0) == '\"') {
            for (unsigned j = 1; j < currWord.size(); ++j) {
                tempWord += currWord.at(j);
            }
            v.at(i) = tempWord;
            insert(v, "\"", i);
            currWord = v.at(i+1);
        }
        else if (currWord.size() != 1 && currWord.at(currWord.size() - 1) == ';') {
            currWord.pop_back();
            if(i != v.size() - 1) {
                v.at(i) = currWord;
                insert(v, ";", i+1);
                currWord = v.at(i+1);
            }
            else {
                v.at(i) = currWord;
                v.push_back(";");
                i = i-1;
            }
        }
        else if (currWord.size() != 1 && currWord.at(currWord.size() - 1) == '\"') {
            currWord.pop_back();
            if(i != v.size() - 1) {
                v.at(i) = currWord;
                insert(v, "\"", i+1);
                currWord = v.at(i+1);
            }
            else {
                v.at(i) = currWord;
                v.push_back("\"");
            }
        }
        else if (currWord.size() != 1 && currWord.at(0) == '(') {
            for (unsigned j = 1; j < currWord.size(); ++j) {
                tempWord += currWord.at(j);
            }
            v.at(i) = tempWord;
            insert(v, "(", i);
            currWord = v.at(i+1);
        }
        else if (currWord.size() != 1 && currWord.at(currWord.size() - 1) == ')') {
            currWord.pop_back();
            if(i != v.size() - 1) {
                v.at(i) = currWord;
                insert(v, ")", i+1);
                currWord = v.at(i+1);
            }
            else {
                v.at(i) = currWord;
                v.push_back(")");
            }
        }

        
    }
    
    return v;
}

vector<string> Tokenizer::flipVector(const vector<string> &originalVector) {
    
    vector<string> v = originalVector;
    vector<string> newVector;
    
    for (unsigned i = v.size() - 1; i >= 0; --i) {
        
        if (v.size() == 0) {
            return newVector;
        }
        
        string currToken = v.at(i);
        
        if (currToken == "(") {
            newVector.push_back(")");
            v = sliceVector(v, 0, i-1);
        }
        else if (currToken == ")") {
            newVector.push_back("(");
            v = sliceVector(v, 0, i-1);
        }
        else if (currToken == "echo" ||
                 currToken == "mkdir" ||
                 currToken == "ls" ||
                 currToken == "exit" ||
                 currToken == "test" ||
                 currToken == "[") {
            
            for (unsigned j = i; j < v.size(); ++j) {
                newVector.push_back(v.at(j));
            }
            v = sliceVector(v, 0, i-1);
            
        }
        else if (currToken == "&&" || currToken == "||") {
            newVector.push_back(currToken);
            v = sliceVector(v, 0, i-1);
        }
    }
    
    return newVector;
    
}

vector<string> Tokenizer::makePostFix(vector<string> &originalVector) {
    
    vector<string> s;
    vector<string> q;
    string currToken;
    bool quotationMarks = false;
    
    for (unsigned i = 0; i < originalVector.size(); ++i) {
        
        currToken = originalVector.at(i);
        if (currToken == "echo" ||
            currToken == "mkdir" ||
            currToken == "ls" ||
            currToken == "exit" ||
            currToken == "test" ||
            currToken == "[") {
            int incrementer = i;
            while (((currToken != "&&" && currToken != "||" &&
                     currToken != ";" && currToken != "(" && currToken != ")")
                    && (incrementer < originalVector.size()))
                   || ((currToken == "&&" || currToken == "||" || currToken == ";")
                       && quotationMarks == true)) {
                       if (currToken == "\"" && quotationMarks == false) {
                           quotationMarks = true;
                       }
                       else if (currToken == "\""){
                           quotationMarks = false;
                       }
                       q.push_back(currToken);
                       ++incrementer;
                       if (incrementer < originalVector.size()) {
                           currToken = originalVector.at(incrementer);
                       }
                   }
            i = incrementer - 1;
        }
        else if (currToken == "&&" || currToken == "||" || currToken == ";") {
            if (s.size() != 0 && quotationMarks == false) {
                while ((s.size() != 0) && (s.at(s.size() - 1) != "(") &&
                       (s.at(s.size() - 1) == "&&" || s.at(s.size() - 1) == "||" || s.at(s.size() - 1) == ";")) {
                    q.push_back(s.at(s.size() - 1));
                    s.pop_back();
                }
            }
            s.push_back(currToken);
        }
        else if (currToken == "(") {
            s.push_back(currToken);
        }
        else if (currToken == ")") {
            while (s.at(s.size() - 1) != "(") {
                q.push_back(s.at(s.size() - 1));
                s.pop_back();
            }
            s.pop_back();
        }
        
    }
    
    while (s.size() != 0) {
        q.push_back(s.at(s.size() - 1));
        s.pop_back();
    }
    
    return q;
    
}

Token* Tokenizer::tok(vector<string> &v, unsigned &startIndex) {
    int temp1, temp2;
    string currToken;
    vector<string> slicedUserInput;
    
    for (unsigned i = startIndex; i < v.size(); ++i) {
        currToken = v.at(i);
        if (currToken == "&&") {
            ConnectorToken* T = new AndToken();
            temp1 = i+1; temp2 = v.size() - 1;
            startIndex = temp1;
            //slicedUserInput = sliceVector(v, temp1, temp2);
            T->addLeft(tok(v, startIndex));
            T->addRight(tok(v, startIndex));
            return T;
        }
        else if (currToken == "||") {
            ConnectorToken* T = new OrToken();
            temp1 = i+1; temp2 = v.size() - 1;
            startIndex = temp1;
            //slicedUserInput = sliceVector(v, temp1, temp2);
            T->addLeft(tok(v, startIndex));
            T->addRight(tok(v, startIndex));
            return T;
        }
        else if (currToken == ";") {
            ConnectorToken* T = new SemicolonToken();
            temp1 = i+1; temp2 = v.size() - 1;
            startIndex = temp1;
            //slicedUserInput = sliceVector(v, temp1, temp2);
            T->addLeft(tok(v, startIndex));
            T->addRight(tok(v, startIndex));
            return T;
        }
        else if (currToken == "echo") {
            int incrementer = i+1;
            slicedUserInput.push_back(currToken);
            currToken = v.at(incrementer);
            bool quotationMarks = false;
            while (((currToken != "echo" && currToken != "ls" && currToken != "mkdir" &&
                   currToken != "test" && currToken != "[" && currToken != "exit"
                   && currToken != "&&" && currToken != "||")
                   || (currToken == "&&" && quotationMarks == true) || (currToken == "||" && quotationMarks == true))
                   && incrementer < v.size()) {
                if (currToken == "\"" && quotationMarks == false) {
                    quotationMarks = true;
                }
                else if (currToken == "\"") {
                    quotationMarks = false;
                }
                slicedUserInput.push_back(currToken);
                ++incrementer;
                if (incrementer < v.size()) {
                    currToken = v.at(incrementer);
                }
            }
            i = incrementer - 1;
            temp1 = i; temp2 = v.size() - 1;
            startIndex = temp1;
            //v = sliceVector(v, temp1, temp2);
            return new EchoToken(slicedUserInput);
        }
        else if (currToken == "ls") {
            if (v.size() == 1) {
                  return new LsToken();
            }
            int incrementer = i + 1;
            slicedUserInput.push_back(currToken);
            currToken = v.at(incrementer);
            while (currToken != "echo" && currToken != "ls" && currToken != "mkdir" &&
                   currToken != "test" && currToken != "[" && currToken != "exit"
                   && incrementer < v.size()) {
                slicedUserInput.push_back(currToken);
                ++incrementer;
                if (incrementer < v.size()) {
                    currToken = v.at(incrementer);
                }
            }
            temp1 = i; temp2 = v.size() - 1;
            v = sliceVector(v, temp1, temp2);
            if (slicedUserInput.size() == 0) {
                return new LsToken();
            }
            return new LsToken(slicedUserInput);
        }
        else if (currToken == "mkdir") {
            int incrementer = i + 1;
            slicedUserInput.push_back(currToken);
            currToken = v.at(incrementer);
            while (currToken != "echo" && currToken != "ls" && currToken != "mkdir" &&
                   currToken != "test" && currToken != "[" && currToken != "exit"
                   && incrementer < v.size()) {
                slicedUserInput.push_back(currToken);
                ++incrementer;
                if (incrementer < v.size()) {
                    currToken = v.at(incrementer);
                }
            }
            temp1 = i; temp2 = v.size() - 1;
            v = sliceVector(v, temp1, temp2);
            return new MkdirToken(slicedUserInput);
        }
        else if (currToken == "test") {
            int incrementer = i + 1;
            slicedUserInput.push_back(currToken);
            currToken = v.at(incrementer);
            while (currToken != "echo" && currToken != "ls" && currToken != "mkdir" &&
                   currToken != "test" && currToken != "[" && currToken != "exit"
                   && incrementer < v.size()) {
                slicedUserInput.push_back(currToken);
                ++incrementer;
                if (incrementer < v.size()) {
                    currToken = v.at(incrementer);
                }
            }
            temp1 = i; temp2 = v.size() - 1;
            v = sliceVector(v, temp1, temp2);
            return new TestToken(slicedUserInput);
        }
        else if (currToken == "[") {
            int incrementer = i + 1;
            //slicedUserInput.push_back(currToken);
            currToken = v.at(incrementer);
            while (currToken != "echo" && currToken != "ls" && currToken != "mkdir" &&
                   currToken != "test" && currToken != "[" && currToken != "exit"
                   && incrementer < v.size()) {
                slicedUserInput.push_back(currToken);
                ++incrementer;
                if (incrementer < v.size()) {
                    currToken = v.at(incrementer);
                }
            }
            temp1 = i; temp2 = v.size() - 1;
            v = sliceVector(v, temp1, temp2);
            return new TestToken(slicedUserInput);
        }
        else if (currToken == "exit") {
            return new ExitToken();
        }
    }
    
    return new ExitToken();
}

Token* Tokenizer::tokenize(vector<string> userInput) {
   /* unsigned i;
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
        return new TestToken(userInput);
    }
    else if (userInput.at(0) == "[") { //I'm assuming that there will always be a ] at the end
        slicedUserInput1 = sliceVector(userInput, 1, userInput.size() - 2);
        return new TestToken(slicedUserInput1);
    }
    
    return new ExitToken();*/
    
    vector<string> v = userInput;
    
    v = seperator(v);
    v = flipVector(v);
    v = makePostFix(v);
    v = flipVector(v);
    
    unsigned i = 0;
    return tok(v, i);
    
    /*int temp1, temp2;
    vector<string> slicedUserInput;
    
    for (unsigned i = 0; i < v.size(); ++i) {
        currToken = v.at(i);
        if (currToken == "&&") {
            Token* T = new AndToken();
            temp1 = i+1; temp2 = v.size() - 1;
            slicedUserInput = sliceVector(userInput, temp1, temp2);
            T->addLeft(tokenize(v));
            T->addRight(tokenize(v));
            return T;
        }
        else if (currToken == "||") {
            Token* T = new OrToken();
            temp1 = i+1; temp2 = v.size() - 1;
            slicedUserInput = sliceVector(userInput, temp1, temp2);
            T->addLeft(tokenize(v));
            T->addRight(tokenize(v));
            return T;
        }
        else if (currToken == ";") {
            Token* T = new SemicolonToken();
            temp1 = i+1; temp2 = v.size() - 1;
            slicedUserInput = sliceVector(userInput, temp1, temp2);
            T->addLeft(tokenize(v));
            T->addRight(tokenize(v));
            return T;
        }
        else if (currToken == "echo") {
            int incrementer = i + 1;
            currToken = v.at(incrementer);
            while (currToken != "echo" && currToken != "ls" && currToken != "mkdir" &&
                   currToken != "test" && currToken != "[" && currToken != "exit"
                   && incrementer < v.size()) {
                slicedUserInput.push_back(currToken);
                ++incrementer;
                if (incrementer < v.size()) {
                    currToken = v.at(incrementer);
                }
            }
            temp1 = i; temp2 = v.size() - 1;
            v = sliceVector(v, temp1, temp2);
            return new EchoToken(slicedUserInput);
        }
        else if (currToken == "ls") {
            int incrementer = i + 1;
            currToken = v.at(incrementer);
            while (currToken != "echo" && currToken != "ls" && currToken != "mkdir" &&
                   currToken != "test" && currToken != "[" && currToken != "exit"
                   && incrementer < v.size()) {
                slicedUserInput.push_back(currToken);
                ++incrementer;
                if (incrementer < v.size()) {
                    currToken = v.at(incrementer);
                }
            }
            temp1 = i; temp2 = v.size() - 1;
            v = sliceVector(v, temp1, temp2);
            if (slicedUserInput.size() == 0) {
                return new LsToken();
            }
            return new LsToken(slicedUserInput);
        }
        else if (currToken == "mkdir") {
            int incrementer = i + 1;
            currToken = v.at(incrementer);
            while (currToken != "echo" && currToken != "ls" && currToken != "mkdir" &&
                   currToken != "test" && currToken != "[" && currToken != "exit"
                   && incrementer < v.size()) {
                slicedUserInput.push_back(currToken);
                ++incrementer;
                if (incrementer < v.size()) {
                    currToken = v.at(incrementer);
                }
            }
            temp1 = i; temp2 = v.size() - 1;
            v = sliceVector(v, temp1, temp2);
            return new MkdirToken(slicedUserInput);
        }
        else if (currToken == "test") {
            int incrementer = i + 1;
            currToken = v.at(incrementer);
            while (currToken != "echo" && currToken != "ls" && currToken != "mkdir" &&
                   currToken != "test" && currToken != "[" && currToken != "exit"
                   && incrementer < v.size()) {
                slicedUserInput.push_back(currToken);
                ++incrementer;
                if (incrementer < v.size()) {
                    currToken = v.at(incrementer);
                }
            }
            temp1 = i; temp2 = v.size() - 1;
            v = sliceVector(v, temp1, temp2);
            return new TestToken(slicedUserInput);
        }
        else if (currToken == "[") {
            int incrementer = i + 1;
            currToken = v.at(incrementer);
            while (currToken != "echo" && currToken != "ls" && currToken != "mkdir" &&
                   currToken != "test" && currToken != "[" && currToken != "exit"
                   && incrementer < v.size()) {
                slicedUserInput.push_back(currToken);
                ++incrementer;
                if (incrementer < v.size()) {
                    currToken = v.at(incrementer);
                }
            }
            temp1 = i; temp2 = v.size() - 1;
            v = sliceVector(v, temp1, temp2);
            return new TestToken(slicedUserInput);
        }
        else if (currToken == "exit") {
            return new ExitToken();
        }
    }
    
    return new ExitToken();*/
    
    
    
    
    
}

#endif //__TOKENIZER_CPP__
