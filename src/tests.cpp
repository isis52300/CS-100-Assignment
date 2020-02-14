#ifndef __TEST_HPP__
#define __TEST_HPP__

#include "gtest/gtest.h"
#include "token.h"
#include "tokenizer.h"
#include "tokenizer.cpp"
#include "echotoken.h"
#include "lstoken.h"
#include "mkdirtoken.h"
#include "andtoken.h"
#include "ortoken.h"

TEST(EchoTokenTest, EchoExecute) {
	Token* echo = new EchoToken("hello");
}

TEST(TokenizerTest, TokenizerExecute) {
	Token* test;
	Tokenizer* makeTokens = new Tokenizer();
	test = makeTokens->tokenize({"echo", "hello"});
	
}

#endif //__TEST_HPP__

