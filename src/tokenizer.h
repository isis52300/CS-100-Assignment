#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include <vector>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "token.h"
#include "andtoken.h"
#include "ortoken.h"
#include "lstoken.h"
#include "echotoken.h"
#include "mkdirtoken.h"
#include "exittoken.h"
#include "testtoken.h"

using namespace std;

class Tokenizer {
	public:
    
    Tokenizer();
    Token* tokenize(vector<string> userInput);
    Token* tok(vector<string> &v, unsigned &startIndex);
    
	protected:
    vector<string> sliceVector(const vector<string> &originalVector, int startIndex, int endIndex);
    void insert (vector<string> &originalVector, string word, unsigned index);
    vector<string> seperator(const vector<string> &originalVector);
    
    vector<string> flipVector(const vector<string> &originalVector);
    vector<string> makePostFix(vector<string> &originalVector);
};  

#endif //__TOKENIZER_H__
