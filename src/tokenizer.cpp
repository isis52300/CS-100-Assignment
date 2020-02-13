#include "tokenizer.h"

#include<iostream>


struct MyTree {
	char inChar;
	MyTree* left, *right;
};

bool isConnector(char c)
{
	if(c == "&&"  || c == "||")
		return true;
	return false;	
}

MyTree* newNode(char c)
{
	MyTree* temp = new MyTree;
	temp->left = temp->right = nullptr;
	temp->inChar = c;
	return temp;
}

MyTree* makeTree(char table<Token*>)
{
	stack<MyTree *> st;
	MyTree *t, *t1, *t2;
	
	for(int i = 0; i < table.size(); i++)
	{
		if(!isConnector(table.at(i))
		{
			t = newNode(table.at(i));
			st.push(t);		
		}
		else
		{
			t = newNode(table.at(i));
			
			t1 = st.top();
			st.pop();
			t2 = st.top();
			st.pop()

			t->right = t1;
			t->left = t2;

			st.push(t);	
		}
	}

	t = st.top();
	st.pop();

	return t;
}

Token* tokenize(vector<string> userInput) {
   unsigned i;
   string currentToken, editedCurrentToken, otherToken;
   vector<string> slicedUserInput1, slicedUserInput2;
   
    for (i = 0; i < userInput.size(); ++i) {
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
   
   for (i = 0; i < userInput.size(); ++i) {
       currentToken = userInput.at(i);
       if (currentToken == "&&") {
           
           //Slices the vector to the first and second parts
           slicedUserInput1 = slice(userInput, 0, i - 1);
           slicedUserInput2 = slice(userInput, i + 1, userInput.size() - 1);
           
           //Returns AndToken pointer, and makes a tree with the tokenize fucntion making the leaves
           return new AndToken( tokenize(slicedUserInput1), tokenize(slicedUserInput2) );
       }
   }
}
