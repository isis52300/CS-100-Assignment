#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include <vector>
#include <string>
#include <stdio.h>
#include <unistd.h>

#include "token.h"
#include "andtoken.h"
#include "ortoken"
#include "lstoken"
#include "echotoken"
#include "mkdirtoken"

class Tokenizer {
	public:
    
    Tokenizer();
    Token* tokenize(vector<string> userInput);
    
		bool isConnector(char);
		MyTree* newNode(char);
		MyTree* makeTree(char);
	protected:
		
};

#endif //__TOKENIZER_H__
