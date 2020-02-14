#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include <vector>
#include <string>
#include <stdio.h>
#include <unistd.h>

#include "token.h"
#include "andtoken.h"
#include "ortoken.h"
#include "lstoken.h"
#include "echotoken.h"
#include "mkdirtoken.h"
#include "exittoken.h"

using namespace std;

class Tokenizer {
	public:
    
    Tokenizer();
    Token* tokenize(vector<string> userInput);
    
    vector<string> sliceVector(vector<string> originalVector, int startIndex, int endIndex);
	protected:
		
};

#endif //__TOKENIZER_H__
